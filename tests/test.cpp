#include "pch.h"
#include "../staticLib/GrainsBoard.h"
#include "../staticLib/Inclusions.h"

#include <list>


class BoardTest : public Board {

public:

	BoardTest(size_t width, size_t height) :Board(width, height) {}

	void SetBoard(int** board) {

		for (int y = 0; y < this->height; y++) {
			delete this->board[y];
		}
		delete this->board;

		this->board = board;
	}
};



TEST(BoardTest, Board_constructor_positive) {

	Board board(5, 3);

	ASSERT_EQ(board.getWidth(), 5);
	ASSERT_EQ(board.getHeight(), 3);

	int** tab = board.getBoard();

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 5; x++) {
			ASSERT_EQ(tab[y][x], 0);
		}
		delete tab[y];
	}
	delete tab;
}

TEST(BoardTest, Board_copy_constructor_positive) {

	int **tab = new int*[5];
	for (int i = 0; i < 5; i++) {
		tab[i] = new int[3];
	}

	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 3; x++) {
			tab[y][x] = x + y;
		}
	}

	BoardTest board(3, 5);
	board.SetBoard(tab);

	Board copy(board);

	int ** copied = copy.getBoard();

	ASSERT_EQ(copy.getWidth(), 3);
	ASSERT_EQ(copy.getHeight(), 5);

	for (int y = 0; y < copy.getHeight(); y++) {
		for (int x = 0; x < copy.getWidth(); x++) {
			ASSERT_EQ(copied[y][x], x + y);
		}
	}
}

TEST(BoundaryConditionsTest, left) {

	Board board(5,7);
	
	int result1 = BoundaryConditions::get_left(2, &board);
	int result2 = BoundaryConditions::get_left(0, &board);
	int result3 = BoundaryConditions::get_left(-1, &board);
	int result4 = BoundaryConditions::get_left(8, &board);
	
	ASSERT_EQ(result1, 1);
	ASSERT_EQ(result2, 4);
	ASSERT_EQ(result3, 3);
	ASSERT_EQ(result4, 2);
}

TEST(BoundaryConditionsTest, right) {

	Board board(5, 7);

	int result1 = BoundaryConditions::get_right(2, &board);
	int result2 = BoundaryConditions::get_right(4, &board);
	int result3 = BoundaryConditions::get_right(-3, &board);
	int result4 = BoundaryConditions::get_right(8, &board);

	ASSERT_EQ(result1, 3);
	ASSERT_EQ(result2, 0);
	ASSERT_EQ(result3, 3);
	ASSERT_EQ(result4, 4);
}

TEST(BoundaryConditionsTest, top) {

	Board board(5, 7);

	int result1 = BoundaryConditions::get_top(5, &board);
	int result2 = BoundaryConditions::get_top(0, &board);
	int result3 = BoundaryConditions::get_top(-2, &board);
	int result4 = BoundaryConditions::get_top(9, &board);

	ASSERT_EQ(result1, 4);
	ASSERT_EQ(result2, 6);
	ASSERT_EQ(result3, 4);
	ASSERT_EQ(result4, 1);
}

TEST(BoundaryConditionsTest, bottom) {

	Board board(5, 7);

	int result1 = BoundaryConditions::get_bottom(5, &board);
	int result2 = BoundaryConditions::get_bottom(6, &board);
	int result3 = BoundaryConditions::get_bottom(-2, &board);
	int result4 = BoundaryConditions::get_bottom(9, &board);

	ASSERT_EQ(result1, 6);
	ASSERT_EQ(result2, 0);
	ASSERT_EQ(result3, 6);
	ASSERT_EQ(result4, 3);
}


TEST(GrainsBoardTest, add_nucleons_saquare_board_positive) {

	GrainsBoard gb(5, 5);
	std::list<int> ids;

	gb.addNucleons(5);
	int** result1 = gb.getBoard();

	gb.addNucleons(5);
	int** result2 = gb.getBoard();

	for (int y = 0; y < 5; y++) {

		for (int x = 0; x < 5; x++) {
			if (result1[y][x] != 0) {
				EXPECT_TRUE(std::find(ids.begin(), ids.end(), result1[y][x]) == ids.end()) << "Nucleon is duplicated";
				ids.push_back(result1[y][x]);
			}
		}
	}

	ids.clear();

	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			if (result2[y][x] != 0) {
				EXPECT_TRUE(std::find(ids.begin(), ids.end(), result2[y][x]) == ids.end()) << "Nucleon is duplicated";
				ids.push_back(result2[y][x]);
			}
		}
	}

	EXPECT_EQ(ids.size(), 10);


	for (int y = 0; y < 5; y++) {
		delete result1[y];
		delete result2[y];
	}

	delete result1;
	delete result2;

}

TEST(neighberhoodTest, VonNeuman_neighbers_positive) {

	Board board(5, 6);

	std::list<Point> result1 = Neighberhood::get_Neighbours(2, 2, &board, neighberhoodType::VON_NEUMANN);
	std::list<Point> result2 = Neighberhood::get_Neighbours(0, 0, &board, neighberhoodType::VON_NEUMANN);
	std::list<Point> result3 = Neighberhood::get_Neighbours(4, 5, &board, neighberhoodType::VON_NEUMANN);

	std::list<Point> expectedResult1 = { Point{2,1}, Point{3,2}, Point{2,3}, Point{1,2} };
	std::list<Point> expectedResult2 = { Point{0,5}, Point{1,0}, Point{0,1}, Point{4,0} };
	std::list<Point> expectedResult3 = { Point{4,4}, Point{0,5}, Point{4,0}, Point{3,5} };


	ASSERT_EQ(result1.size(), 4);
	ASSERT_EQ(result2.size(), 4);
	ASSERT_EQ(result3.size(), 4);

	auto ir1 = result1.begin(); auto ier1 = expectedResult1.begin();
	auto ir2 = result2.begin(); auto ier2 = expectedResult2.begin();
	auto ir3 = result3.begin(); auto ier3 = expectedResult3.begin();
	for (int i = 0; i < 4; i++) {

		EXPECT_TRUE(*ir1 == *ier1);
		EXPECT_TRUE(*ir2 == *ier2);
		EXPECT_TRUE(*ir3 == *ier3);

		ir1++; ir2++; ir3++;
		ier1++; ier2++; ier3++;
	}
}

TEST(grainsBoardTest, grow_VonNeumann_positive) {

	int** tab = new int* [5];
	for (int i = 0; i < 5; i++) {
		tab[i] = new int[5];
		for (int j = 0; j < 5; j++) {
			tab[i][j] = 0;
		}
	}

	tab[2][2] = 3;

	BoardTest *board = new BoardTest(5, 5);
	board->SetBoard(tab);

	GrainsBoard gb(board);

	gb.grow(growthType::CURVATURE_GROWTH, 1);
	int** result1 = gb.getBoard();

	gb.grow(growthType::CURVATURE_GROWTH, 15);
	int** result2 = gb.getBoard();



	ASSERT_EQ(result1[1][2], 3);
	ASSERT_EQ(result1[2][3], 3);
	ASSERT_EQ(result1[3][2], 3);
	ASSERT_EQ(result1[2][1], 3);
	
	int zeros = 0;
	for (int y = 0; y < 5; y++) {
		for(int x = 0; x < 5; x++) {
			if (result1[y][x] == 0)
				zeros++;
			ASSERT_EQ(result2[y][x], 3);
			std::cout << result2[y][x] << " ";
		}
		std::cout << std::endl;
	}
	ASSERT_EQ(zeros, 20);

}

TEST(InclusionsTest, square_inclusions_before_possitive) {

	for (int k = 0; k < 10; k++)
	{
		BoardTest board(12, 12);
		int** tab = new int* [12];
		for (int i = 0; i < 12; i++) {
			tab[i] = new int[12];
			for (int j = 0; j < 12; j++) {

				if (j < 6)
				{
					tab[i][j] = 2;
				}
				else
				{
					tab[i][j] = 4;
				}
			}
		}

		board.SetBoard(tab);

		Inclusions::addCircleInclusions(1, 5, &board);
		int** result = board.getBoard();
	}
}

TEST(InclusionsTest, square_inclusions_after_possitive) {

}