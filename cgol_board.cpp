#include "cgol_board.hpp"
#include <QPainter>
#include <QRgb>
#include <QTimerEvent>
#include <QtGui/QPaintEvent>

CGOLBoard::CGOLBoard(QWidget *parent)
	: QFrame{parent},
	  board_{},
	  rng_{std::random_device()()},
	  random_dist_{1, 10},
	  speed_{0},
	  game_logic_{},
	  scale_{1.0}
{
}

void CGOLBoard::start()
{
	initRandom();
	timer_.start(timeoutTime(), this);
}

void CGOLBoard::setSpeed(int speed)
{
	speed_ = speed;
}

void CGOLBoard::initEmpty()
{
	for (bool &i : board_)
		i = false;
}

void CGOLBoard::initRandom()
{
	for (bool &i : board_) {
		auto rand_num = random_dist_(rng_);
		i = (rand_num <= 5);
	}
}

void CGOLBoard::initChess()
{
	for (int i = 0; i < size_; ++i) {
		for (int j = 0; j < size_; ++j) {
			board_[i * size_ + j] = !((i + j) & 1);
		}
	}
}

void CGOLBoard::paintEvent(QPaintEvent *event)
{
	static constexpr QRgb black = 0x000000;
	static constexpr QRgb white = 0xffffff;
	static constexpr int margin = 1;
	QFrame::paintEvent(event);

	QPainter painter(this);
	painter.scale(scale_, scale_);

	for (int i = 0; i < size_; ++i) {
		for (int j = 0; j < size_; ++j) {
			QRgb rgb = board_[i * size_ + j] ? black : white;
			QRectF tile(j * squareWidth() + margin, i * squareHeight() + margin,
						squareWidth() - margin, squareHeight() - margin);
			painter.fillRect(tile, rgb);
		}
	}
}

void CGOLBoard::timerEvent(QTimerEvent *event)
{
	if (event->timerId() != timer_.timerId()) {
		QFrame::timerEvent(event);
		return;
	}

	game_logic_.runGeneration(board_, size_);
	update();
	timer_.start(timeoutTime(), this);
}

void CGOLBoard::wheelEvent(QWheelEvent *event)
{
	QWidget::wheelEvent(event);
	scale_ += (event->delta() / 1200.0);
	scale_ = std::fmin(5.0, std::fmax(1.0, scale_));
	update();
}
