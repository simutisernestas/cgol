#include "test_gui.hpp"
#include "include/cgol_logic.hpp"

#include <QSignalSpy>
#include <QSlider>
#include <QPushButton>

void TestGUI::test_cgol_frame_exist_in_the_main_window()
{
	auto board_ = std::make_shared<CGOLBoard>();
	auto window_ = std::make_shared<CGOLWindow>(board_);

	auto *frame = window_->findChild<CGOLFrame *>();
	QVERIFY(frame != nullptr);
}

void TestGUI::test_game_speed_slider_exist_in_the_main_window()
{
	auto board_ = std::make_shared<CGOLBoard>();
	auto window_ = std::make_shared<CGOLWindow>(board_);

	auto *slider = window_->findChild<QSlider *>("speedSlider");
	QVERIFY(slider != nullptr);
}

void TestGUI::test_board_size_slider_exist_in_the_main_window()
{
	auto board_ = std::make_shared<CGOLBoard>();
	auto window_ = std::make_shared<CGOLWindow>(board_);

	auto *slider = window_->findChild<QSlider *>("boardSizeSlider");
	QVERIFY(slider != nullptr);
}

void TestGUI::test_game_speed_slider_response_to_signal()
{
	auto board_ = std::make_shared<CGOLBoard>();
	auto window_ = std::make_shared<CGOLWindow>(board_);

	auto *slider = window_->findChild<QSlider *>("speedSlider");

	// listen for signal
	QSignalSpy spy(slider, SIGNAL(valueChanged(int)));
	QCOMPARE(spy.isValid(), true);

	// emit action
	int value = 1;
	slider->setValue(value);

	// action recorded
	QCOMPARE(spy.count(), 1);

	// correct value recorded
	QList<QVariant> arguments = spy.takeFirst();
	QVERIFY(arguments.at(0).toInt() == value);
}

void TestGUI::test_game_speed_slider_changes_game_frame_speed()
{
	auto board_ = std::make_shared<CGOLBoard>();
	auto window_ = std::make_shared<CGOLWindow>(board_);

	auto *slider = window_->findChild<QSlider *>("speedSlider");

	// listen for signal
	QSignalSpy spy(slider, SIGNAL(valueChanged(int)));
	QCOMPARE(spy.isValid(), true);

	// emit action
	int value = 12;
	slider->setValue(value);

	// frame has correct speed value
	auto *frame = window_->findChild<CGOLFrame *>();
	QCOMPARE(frame->getSpeed(), value);
}

void TestGUI::test_game_board_size_slider_response_to_signal()
{
	auto board_ = std::make_shared<CGOLBoard>();
	auto window_ = std::make_shared<CGOLWindow>(board_);

	auto *slider = window_->findChild<QSlider *>("boardSizeSlider");

	// listen for signal
	QSignalSpy spy(slider, SIGNAL(valueChanged(int)));
	QCOMPARE(spy.isValid(), true);

	// emit action
	int value = 87;
	slider->setValue(value);
	// action recorded
	QCOMPARE(spy.count(), 1);

	// correct value recorded
	QList<QVariant> arguments = spy.takeFirst();
	QVERIFY(arguments.at(0).toInt() == value);
}

void TestGUI::test_game_board_size_slider_changes_board_size()
{
	auto board_ = std::make_shared<CGOLBoard>();
	auto window_ = std::make_shared<CGOLWindow>(board_);

	auto *slider = window_->findChild<QSlider *>("boardSizeSlider");

	// listen for signal
	QSignalSpy spy(slider, SIGNAL(valueChanged(int)));
	QCOMPARE(spy.isValid(), true);

	// emit action
	int value = 88;
	slider->setValue(value);

	// start game loop thread to update the board
	auto *button = window_->findChild<QPushButton *>("startButton");
	button->click();
	QTest::qWait(200);

	// board is proper size
	QCOMPARE(board_->getSize(), value);
}

void TestGUI::test_start_button_exist_in_the_main_window()
{
	auto board_ = std::make_shared<CGOLBoard>();
	auto window_ = std::make_shared<CGOLWindow>(board_);

	auto *button = window_->findChild<QPushButton *>("startButton");
	QVERIFY(button != nullptr);
}

void TestGUI::test_start_button_initializes_the_game()
{
	auto board_ = std::make_shared<CGOLBoard>();
	auto window_ = std::make_shared<CGOLWindow>(board_);

	auto *button = window_->findChild<QPushButton *>("startButton");

	// listen for signal
	QSignalSpy spy(button, SIGNAL(clicked()));
	QCOMPARE(spy.isValid(), true);

	button->click();
	QTest::qWait(100);

	bool have_at_least_one_alive_cell = false;

	for (int row = 0; row < board_->getSize(); ++row) {
		for (int col = 0; col < board_->getSize(); ++col) {
			if (!CGOLLogic::isCellAlive(board_, row, col))
				continue;
			have_at_least_one_alive_cell = true;
			break;
		}
		if (have_at_least_one_alive_cell) break;
	}

	QCOMPARE(have_at_least_one_alive_cell, true);
}

void TestGUI::test_board_is_empty_after_game_size_change()
{
	auto board_ = std::make_shared<CGOLBoard>();
	auto window_ = std::make_shared<CGOLWindow>(board_);

	auto *slider = window_->findChild<QSlider *>("boardSizeSlider");

	// listen for signal
	QSignalSpy spy(slider, SIGNAL(valueChanged(int)));
	QCOMPARE(spy.isValid(), true);

	// emit action
	slider->setValue(88);
	// action recorded
	QCOMPARE(spy.count(), 1);

	bool have_at_least_one_alive_cell = false;

	for (int row = 0; row < board_->getSize(); ++row) {
		for (int col = 0; col < board_->getSize(); ++col) {
			if (!CGOLLogic::isCellAlive(board_, row, col))
				continue;
			have_at_least_one_alive_cell = true;
			break;
		}
		if (have_at_least_one_alive_cell) break;
	}

	QCOMPARE(have_at_least_one_alive_cell, false);
}

void TestGUI::test_board_slider_sets_values_in_expected_range()
{
	auto board_ = std::make_shared<CGOLBoard>();
	auto window_ = std::make_shared<CGOLWindow>(board_);

	auto *slider = window_->findChild<QSlider *>("boardSizeSlider");

	// listen for signal
	QSignalSpy spy(slider, SIGNAL(valueChanged(int)));
	QCOMPARE(spy.isValid(), true);

	int max = CGOLWindow::BOARD_SIZE_RANGE_MAX;
	int min = CGOLWindow::BOARD_SIZE_RANGE_MIN;

	// set value out of range
	slider->setValue(max + 100);
	// action recorded
	QCOMPARE(spy.count(), 1);

	// start game loop thread to update the board
	auto *button = window_->findChild<QPushButton *>("startButton");
	button->click();
	QTest::qWait(400);

	// value is clipped
	QCOMPARE(board_->getSize(), max);

	// set value out of range
	slider->setValue(min - 100);
	// action recorded
	QCOMPARE(spy.count(), 2);

	// start game loop thread to update the board
	button->click();
	QTest::qWait(100);

	// value is clipped
	QCOMPARE(board_->getSize(), min);
}

void TestGUI::test_game_speed_slider_sets_values_in_expected_range()
{
	auto board_ = std::make_shared<CGOLBoard>();
	auto window_ = std::make_shared<CGOLWindow>(board_);

	auto *slider = window_->findChild<QSlider *>("speedSlider");
	auto *frame = window_->findChild<CGOLFrame *>();
	QVERIFY(frame != nullptr);

	// listen for signal
	QSignalSpy spy(slider, SIGNAL(valueChanged(int)));
	QCOMPARE(spy.isValid(), true);

	int max = CGOLWindow::GAME_SPEED_RANGE_MAX;
	int min = CGOLWindow::GAME_SPEED_RANGE_MIN;

	// set value out of range
	slider->setValue(max + 100);
	// action recorded
	QCOMPARE(spy.count(), 1);
	// value is clipped
	QCOMPARE(frame->getSpeed(), max);

	// set value out of range
	slider->setValue(min - 100);
	// action recorded
	QCOMPARE(spy.count(), 2);
	// value is clipped
	QCOMPARE(frame->getSpeed(), min);
}

QTEST_MAIN(TestGUI)
