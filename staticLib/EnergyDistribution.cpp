#include "EnergyDistribution.h"

EnergyDistribution::EnergyDistribution(int width, int height)
{
	this->width = width;
	this->height = height;

	E = new double* [height];

	for (int y = 0; y < height; y++)
	{
		E[y] = new double[width];

		for (int x = 0; x < width; x++)
		{
			E[y][x] = 1;
		}
	}
}

void EnergyDistribution::distributeEnergy(double energy_inside, double energy_on_edges, Board* board)
{

	if (board == NULL) {

		double deviation_inside = 0.1 * energy_inside;
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				E[y][x] = energy_inside + double(rand() % int(energy_inside*10) * rand() % 2 - 1) * 0.01;
			}
		}
	}
	else
	{
		double deviation_inside = 0.1 * energy_inside;
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				if (board->get(x, y) == -1)
				{
					E[y][x] = energy_on_edges + double((rand() % int(energy_on_edges * 10)) * rand()%2-1)* 0.01;
				}
				else
				{
					E[y][x] = energy_inside + double((rand() % int(energy_inside * 10)) * rand() % 2 - 1)*0.01;
				}
			}
		}
	}
}

double** EnergyDistribution::getBoard()
{
	double** copy = new double* [height];
	for (int y = 0; y < height; y++)
	{
		copy[y] = new double[width];
		for (int x = 0; x < width; x++) {
			copy[y][x] = E[y][x];
		}
	}
	return copy;
}
