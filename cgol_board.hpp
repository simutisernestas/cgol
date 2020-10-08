#ifndef CGOL_BOARD_HPP
#define CGOL_BOARD_HPP

#include <QFrame>
#include <QBasicTimer>
#include <random>

class CGOLBoard: public QFrame
{
Q_OBJECT

public:
	explicit CGOLBoard(QWidget *parent = nullptr);

public slots:
	void start();
	void setSpeed(int speed);

protected:
	void paintEvent(QPaintEvent *event) override;
	void timerEvent(QTimerEvent *event) override;

private:
	static constexpr int size_ = 50; // square
	static constexpr int area_ = size_ * size_;
	QBasicTimer timer_;
	bool board[area_];
	std::mt19937 rng_;
	std::uniform_int_distribution<std::mt19937::result_type> random_dist_;
	int speed_;

	int squareWidth()
	{ return width() / size_; }
	int squareHeight()
	{ return height() / size_; }
	void clearBoard();
	void initBoard();
	void drawSquare(QPainter &painter, int x, int y, QRgb color);
	[[nodiscard]] int timeoutTime() const
	{ return 1000 / (speed_ + 1); }
};

#endif //CGOL_BOARD_HPP
