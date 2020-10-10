#include <QTest>
#include "include/cgol_window.hpp"


class TestGUI: public QObject
{
Q_OBJECT

public:
	TestGUI();

private:
	std::unique_ptr<CGOLWindow> window_;
	std::shared_ptr<CGOLBoard> board_;

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
};
