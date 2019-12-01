#include "Inclusions.h"

#include <cstdlib>
#include <time.h>
#include <cmath>

#include "BoundaryConditions.h"


#include <iostream>

void Inclusions::addSquareInclusions(int count, int size, Board* board)
{
	
	if (board->count(0) == 0)
	{
		int added = 0;
		while (added < count) {
			
			int firstId = -1;
			int x, y;
			while (firstId == -1)
			{
				x = rand() % board->getWidth();
				y = rand() % board->getHeight();

				firstId = board->get(x, y);
			}

			int secondId = firstId;
			int checked = 0;
			while ((firstId == secondId) || (checked == board->getWidth() * board->getHeight())) {
				x= BoundaryConditions::get_right(x, board);
				y= BoundaryConditions::get_bottom(y, board);
				secondId = board->get(x, y);
				checked++;
			}
			if (checked == board->getWidth() * board->getHeight())
			{
				return;
			}
			if (secondId == -1)
			{
				continue;
			}

			x = x - size / 2 -1;
			y = y - size / 2 -1;
			int nextX = x;
			int nextY = y;
			for (int i = 0; i < size; i++)
			{
				nextY = BoundaryConditions::get_bottom(nextY, board);
				for (int j = 0; j < size; j++)
				{
					nextX = BoundaryConditions::get_right(nextX, board);
					board->set(nextX, nextY, -1);
				}
				nextX = x;
			}
			added++;
		}

	}
	else
	{
		int added = 0;
		while (added < count) {
			int x = rand() % board->getWidth();
			int y = rand() % board->getHeight();

			int nextX = x;
			int nextY = y;
			for (int i = 0; i < size; i++)
			{
				nextY = BoundaryConditions::get_bottom(nextY, board);
				for (int j = 0; j < size; j++)
				{
					nextX = BoundaryConditions::get_right(nextX, board);
					board->set(nextX, nextY, -1);
				}
				nextX = x;
			}
			added++;
		}
	}
}

void Inclusions::addCircleInclusions(int count, int size, Board* board)
{

	if (board->count(0) == 0)
	{
		int added = 0;
		while (added < count) {

			int firstId = -1;
			int x, y;
			while (firstId == -1)
			{
				x = rand() % board->getWidth();
				y = rand() % board->getHeight();

				firstId = board->get(x, y);
			}

			int secondId = firstId;
			int checked = 0;
			while ((firstId == secondId) || (checked == board->getWidth() * board->getHeight())) {
				x = BoundaryConditions::get_right(x, board);
				y = BoundaryConditions::get_bottom(y, board);
				secondId = board->get(x, y);
				checked++;
			}
			if (checked == board->getWidth() * board->getHeight())
			{
				return;
			}
			if (secondId == -1)
			{
				continue;
			}

			int x_centre = x-1;
			int y_centre = y-1;
			x = x - size / 2 - 1;
			y = y - size / 2 - 1;
			int nextX = x;
			int nextY = y;
			for (int i = 0; i < size; i++)
			{
				nextY ++;
				for (int j = 0; j < size; j++)
				{
					nextX++;

					if (sqrt(pow(double(x_centre - nextX), 2) + pow(double(y_centre - nextY), 2)) <= size / 2)
					{
						board->set(BoundaryConditions::get_current_x(nextX, board), BoundaryConditions::get_current_y(nextY, board), -1);
					}
				}
				nextX = x;
			}
			added++;
		}

	}
	else
	{
		int added = 0;
		while (added < count) {
			int x = rand() % board->getWidth();
			int y = rand() % board->getHeight();

			int nextX = x;
			int nextY = y;
			int x_center = x + 1 + size / 2;
			int y_center = y + 1 + size / 2;

			for (int i = 0; i < size; i++)
			{
				nextY++;
				for (int j = 0; j < size; j++)
				{
					nextX++;
					if (sqrt(pow(double(x_center - nextX), 2) + pow(double(y_center - nextY), 2)) <= size / 2)
					{
						board->set(BoundaryConditions::get_current_x(nextX, board), BoundaryConditions::get_current_y(nextY, board), -1);
					}
				}
				nextX = x;
			}
			added++;
		}
	}
}
