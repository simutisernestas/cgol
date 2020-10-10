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
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;

private:
	static constexpr int size_ = 100; // square
	QBasicTimer timer_;
	bool board_[size_ * size_];
	std::mt19937 rng_;
	std::uniform_int_distribution<std::mt19937::result_type> random_dist_;
	int speed_;
	CGOLLogic game_logic_;
	float scale_;
	QPoint mouse_offset_;
	QPoint panning_vector_;

	inline float squareWidth()
	{ return width() / static_cast<float>(size_); }
	inline float squareHeight()
	{ return height() / static_cast<float>(size_); }
	[[nodiscard]] inline int timeoutTime() const
	{ return 500 / (speed_ + 1); }

	void initEmpty();
	void initRandom();
	void initCheckered();
};

#endif //CGOL_BOARD_HPP
