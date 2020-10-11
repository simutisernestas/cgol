#include <QPainter>
#include <QRgb>
#include <QTimerEvent>
#include <QtGui/QPaintEvent>
#include <utility>

#include "include/cgol_frame.hpp"
#include "include/cgol_logic.hpp"

CGOLFrame::CGOLFrame(std::shared_ptr<CGOLBoard> board_ptr, QWidget *parent)
	: QFrame{parent},
	  scale_{1.0},
	  mouse_offset_{},
	  panning_vector_{},
	  margin_{},
	  board_{std::move(board_ptr)},
	  game_loop_thread_{}
{
	qRegisterMetaType<CGOLBoard>("CGOLBoard");
	connect(&game_loop_thread_, &CGOLLoopThread::boardReady, this, &CGOLFrame::updateBoard);
}

void CGOLFrame::start()
{
	game_loop_thread_.reset(CGOLBoard::State::Random);
}


void CGOLFrame::speedSliderValueChangedCallback(const int &speed)
{
	game_loop_thread_.setSpeed(speed);
}

void CGOLFrame::sizeSliderValueChangedCallback(const int &size)
{
	game_loop_thread_.reset(CGOLBoard::State::Empty, size);
	margin_ = 10.0f / static_cast<float>(size);
	update();
}

void CGOLFrame::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.scale(scale_, scale_);

	int row_offset = std::floor((static_cast<float>(board_->getSize()) * (1 - 1 / scale_)) / 2);
	int col_offset = row_offset;

	int drawn_view_side_len = std::ceil(static_cast<float>(board_->getSize()) / scale_);

	if (scale_ > 1) {
		row_offset = std::clamp(row_offset - panning_vector_.y(), 0, board_->getSize() - drawn_view_side_len);
		col_offset = std::clamp(col_offset - panning_vector_.x(), 0, board_->getSize() - drawn_view_side_len);
	}

	for (int row = row_offset; row < row_offset + drawn_view_side_len; ++row) {
		for (int col = col_offset; col < col_offset + drawn_view_side_len; ++col) {
			auto color = CGOLLogic::isCellAlive(board_, row, col) ? Qt::magenta : Qt::white;

			QRectF tile(static_cast<float>(col - col_offset) * tileWidth() + margin_,
						static_cast<float>(row - row_offset) * tileHeight() + margin_,
						tileWidth() - margin_,
						tileHeight() - margin_);

			painter.fillRect(tile, color);
		}
	}
}

void CGOLFrame::wheelEvent(QWheelEvent *event)
{
	scale_ *= event->delta() < 0 ? 0.95f : 1.05f;
	scale_ = std::clamp(scale_, 1.0f, static_cast<float>(board_->getSize()));
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

float CGOLFrame::tileWidth() const
{
	return static_cast<float>(width()) / static_cast<float>(board_->getSize());
}

float CGOLFrame::tileHeight() const
{
	return static_cast<float>(height()) / static_cast<float>(board_->getSize());
}

void CGOLFrame::updateBoard(CGOLBoard board)
{
	*board_ = std::move(board);
	update();
}

int CGOLFrame::getSpeed() const
{
	return game_loop_thread_.getSpeed();
}
