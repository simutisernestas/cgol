#ifndef TEST_GUI_HPP
#define TEST_GUI_HPP

#include <QTest>

#include "include/cgol_window.hpp"

class TestGUI: public QObject
{
Q_OBJECT

private slots:
	void test_game_speed_slider_response_to_signal();
	void test_game_speed_slider_changes_game_frame_speed();
	void test_game_board_size_slider_response_to_signal();
	void test_game_board_size_slider_changes_board_size();
	void test_cgol_frame_exist_in_the_main_window();
	void test_game_speed_slider_exist_in_the_main_window();
	void test_board_size_slider_exist_in_the_main_window();
	void test_start_button_exist_in_the_main_window();
	void test_start_button_initializes_the_game();
	void test_board_is_empty_after_game_size_change();
	void test_board_slider_sets_values_in_expected_range();
	void test_game_speed_slider_sets_values_in_expected_range();
};

#endif //TEST_GUI_HPP
