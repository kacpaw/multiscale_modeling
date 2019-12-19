#pragma once

#include "Point.h"
#include <list>

class Board
{
	friend class Neighberhood;
protected:
	int** board;
	int width;
	int height;

public:
	Board(size_t width, size_t height);
	Board(const Board& oldBoard);
	Board(int width, int height, int n);
	~Board();
	void set(int x, int y, int value);
	void set(Point point, int value);
	void set(std::list<int> ids, int new_id);
	int get(int x, int y);
	int get(Point point);
	int count(int value);

	void random(std::list<int> ignore, int ids);
	
	void clear(std::list<int> ignore);

	int getWidth();
	int getHeight();
	int** getBoard();
	

};

