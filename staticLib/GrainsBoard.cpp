#include "GrainsBoard.h"
#include "Inclusions.h"
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <thread>
#include <ctime>
#include <map>


void GrainsBoard::clear()
{
	delete board;
}

int GrainsBoard::getBiggestNeighber(std::list<Point> neighbers, std::list<int> without)
{

	std::map<int, int>ids;
	for (auto neighber : neighbers) {
		if ((board->get(neighber)) != 0 && (board->get(neighber)!=-1) && std::find(without.begin(), without.end(), board->get(neighber)) == without.end())
		{
			if (ids.find(board->get(neighber)) == ids.end())
			{
				ids[board->get(neighber)] = 1;
			}
			else
			{
				ids[board->get(neighber)] = ids[board->get(neighber)] + 1;
			}
		}
	}

	int max_id=0, max_value = 0;


	for (auto id : ids)
	{
		if (id.second > max_value) {
			max_value = id.second;
			max_id = id.first;
		}
	}
	return max_id;
}

int GrainsBoard::getBiggestNeighber(std::list<Point> neighbers, int *count)
{

	std::map<int, int>ids;
	for (auto neighber : neighbers) {
		if ((board->get(neighber)) != 0 && (board->get(neighber) != -1))
		{
			if (ids.find(board->get(neighber)) == ids.end())
			{
				ids[board->get(neighber)] = 1;
			}
			else
			{
				ids[board->get(neighber)] = ids[board->get(neighber)] + 1;
			}
		}
	}

	int max_id = 0, max_value = 0;


	for (auto id : ids)
	{
		if (id.second > max_value) {
			max_value = id.second;
			max_id = id.first;
		}
	}
	*count = max_value;
	return max_id;
}




int GrainsBoard::CurvatureGrowth(int x, int y, Board *board2, int propability, std::list<int> without) {

	int count;
	//RULE1
	std::list<Point> neighbers = Neighberhood::get_Neighbours(x, y, board, neighberhoodType::MOORE);
	int biggest_neighber = getBiggestNeighber(neighbers, &count);
	if (count >= 5)
	{
		if (std::find(without.begin(), without.end(), biggest_neighber) == without.end())
		{
			board2->set(x, y, biggest_neighber);
			return 1;
		}
	}
	//RULE2
	neighbers = Neighberhood::get_Neighbours(x, y, board, neighberhoodType::NEAREST_MOORE);
	biggest_neighber = getBiggestNeighber(neighbers, &count);
	if (count == 3)
	{
		if (std::find(without.begin(), without.end(), biggest_neighber) == without.end())
		{
			board2->set(x, y, biggest_neighber);
			return 1;
		}
	}
	//RULE3
	neighbers = Neighberhood::get_Neighbours(x, y, board, neighberhoodType::FURTHER_MOORE);
	biggest_neighber = getBiggestNeighber(neighbers, &count);
	if (count == 3)
	{
		if (std::find(without.begin(), without.end(), biggest_neighber) == without.end())
		{
			board2->set(x, y, biggest_neighber);
			return 1;
		}
	}
	//RULE4
	neighbers = Neighberhood::get_Neighbours(x, y, board, neighberhoodType::MOORE);
	biggest_neighber = getBiggestNeighber(neighbers, &count);
	if (biggest_neighber != 0)
	{
		if (rand() % 100 < propability)
		{
			if (std::find(without.begin(), without.end(), biggest_neighber) == without.end())
			{
				board2->set(x, y, biggest_neighber);
				return 1;
			}
		}
		return 0;
	}
	return 0;
}

int GrainsBoard::simpleGrowth(int x, int y, Board* board2, std::list<int> without)
{
	std::list<Point> neighbers = Neighberhood::get_Neighbours(x, y, board, neighberhoodType::VON_NEUMANN);

	int biggest_neighber = getBiggestNeighber(neighbers, without);
	if (biggest_neighber != 0)
	{
			board2->set(x, y, biggest_neighber);
			return 1;
	}
	return 0;

}

double GrainsBoard::calculateEnergy(Point p)
{

	std::list<Point>  neighbers = Neighberhood::get_Neighbours(p.x, p.y, board, neighberhoodType::VON_NEUMANN);

	double E1 = 0;
	for (auto point : neighbers) {
		double delta;
		if (board->get(point) == board->get(p)) {
			delta = 1;
		}
		else
		{
			delta = 0;
		}
		E1 += 1 - delta;
	}

	return E1;
}

int GrainsBoard::calculateEnergy2(Point p)
{
	std::list<Point>  neighbers = Neighberhood::get_Neighbours(p.x, p.y, board, neighberhoodType::VON_NEUMANN);

	int E1 = 0;
	for (auto point : neighbers) {
		int delta;
		if (energy->get(point.x, point.y) == energy->get(p.x, p.y)) {
			delta = 1;
		}
		else
		{
			delta = 0;
		}
		E1 += 1 - delta;
	}

	return E1 * energy->get(p.x, p.y);
}


GrainsBoard::GrainsBoard(size_t width, size_t height)
{
	board = new Board(width, height);
	srand(time(NULL));
	ids_count = 0;
	energy = new EnergyDistribution(width, height);
}

GrainsBoard::GrainsBoard(Board *board)
{
	srand(time(NULL));
	this->board = board;
	ids_count = 0;
	energy = new EnergyDistribution(board->getWidth(), board->getHeight());
}

GrainsBoard::GrainsBoard(size_t width, size_t height, int n)
{
	this->board = new Board(width, height, n);
	ids_count = n;
	energy = new EnergyDistribution(board->getWidth(), board->getHeight());
}






GrainsBoard::~GrainsBoard()
{
	delete board;
}

void GrainsBoard::addNucleons(int count)
{
	int added = 0;
	while(added < count)
	{
		int x = rand() % board->getWidth();
		int y = rand() % board->getHeight();

		if (board->get(x,y) == 0) {
			ids_count++;
			added++;
			board->set(x,y,ids_count);
		}
	}
}

void GrainsBoard::addInclusions(inclusionsType type, int size, int number)
{
	switch (type)
	{
	case inclusionsType::SQUARE:
		Inclusions::addSquareInclusions(number, size, board);
		break;
	case inclusionsType::CIRCLE:
		Inclusions::addCircleInclusions(number, size, board);
		break;
	}
}

bool GrainsBoard::grow(growthType type, int cycles_number, int propability, std::list<int> without)
{
	//int finished = ids_count;
	//int all = board->getWidth() * board->getHeight();

	//for (int i = 0; (i < cycles_number) || (ids_count >= all); i++)
	//{
	//	Board *board2 = new Board(*board);
	//	for (int y = 0; y < board->getHeight(); y++)
	//	{
	//		for (int x = 0; x < board->getWidth(); x++)
	//		{
	//			if (board->get(x, y) == 0) {

	//				switch (type)
	//				{ 
	//				case growthType::SIMPLE_GROWTH:
	//					finished += simpleGrowth(x, y, board2, without);
	//					break;
	//				case growthType::CURVATURE_GROWTH:
	//					finished += CurvatureGrowth(x, y, board2, propability, without);
	//					break;
	//				}
	//			}
	//			else
	//			{
	//				finished++;
	//			}
	//		}
	//	}
	//	delete board;
	//	board = board2;
	//}

	//if(ids_count >= all)
	//	return true;

	//return false;

	int finished = ids_count;
	int all = board->getWidth() * board->getHeight();

	for (int i = 0; (i < cycles_number) || (ids_count >= all); i++)
	{
		Board* board2 = new Board(*board);
		for (int y = 0; y < board->getHeight(); y++)
		{
			for (int x = 0; x < board->getWidth(); x++)
			{
				if (board->get(x, y) == 0) {

					switch (type)
					{
					case growthType::SIMPLE_GROWTH:
						finished += simpleGrowth(x, y, board2, without);
						break;
					case growthType::CURVATURE_GROWTH:
						finished += CurvatureGrowth(x, y, board2, propability, without);
						break;
					}
				}
				else
				{
					finished++;
				}
			}
		}
		delete board;
		board = board2;
	}

	if (ids_count >= all)
		return true;

	return false;
}

void GrainsBoard::clear(std::list<int> ignore)
{
	ids_count = ignore.size();
	board->clear(ignore);
}

void GrainsBoard::setNewColor(std::list<int> ids)
{
	ids_count -= ids.size() - 1;
	board->set(ids, ids.front());
}

void GrainsBoard::allBoundaries()
{
	Board* board2 = new Board(*board);
	for (int y = 0; y < board->getWidth(); y++)
	{
		for (int x = 0; x < board->getHeight(); x++)
		{
			int current = board->get(x, y);
			int next1 = board->get(BoundaryConditions::get_right(x, board), y);
			int next2 = board->get(x, BoundaryConditions::get_bottom(y, board));
			if (board->get(x, y) != -1 && (current != next1 || current != next2))
			{
				board2->set(x, y, -1);
			}
		}
	}
	delete board;
	board = board2;
}

void GrainsBoard::selectedBoundaries(std::list<int> selected)
{
	Board* board2 = new Board(*board);
	for (int y = 0; y < board->getHeight(); y++)
	{
		for (int x = 0; x < board->getWidth(); x++)
		{
			int current = board->get(x, y);
			int next1 = board->get(BoundaryConditions::get_right(x, board), y);
			int next2 = board->get(x, BoundaryConditions::get_bottom(y, board));
			if (current != -1 && (current != next1 || current != next2))
			{
				if((std::find(selected.begin(), selected.end(), board->get(x, y)) != selected.end()) || (std::find(selected.begin(), selected.end(), next1) != selected.end()) || (std::find(selected.begin(), selected.end(), next2) != selected.end()))
				board2->set(x, y, -1);
			}
		}
	}
}

#include <iostream>
void GrainsBoard::fillRandomly(std::list<int> ignore, int n)
{
	ids_count = n + ignore.size();
	board->random(ignore, n);
}
int GrainsBoard::mc_method(int n)
{

	//std::list<Point>  neighbers = Neighberhood::get_Neighbours(0, 0, board, neighberhoodType::VON_NEUMANN);
	//std::vector<Point>  points;
	//for (int y = 0; y < board->getHeight(); y++)
	//{
	//	for(int x=0; x<board->getWidth(); x++)
	//	{
	//		points.push_back(Point(x, y));
	//	}
	//}

	//
	//while(points.size() > 0)
	//{

	//	int it = rand() % points.size();
	//	Point randPoint = points[it];
	//	points.erase(points.begin() + it);

	//	int E1 = calculateEnergy(randPoint);

	//	int old = board->get(randPoint);
	//	board->set(randPoint, rand() % ids_count);

	//	int E2 = calculateEnergy(randPoint);

	//	if (E2 - E1 > 0) {
	//		board->set(randPoint, old);
	//	}
	//}

	//return 0;

	int threads_count = 6;
	std::vector<Point> *points = new std::vector<Point>[threads_count];


	int delta = board->getHeight() / threads_count;
	std::cout << "DELTA: " << delta << std::endl;
	int thread_num = -1;
	int last_line_for_thread = 0;
	for (int y = 0; y < board->getHeight(); y++)
	{
		if (last_line_for_thread == y)
		{
			if (thread_num == threads_count - 2)
			{
				last_line_for_thread = board->getHeight();
			}
			else
			{
				if (y + delta <= board->getHeight()) {
					last_line_for_thread = y + delta;
				}
				else
				{
					last_line_for_thread = board->getHeight();
				}
				thread_num++;
			}
		}
		for (int x = 0; x < board->getWidth(); x++)
		{
			points[thread_num].push_back(Point(x, y));
		}
	}


	auto f = [this](std::vector<Point> points, Board* board, int seed) {
		
		srand(seed);
		while (points.size() > 0)
		{
			int it = rand() % points.size();
			Point randPoint = points[it];
			points.erase(points.begin() + it);
			int E1 = calculateEnergy(randPoint);
			int old = board->get(randPoint);
			board->set(randPoint, rand() % ids_count+1);
			int E2 = calculateEnergy(randPoint);

			if (E2 - E1 > 0) {
				board->set(randPoint, old);
			}
		}
	};

	std::thread** threads = new std::thread*[threads_count];
	for (int i = 0; i < threads_count; i++)
	{
		threads[i] = new std::thread(f, points[i], board, rand());
	}

	for (int i = 0; i < threads_count; i++)
	{
		threads[i]->join();
		delete threads[i];
	}
	delete threads;

	return 0;
}

int** GrainsBoard::getBoard()
{
	return board->getBoard();
}

double** GrainsBoard::getEnergy()
{
	return energy->getBoard();
}

int GrainsBoard::get(int x, int y)
{
	return board->get(x, y);
}

void GrainsBoard::distributeEnergy(energyDistributionType type, double inside, double on_edges)
{
	if (type == energyDistributionType::HOMOGENOUS) {

		energy->distributeEnergy(inside);
	}
	else 
	{
		Board* board2=new Board(*board);
		this->allBoundaries();
		energy->distributeEnergy(inside, on_edges, board);

		delete board;
		board = board2;
	}
}

void GrainsBoard::srxmc_add_nucleons(int n, int from)
{
	int added = 0;
	while (added < n)
	{
		int x = rand() % board->getWidth();
		int y = rand() % board->getHeight();


		added++;
		board->set(x, y, -1-added-from);
		energy->set(x, y, 0);
		
	}
}

void GrainsBoard::srxmc(int steps)
{

	int threads_count = 6;
	std::vector<Point>* points = new std::vector<Point>[threads_count];


	int delta = board->getHeight() / threads_count;
	std::cout << "DELTA: " << delta << std::endl;
	int thread_num = -1;
	int last_line_for_thread = 0;
	for (int y = 0; y < board->getHeight(); y++)
	{
		if (last_line_for_thread == y)
		{

			if (thread_num == threads_count - 2)
			{
				last_line_for_thread = board->getHeight();
			}
			else
			{
				if (y + delta <= board->getHeight()) {
					last_line_for_thread = y + delta;
				}
				else
				{
					last_line_for_thread = board->getHeight();
				}
				thread_num++;
			}
			
		}

		for (int x = 0; x < board->getWidth(); x++)
		{
			if (energy->get(x, y) > 0)
			{
				points[thread_num].push_back(Point(x, y));
			}
		}
	}


	auto f = [this](std::vector<Point> points, Board* board, int seed) {

		srand(seed);
		while (points.size() > 0)
		{
			int it = rand() % points.size();
			Point randPoint = points[it];
			if (energy->get(randPoint.x, randPoint.y) != 0)
			{
				std::list<Point>  neighbers = Neighberhood::get_Neighbours(randPoint.x, randPoint.y, board, neighberhoodType::VON_NEUMANN);
				bool a = false;
				std::vector<Point>  neighbers0;
				for (auto neighber : neighbers) {
					if (energy->get(neighber.x, neighber.y) == 0)
					{
						neighbers0.push_back(neighber);
					}
				}

				if (neighbers0.size() > 0)
				{
					double E1 = calculateEnergy(randPoint) + energy->get(randPoint.x, randPoint.y);
					int old = board->get(randPoint);
					Point newState = neighbers0[rand() % neighbers0.size()];
					board->set(randPoint, board->get(newState));
					double E2 = calculateEnergy(randPoint);

					if (E2 - E1 > 0) {
						board->set(randPoint, old);
					}
					else
					{
						energy->set(randPoint.x, randPoint.y, 0);
					}
				}
			}
			points.erase(points.begin() + it);
		}
	};

	std::thread** threads = new std::thread * [threads_count];
	for (int i = 0; i < threads_count; i++)
	{
		threads[i] = new std::thread(f, points[i], board, rand());
	}

	for (int i = 0; i < threads_count; i++)
	{
		threads[i]->join();
		delete threads[i];
	}
	delete threads;
}
