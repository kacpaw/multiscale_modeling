#include "BoundaryConditions.h"
#include <iostream>
int BoundaryConditions::get_left(int x, Board* board)
{
	return ((x-1)%board->getWidth() + board->getWidth()) % board->getWidth();
}

int BoundaryConditions::get_right(int x, Board* board)
{
	return ((x + 1) % board->getWidth() + board->getWidth()) % board->getWidth();
}

int BoundaryConditions::get_top(int y, Board* board)
{
	return ((y-1)%board->getHeight() + board->getHeight()) % board->getHeight();
}

int BoundaryConditions::get_bottom(int y, Board* board)
{
	return ((y + 1) % board->getHeight() + board->getHeight()) % board->getHeight();
}

int BoundaryConditions::get_current_x(int x, Board* board)
{
	return (x % board->getWidth() + board->getWidth()) % board->getWidth();
}

int BoundaryConditions::get_current_y(int y, Board* board)
{
	return (y % board->getHeight() + board->getHeight()) % board->getHeight();
}
