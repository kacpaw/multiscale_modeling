#include "GrainsBoard.h"
#include "Inclusions.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <map>


void GrainsBoard::clear()
{
	delete board;
}

int GrainsBoard::getBiggestNeighber(std::list<Point> neighbers)
{

	std::map<int, int>ids;
	for (auto neighber : neighbers) {
		if ((board->get(neighber)) != 0 && (board->get(neighber)!=-1))
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

	int biggest_neighber = getBiggestNeighber(neighbers);
	if (biggest_neighber != 0)
	{
		if (std::find(without.begin(), without.end(), biggest_neighber) == without.end())
		{
			board2->set(x, y, biggest_neighber);
			return 1;
		}
	}
	return 0;

}


GrainsBoard::GrainsBoard(size_t width, size_t height)
{
	board = new Board(width, height);
	srand(time(NULL));
}

GrainsBoard::GrainsBoard(Board *board)
{
	srand(time(NULL));
	this->board = board;
}

GrainsBoard::GrainsBoard(size_t width, size_t height, int n)
{
	this->board = new Board(width, height, n);
	ids_count = n;
}






GrainsBoard::~GrainsBoard()
{
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
	int finished = ids_count;
	int all = board->getWidth() * board->getHeight();

	for (int i = 0; (i < cycles_number) || (ids_count >= all); i++)
	{
		Board *board2 = new Board(*board);
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

	if(ids_count >= all)
		return true;

	return false;
}

void GrainsBoard::clear(std::list<int> ignore)
{
	board->clear(ignore);
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

int** GrainsBoard::getBoard()
{
	return board->getBoard();
}

int GrainsBoard::get(int x, int y)
{
	return board->get(x, y);
}
