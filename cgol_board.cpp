#include "cgol_board.hpp"
#include <QPainter>
#include <QRgb>
#include <QTimerEvent>
#include <QtGui/QPaintEvent>

CGOLBoard::CGOLBoard(QWidget *parent)
	: QFrame(parent),
	  board{},
	  rng_{std::random_device()()},
	  random_dist_{1, 10},
	  speed_{0}
{
}

void CGOLBoard::clearBoard()
{
	for (bool &i : board)
		i = false;
}

void CGOLBoard::initBoard()
{
	for (bool &i : board) {
		auto rand_num = random_dist_(rng_);
		i = (rand_num <= 5);
	}
}

void CGOLBoard::drawSquare(QPainter &painter, int x, int y, QRgb rgb)
{
	auto color = QColor(rgb);
	painter.fillRect(x + 1, y + 1, squareWidth() - 2, squareHeight() - 2, color);

	painter.setPen(color.lighter());
	painter.drawLine(x, y + squareHeight() - 1, x, y);
	painter.drawLine(x, y, x + squareWidth() - 1, y);

	painter.setPen(color.darker());
	painter.drawLine(x + 1, y + squareHeight() - 1,
					 x + squareWidth() - 1, y + squareHeight() - 1);
	painter.drawLine(x + squareWidth() - 1, y + squareHeight() - 1,
					 x + squareWidth() - 1, y + 1);
}

void CGOLBoard::paintEvent(QPaintEvent *event)
{
	static constexpr QRgb black = 0x000000;
	static constexpr QRgb white = 0xffffff;

	QFrame::paintEvent(event);

	QPainter painter(this);
	QRect rect = contentsRect();

	int boardTop = rect.bottom() - size_ * squareHeight();

	for (int i = 0; i < size_; ++i) {
		for (int j = 0; j < size_; ++j) {
			QRgb rgb = board[i * j] ? black : white;

			drawSquare(
				painter,
				rect.left() + j * squareWidth(),
				boardTop + i * squareHeight(),
				rgb
			);
		}
	}
}

void CGOLBoard::timerEvent(QTimerEvent *event)
{
	if (event->timerId() != timer_.timerId()) {
		QFrame::timerEvent(event);
		return;
	}

	// TODO: step?
	update();
	timer_.start(timeoutTime(), this);

}

void CGOLBoard::start()
{
	clearBoard();
	initBoard();
	timer_.start(timeoutTime(), this);
}

void CGOLBoard::setSpeed(int speed)
{
	speed_ = speed;
}
