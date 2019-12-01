#include "Neighberhood.h"


std::list<Point> Neighberhood::getVonNeumanNeighbers(int x, int y, Board* board)
{

	std::list<Point> neighbours;

	neighbours.push_back(Point{ x, BoundaryConditions::get_top(y, board) });
	neighbours.push_back(Point{ BoundaryConditions::get_right(x, board), y });
	neighbours.push_back(Point{ x, BoundaryConditions::get_bottom(y, board) });
	neighbours.push_back(Point{BoundaryConditions::get_left(x, board), y});

	return neighbours;
}

std::list<Point> Neighberhood::getFurtherMoore(int x, int y, Board* board)
{
	std::list<Point> neighbours;

	neighbours.push_back(Point{ BoundaryConditions::get_left(x, board), BoundaryConditions::get_top(y, board) });
	neighbours.push_back(Point{ BoundaryConditions::get_right(x, board), BoundaryConditions::get_top(y, board) });
	neighbours.push_back(Point{ BoundaryConditions::get_right(x, board), BoundaryConditions::get_bottom(y, board) });
	neighbours.push_back(Point{ BoundaryConditions::get_left(x, board), BoundaryConditions::get_bottom(y, board) });

	return neighbours;
}

std::list<Point> Neighberhood::get_Neighbours(int x, int y, Board* board, neighberhoodType type)
{
	switch (type) {
	case neighberhoodType::VON_NEUMANN:
		return getVonNeumanNeighbers(x, y, board);
	case neighberhoodType::NEAREST_MOORE:
		return getVonNeumanNeighbers(x, y, board);
	case neighberhoodType::FURTHER_MOORE:
		return getFurtherMoore(x, y, board);
	case neighberhoodType::MOORE:
		std::list<Point> neighbours = getVonNeumanNeighbers(x, y, board);
		std::list<Point> neighbours2 = getFurtherMoore(x, y, board);
		neighbours.splice(neighbours.end(), neighbours2);
		return neighbours;
	}

	return std::list<Point>();
}