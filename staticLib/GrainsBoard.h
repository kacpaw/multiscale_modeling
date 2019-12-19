#pragma once

#include <string>

#include "Neighberhood.h"
#include "Board.h"
#include "EnergyDistribution.h"

enum class inclusionsType {
	SQUARE = 0,
	CIRCLE
};

enum class growthType {
	SIMPLE_GROWTH = 0,
	CURVATURE_GROWTH
};

enum class energyDistributionType {
	HOMOGENOUS = 0,
	HETEROGENOUS
};

class GrainsBoard
{

	Board *board;
	int ids_count;
	EnergyDistribution* energy;

	void clear();
	int getBiggestNeighber(std::list<Point> neighbers, std::list<int>without);
	int getBiggestNeighber(std::list<Point> neighbers, int* count);
	int CurvatureGrowth(int x, int y, Board *board2, int propability, std::list<int> without);
	int simpleGrowth(int x, int y, Board* board2, std::list<int> without);
	double calculateEnergy(Point p);
	int calculateEnergy2(Point p);

public:

	GrainsBoard(size_t width, size_t height);
	GrainsBoard(Board *board);
	GrainsBoard(size_t width, size_t height, int n);
	~GrainsBoard();

	void addNucleons(int count);
	void addInclusions(inclusionsType type, int size, int number);
	bool grow(growthType type,int cycles_number = 1, int propability = 80, std::list<int> without = std::list<int>()) ;

	void clear(std::list<int> ignore);
	void setNewColor(std::list<int> ids);

	void allBoundaries();
	void selectedBoundaries(std::list<int> selected);

	void load(std::string path);
	void save(std::string path);

	void fillRandomly(std::list<int> ignore, int n);
	int mc_method(int n);

	int** getBoard();
	double** getEnergy();
	int get(int x, int y);

	void distributeEnergy(energyDistributionType type, double inside, double on_edges = 0);

	void srxmc_add_nucleons(int n, int from);
	void srxmc(int steps);
};