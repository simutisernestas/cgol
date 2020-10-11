#include <memory>

#include "test_board.hpp"

#include "include/cgol_logic.hpp"

using std::byte;

void TestBoard::test_board_tiles_are_accessible()
{
	CGOLBoard test_board{100, CGOLBoard::State::Empty};
	byte value = test_board.getAt(50, 50);
	QCOMPARE(value, byte{0});
}

void TestBoard::test_board_tiles_are_writable()
{
	CGOLBoard test_board{100, CGOLBoard::State::Empty};
	byte set_value = byte{44};
	int row = 1, col = 2;
	test_board.setAt(set_value, row, col);
	byte get_value = test_board.getAt(row, col);
	QCOMPARE(get_value, set_value);
}

void TestBoard::test_not_initialized_board_throws_exception_if_accessed()
{
	CGOLBoard test_board{}; // initBoard is not called
	// cast to suppress nodiscard compiler warning
	QVERIFY_EXCEPTION_THROWN(static_cast<void>(test_board.getAt(100, 100)), std::out_of_range);
}

void TestBoard::test_not_initialized_board_throws_exception_if_written()
{
	CGOLBoard test_board{}; // initBoard is not called
	QVERIFY_EXCEPTION_THROWN(test_board.setAt(byte{78}, 100, 100), std::out_of_range);
}

void TestBoard::test_board_can_be_initialized_randomly()
{
	std::shared_ptr<CGOLBoard> test_board = std::make_shared<CGOLBoard>();
	int size = 1000;
	test_board->initBoard(size, CGOLBoard::State::Random);
	int alive_sum{};
	for (int row = 0; row < size; ++row)
		for (int col = 0; col < size; ++col)
			if (CGOLLogic::isCellAlive(test_board, row, col))
				++alive_sum;

	QVERIFY(alive_sum > (size * size * 0.4));
	QVERIFY(alive_sum < (size * size * 0.6));
}

void TestBoard::test_board_can_be_initialized_checkered()
{
	std::shared_ptr<CGOLBoard> test_board = std::make_shared<CGOLBoard>();
	int size = 1000;
	test_board->initBoard(size, CGOLBoard::State::Checkered);
	int alive_sum{};
	for (int row = 0; row < size; ++row)
		for (int col = 0; col < size; ++col)
			if (CGOLLogic::isCellAlive(test_board, row, col))
				++alive_sum;

	QVERIFY(alive_sum == ((size * size) / 2));
}

void TestBoard::test_board_access_throws_exception_if_written_out_of_range()
{
	CGOLBoard test_board{14}; // initBoard is not called
	QVERIFY_EXCEPTION_THROWN(test_board.setAt(byte{78}, 100, 100), std::out_of_range);
	QVERIFY_EXCEPTION_THROWN(test_board.setAt(byte{78}, -1, 100), std::out_of_range);
	QVERIFY_EXCEPTION_THROWN(test_board.setAt(byte{78}, 7, -1), std::out_of_range);
}

void TestBoard::test_board_access_throws_exception_if_accessed_out_of_range()
{
	CGOLBoard test_board{13}; // initBoard is not called
	// cast to suppress nodiscard compiler warning
	QVERIFY_EXCEPTION_THROWN(static_cast<void>(test_board.getAt(100, 100)), std::out_of_range);
	QVERIFY_EXCEPTION_THROWN(static_cast<void>(test_board.getAt(100, -5)), std::out_of_range);
	QVERIFY_EXCEPTION_THROWN(static_cast<void>(test_board.getAt(-100, 1)), std::out_of_range);
}

QTEST_MAIN(TestBoard)