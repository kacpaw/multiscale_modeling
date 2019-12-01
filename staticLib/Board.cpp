#include "Board.h"

#include <ctime>

Board::Board(size_t width, size_t height)
{
	board = new int* [height];
	for (int y = 0; y < height; y++)
	{
		board[y] = new int[width];
		for (int x = 0; x < width; x++)
		{
			board[y][x] = 0;
		}
	}

	this->width = width;
	this->height = height;
}

Board::Board(const Board& oldBoard)
{
	
	this->board = new int* [oldBoard.height];
	for (int i = 0; i < oldBoard.height; i++) {
		this->board[i] = new int[oldBoard.width];

		for (int j = 0; j < oldBoard.width; j++)
		{
			this->board[i][j] = oldBoard.board[i][j];
		}
	}

	this->width = oldBoard.width;
	this->height = oldBoard.height;
}

Board::Board(int width, int height, int n)
{
	srand (time(NULL));

	board = new int* [height];
	for (int y = 0; y < height; y++)
	{
		board[y] = new int[width];
		for (int x = 0; x < width; x++)
		{
			board[y][x] = rand()%n;
		}
	}

	this->width = width;
	this->height = height;
}

Board::~Board()
{
	for (int y = 0; y < height; y++) {
		delete board[y];
	}
	delete board;
}

void Board::set(int x, int y, int value)
{
	board[y][x] = value;
}

void Board::set(Point point, int value)
{
	board[point.y][point.x] = value;
}

int Board::get(int x, int y)
{
	return board[y][x];
}

int Board::get(Point point)
{
	return board[point.y][point.x];
}

int Board::count(int value)
{
	int n = 0;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			if (board[y][x] == value) {
				n++;
			}
		}
	}
	return n;
}

void Board::clear(std::list<int> ignore)
{
	ignore.push_back(-1);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (std::find(ignore.begin(), ignore.end(), board[y][x]) == ignore.end()) {
				board[y][x] = 0;
			}
		}
	}
}

int Board::getWidth()
{
	return width;
}

int Board::getHeight()
{
	return height;
}

int** Board::getBoard()
{
	int** board_copy = new int* [height];
	for (int i = 0; i < height; i++) {
		board_copy[i] = new int[width];

		for (int j = 0; j < width; j++)
		{
			board_copy[i][j] = board[i][j];
		}
	}

	return board_copy;
}
