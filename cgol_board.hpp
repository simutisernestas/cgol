#ifndef CGOL_BOARD_HPP
#define CGOL_BOARD_HPP

#include <QFrame>
#include <QBasicTimer>
#include <random>
#include "cgol_logic.hpp"

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
	void wheelEvent(QWheelEvent *event) override;

private:
	static constexpr int size_ = 10; // square
	static constexpr int area_ = size_ * size_;
	QBasicTimer timer_;
	bool board_[area_];
	std::mt19937 rng_;
	std::uniform_int_distribution<std::mt19937::result_type> random_dist_;
	int speed_;
	CGOLLogic game_logic_;
	float scale_;

	double squareWidth()
	{ return width() / (double)size_; }
	double squareHeight()
	{ return height() / (double)size_; }
	void initEmpty();
	void initRandom();
	void initChess();
	[[nodiscard]] int timeoutTime() const
	{ return 500 / (speed_ + 1); }
};

#endif //CGOL_BOARD_HPP
