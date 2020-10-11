#ifndef TEST_BOARD_HPP
#define TEST_BOARD_HPP

#include <QTest>

#include "include/cgol_board.hpp"

class TestBoard: public QObject
{
Q_OBJECT

private slots:
	void test_not_initialized_board_throws_exception_if_written();
	void test_not_initialized_board_throws_exception_if_accessed();
	void test_board_tiles_are_writable();
	void test_board_tiles_are_accessible();
	void test_board_can_be_initialized_randomly();
	void test_board_can_be_initialized_checkered();
	void test_board_access_throws_exception_if_accessed_out_of_range();
	void test_board_access_throws_exception_if_written_out_of_range();
};


#endif //TEST_BOARD_HPP
