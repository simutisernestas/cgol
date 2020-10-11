#include "test_game_logic.hpp"

#include "include/cgol_logic.hpp"
#include "include/cgol_board.hpp"

static int count_alive_cells(const std::shared_ptr<CGOLBoard> &board)
{
	int alive_sum{};

	for (int row = 0; row < board->getSize(); ++row)
		for (int col = 0; col < board->getSize(); ++col)
			if (CGOLLogic::isCellAlive(board, row, col))
				++alive_sum;

	return alive_sum;
}

void TestGameLogic::test_rule_1()
{
	// Any live cell with fewer than two live neighbours dies, as if by underpopulation.
	int size = 2; // 2x2 board
	std::shared_ptr<CGOLBoard> test_board = std::make_shared<CGOLBoard>(size, CGOLBoard::Empty);

	// single cell alive
	test_board->setAt(CGOLLogic::CELL_ALIVE, 0, 0);
	CGOLLogic::runGeneration(test_board);

	// dies by underpopulation
	QCOMPARE(count_alive_cells(test_board), 0);

	// two neighbour cells alive
	test_board->setAt(CGOLLogic::CELL_ALIVE, 1, 1);
	test_board->setAt(CGOLLogic::CELL_ALIVE, 1, 0);
	CGOLLogic::runGeneration(test_board);

	// dies by underpopulation
	QCOMPARE(count_alive_cells(test_board), 0);
}

void TestGameLogic::test_rule_2()
{
	// Any live cell with two or three live neighbours lives on to the next generation.
	int size = 5; // 5x5 board
	std::shared_ptr<CGOLBoard> test_board = std::make_shared<CGOLBoard>(size,CGOLBoard::Empty);

	// three neighbour cells alive
	std::pair<int,int> cell_1 = {1,1};
	std::pair<int,int> cell_2 = {1,0};
	std::pair<int,int> cell_3 = {0,1};
	test_board->setAt(CGOLLogic::CELL_ALIVE, cell_1.first, cell_1.second);
	test_board->setAt(CGOLLogic::CELL_ALIVE, cell_2.first, cell_2.second);
	test_board->setAt(CGOLLogic::CELL_ALIVE, cell_3.first, cell_3.second);
	CGOLLogic::runGeneration(test_board);

	// at least three lives on
	QVERIFY(count_alive_cells(test_board) >= 3);
	// specific ones are alive
	QVERIFY(CGOLLogic::isCellAlive(test_board, cell_1.first, cell_1.second));
	QVERIFY(CGOLLogic::isCellAlive(test_board, cell_2.first, cell_2.second));
	QVERIFY(CGOLLogic::isCellAlive(test_board, cell_3.first, cell_3.second));
}

void TestGameLogic::test_rule_3()
{
	// Any live cell with more than three live neighbours dies, as if by overpopulation.
	int size = 5; // 5x5 board
	std::shared_ptr<CGOLBoard> test_board = std::make_shared<CGOLBoard>(size,CGOLBoard::Empty);

	// four neighbour cells alive around one
	std::pair<int,int> cell_1 = {2,3};
	std::pair<int,int> cell_2 = {2,1};
	std::pair<int,int> cell_3 = {3,2};
	std::pair<int,int> cell_4 = {1,2};
	std::pair<int,int> center_cell = {2,2};
	test_board->setAt(CGOLLogic::CELL_ALIVE, cell_1.first, cell_1.second);
	test_board->setAt(CGOLLogic::CELL_ALIVE, cell_2.first, cell_2.second);
	test_board->setAt(CGOLLogic::CELL_ALIVE, cell_3.first, cell_3.second);
	test_board->setAt(CGOLLogic::CELL_ALIVE, cell_4.first, cell_4.second);
	test_board->setAt(CGOLLogic::CELL_ALIVE, center_cell.first, center_cell.second);
	CGOLLogic::runGeneration(test_board);

	QVERIFY(!CGOLLogic::isCellAlive(test_board, center_cell.first, center_cell.second));
}

void TestGameLogic::test_rule_4()
{
	// Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

	int size = 5; // 5x5 board
	std::shared_ptr<CGOLBoard> test_board = std::make_shared<CGOLBoard>(size,CGOLBoard::Empty);

	// three neighbour cells alive
	std::pair<int,int> cell_1 = {2,2};
	std::pair<int,int> cell_2 = {2,1};
	std::pair<int,int> cell_3 = {1,2};
	test_board->setAt(CGOLLogic::CELL_ALIVE, cell_1.first, cell_1.second);
	test_board->setAt(CGOLLogic::CELL_ALIVE, cell_2.first, cell_2.second);
	test_board->setAt(CGOLLogic::CELL_ALIVE, cell_3.first, cell_3.second);
	CGOLLogic::runGeneration(test_board);

	std::pair<int,int> cell_surrounded_by_3 = {1,1};

	// fourth one must become live, by reproduction
	QVERIFY(count_alive_cells(test_board) == 4);
	// specific one is alive
	QVERIFY(CGOLLogic::isCellAlive(test_board, cell_surrounded_by_3.first, cell_surrounded_by_3.second));
}

QTEST_MAIN(TestGameLogic)
