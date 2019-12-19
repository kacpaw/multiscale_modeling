#pragma once
#include "Board.h"

class EnergyDistribution
{
	double** E;
	int width;
	int height;

public:
	EnergyDistribution(int width, int height);
	void distributeEnergy(double energy_inside, double energy_on_edges = 0, Board* board = NULL);

	double** getBoard();
	double get(int x, int y) { return E[y][x]; }
	void set(int x, int y, double val){E[y][x] = val;}

};