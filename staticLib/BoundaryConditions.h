#pragma once

#include "Board.h"


class BoundaryConditions
{

public:
	static int get_left(int x, Board* board);
	static int get_right(int x, Board* board);
	static int get_top(int y, Board* board);
	static int get_bottom(int y, Board* board);

	static int get_current_x(int x, Board *board);
	static int get_current_y(int y, Board* board);
};

