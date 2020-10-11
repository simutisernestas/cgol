#include <QPainter>
#include <QRgb>
#include <QTimerEvent>
#include <QtGui/QPaintEvent>
#include <utility>

#include "include/cgol_frame.hpp"
#include "include/cgol_logic.hpp"

CGOLFrame::CGOLFrame(std::shared_ptr<CGOLBoard> board_ptr, QWidget *parent)
	: QFrame{parent},
	  speed_{0},
	  scale_{1.0},
	  mouse_offset_{},
	  panning_vector_{},
	  margin_{},
	  board_{std::move(board_ptr)}
{
}

void CGOLFrame::start()
{
	board_->initState(CGOLBoard::State::Random);
	timer_.start(timeoutTime(), this);
}

void CGOLFrame::speedSliderValueChangedCallback(const int &speed)
{
	speed_ = speed;
}

void CGOLFrame::sizeSliderValueChangedCallback(const int &size)
{
	board_->initBoard(size, CGOLBoard::Empty);
	margin_ = std::ceil(100 / static_cast<float>(size));
	update();
}

void CGOLFrame::paintEvent(QPaintEvent *)
{
	static constexpr QRgb black = 0x000000;
	static constexpr QRgb white = 0xffffff;

	QPainter painter(this);
	painter.scale(scale_, scale_);

	int board_size = board_->getSize();
	int row_offset = std::floor((static_cast<float>(board_size) * (1 - 1 / scale_)) / 2);
	int col_offset = row_offset;

	int drawn_view_side_len = std::ceil(static_cast<float>(board_size) / scale_);

	if (scale_ > 1) {
		row_offset = std::clamp(row_offset - panning_vector_.y(), 0, board_size - drawn_view_side_len);
		col_offset = std::clamp(col_offset - panning_vector_.x(), 0, board_size - drawn_view_side_len);
	}

	float tile_width = tileWidth();
	float tile_height = tileHeight();
	for (int row = row_offset; row < row_offset + drawn_view_side_len; ++row) {
		for (int col = col_offset; col < col_offset + drawn_view_side_len; ++col) {
			QRgb rgb = CGOLLogic::isCellAlive(board_, row, col) ? black : white;

			QRectF tile(static_cast<float>(col - col_offset) * tile_width + margin_,
						static_cast<float>(row - row_offset) * tile_height + margin_,
						tile_width - margin_,
						tile_height - margin_);
			painter.fillRect(tile, rgb);
		}
	}
}

void CGOLFrame::timerEvent(QTimerEvent *event)
{
	if (event->timerId() != timer_.timerId()) {
		QFrame::timerEvent(event);
		return;
	}

	CGOLLogic::runGeneration(board_);
	update();
	timer_.start(timeoutTime(), this);
}

void CGOLFrame::wheelEvent(QWheelEvent *event)
{
	scale_ *= event->delta() < 0 ? 0.95f : 1.05f;
	scale_ = std::clamp(scale_, 1.0f, 7.0f);
	update();
}

void CGOLFrame::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton) {
		panning_vector_ = event->pos() - mouse_offset_;
		update();
	}
}

void CGOLFrame::mousePressEvent(QMouseEvent *event)
{
	mouse_offset_ = event->pos();
}

int CGOLFrame::getSpeed() const
{
	return speed_;
}

float CGOLFrame::tileWidth() const
{
	return static_cast<float>(width()) / static_cast<float>(board_->getSize());
}

float CGOLFrame::tileHeight() const
{
	return static_cast<float>(height()) / static_cast<float>(board_->getSize());
}

int CGOLFrame::timeoutTime() const
{
	return 500 / (speed_ + 1);
}


