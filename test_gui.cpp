#include "test_gui.hpp"
#include "cgol_logic.hpp"

#include <QSignalSpy>
#include <QSlider>
#include <QPushButton>

TestGUI::TestGUI()
{
	board_ = std::make_shared<CGOLBoard>();
	window_ = std::make_unique<CGOLWindow>(board_);
}

void TestGUI::test_cgol_frame_exist_in_the_main_window()
{
	auto *frame = window_->findChild<CGOLFrame *>();
	QVERIFY(frame != nullptr);
}

void TestGUI::test_game_speed_slider_exist_in_the_main_window()
{
	auto *slider = window_->findChild<QSlider *>("speedSlider");
	QVERIFY(slider != nullptr);
}

void TestGUI::test_board_size_slider_exist_in_the_main_window()
{
	auto *slider = window_->findChild<QSlider *>("boardSizeSlider");
	QVERIFY(slider != nullptr);
}

void TestGUI::test_game_speed_slider_response_to_signal()
{
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
	auto *slider = window_->findChild<QSlider *>("boardSizeSlider");

	// listen for signal
	QSignalSpy spy(slider, SIGNAL(valueChanged(int)));
	QCOMPARE(spy.isValid(), true);

	// emit action
	int value = 88;
	slider->setValue(value);

	// board is proper size
	QCOMPARE(board_->getSize(), value);
}

void TestGUI::test_start_button_exist_in_the_main_window()
{
	auto *button = window_->findChild<QPushButton *>("startButton");
	QVERIFY(button != nullptr);
}

void TestGUI::test_start_button_initializes_the_game()
{
	auto *button = window_->findChild<QPushButton *>("startButton");

	// listen for signal
	QSignalSpy spy(button, SIGNAL(clicked()));
	QCOMPARE(spy.isValid(), true);

	button->click();

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

QTEST_MAIN(TestGUI)
