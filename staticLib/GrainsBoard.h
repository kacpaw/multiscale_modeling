#pragma once

#include <string>

#include "Neighberhood.h"
#include "Board.h"

enum class inclusionsType {
	SQUARE = 0,
	CIRCLE
};

enum class growthType {
	SIMPLE_GROWTH = 0,
	CURVATURE_GROWTH
};

class GrainsBoard
{

	Board *board;
	int ids_count;

	void clear();
	int getBiggestNeighber(std::list<Point> neighbers);
	int getBiggestNeighber(std::list<Point> neighbers, int* count);
	int CurvatureGrowth(int x, int y, Board *board2, int propability, std::list<int> without);
	int simpleGrowth(int x, int y, Board* board2, std::list<int> without);

public:

	GrainsBoard(size_t width, size_t height);
	GrainsBoard(Board *board);
	GrainsBoard(size_t width, size_t height, int n);
	~GrainsBoard();

	void addNucleons(int count);
	void addInclusions(inclusionsType type, int size, int number);
	bool grow(growthType type,int cycles_number = 1, int propability = 80, std::list<int> without = std::list<int>()) ;

	void clear(std::list<int> ignore);

	void allBoundaries();
	void selectedBoundaries(std::list<int> selected);

	void load(std::string path);
	void save(std::string path);

	int** getBoard();
	int get(int x, int y);
};