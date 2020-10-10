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
	  scale_{1.0},
	  mouse_offset_{},
	  panning_vector_{}
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

void CGOLBoard::initCheckered()
{
	for (int i = 0; i < size_; ++i) {
		for (int j = 0; j < size_; ++j) {
			board_[i * size_ + j] = !((i + j) & 1);
		}
	}
}

void CGOLBoard::paintEvent(QPaintEvent *)
{
	static constexpr QRgb black = 0x000000;
	static constexpr QRgb white = 0xffffff;
	static constexpr int margin = 1;

	int dx = std::floor((size_ * (1 - 1 / scale_)) / 2);
	int dy = std::floor((size_ * (1 - 1 / scale_)) / 2);

	int span = std::ceil(size_ / scale_);

	if (scale_ > 1) {
		dx = std::clamp(dx - panning_vector_.y(), 0, size_ - span);
		dy = std::clamp(dy - panning_vector_.x(), 0, size_ - span);
	}

	QPainter painter(this);
	painter.scale(scale_, scale_);
	for (int i = dx; i < dx + span; ++i) {
		for (int j = dy; j < dy + span; ++j) {
			QRgb rgb = board_[i * size_ + j] ? black : white;
			QRectF tile((j - dy) * squareWidth() + margin, (i - dx) * squareHeight() + margin,
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
	scale_ *= event->delta() < 0 ? 0.95f : 1.05f;
	scale_ = std::clamp(scale_, 1.0f, 5.0f);
	update();
}

void CGOLBoard::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton) {
		panning_vector_ = event->pos() - mouse_offset_;
		update();
	}
}

void CGOLBoard::mousePressEvent(QMouseEvent *event)
{
	mouse_offset_ = event->pos();
}
