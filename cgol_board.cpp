#include "cgol_board.hpp"
#include <QPainter>
#include <QRgb>
#include <QTimerEvent>
#include <QtGui/QPaintEvent>
#include <algorithm>

CGOLBoard::CGOLBoard(QWidget *parent)
	: QFrame{parent},
	  size_{},
	  rng_{std::random_device()()},
	  random_dist_{1, 10},
	  speed_{0},
	  scale_{1.0},
	  mouse_offset_{},
	  panning_vector_{},
	  margin_{}
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

void CGOLBoard::setSize(int size)
{
	size_ = size;
	margin_ = std::ceil(100 / static_cast<float>(size_));
	board_.resize(size_ * size_);
	std::fill(board_.begin(), board_.end(), byte{0});
	update();
}

void CGOLBoard::initEmpty()
{
	for (byte &i : board_)
		i = byte{0};
}

void CGOLBoard::initRandom()
{
	for (byte &i : board_) {
		auto rand_num = random_dist_(rng_);
		i = byte{rand_num <= 5};
	}
}

void CGOLBoard::initCheckered()
{
	for (int row = 0; row < size_; ++row) {
		for (int col = 0; col < size_; ++col) {
			board_[row * size_ + col] = byte{!((row + col) & 1)};
		}
	}
}

void CGOLBoard::paintEvent(QPaintEvent *)
{
	static constexpr QRgb black = 0x000000;
	static constexpr QRgb white = 0xffffff;

	QPainter painter(this);
	painter.scale(scale_, scale_);

	int row_offset = std::floor((static_cast<float>(size_) * (1 - 1 / scale_)) / 2);
	int col_offset = row_offset;

	int drawn_view_side_len = std::ceil(static_cast<float>(size_) / scale_); // TODO ceil?

	if (scale_ > 1) {
		row_offset = std::clamp(row_offset - panning_vector_.y(), 0, size_ - drawn_view_side_len);
		col_offset = std::clamp(col_offset - panning_vector_.x(), 0, size_ - drawn_view_side_len);
	}

	float tile_width = tileWidth();
	float tile_height = tileHeight();
	for (int row = row_offset; row < row_offset + drawn_view_side_len; ++row) {
		for (int col = col_offset; col < col_offset + drawn_view_side_len; ++col) {
			QRgb rgb = CGOLLogic::isCellAlive(board_[row * size_ + col]) ? black : white;

			QRectF tile(static_cast<float>(col - col_offset) * tile_width + margin_,
						static_cast<float>(row - row_offset) * tile_height + margin_,
						tile_width - margin_,
						tile_height - margin_);
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

	CGOLLogic::runGeneration(board_, size_);
	update();
	timer_.start(timeoutTime(), this);
}

void CGOLBoard::wheelEvent(QWheelEvent *event)
{
	scale_ *= event->delta() < 0 ? 0.95f : 1.05f;
	scale_ = std::clamp(scale_, 1.0f, 7.0f);
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