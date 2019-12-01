#pragma once
#include <list>
#include "Board.h"
#include "Point.h"
#include "BoundaryConditions.h"

enum class neighberhoodType {
	VON_NEUMANN = 0,
	NEAREST_MOORE,
	FURTHER_MOORE,
	MOORE
};

class Neighberhood
{
	static std::list<Point>getVonNeumanNeighbers(int x, int y, Board *board);
	static std::list<Point>getFurtherMoore(int x, int y, Board* board);
	
public:
	static std::list<Point> get_Neighbours(int x, int y, Board *board, neighberhoodType type);
};

