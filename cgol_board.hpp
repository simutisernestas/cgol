#ifndef CGOL_BOARD_HPP
#define CGOL_BOARD_HPP

#include <QFrame>
#include <QBasicTimer>
#include <random>
#include "cgol_logic.hpp"

using std::byte;

class CGOLBoard: public QFrame
{
Q_OBJECT

public:
	explicit CGOLBoard(QWidget *parent = nullptr);

public slots:
	void start();
	void setSpeed(int speed);
	void setSize(int size);

protected:
	void paintEvent(QPaintEvent *event) override;
	void timerEvent(QTimerEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;

private:
	int size_; // rectangular board
	QBasicTimer timer_;
	std::vector<byte> board_;
	std::mt19937 rng_;
	std::uniform_int_distribution<std::mt19937::result_type> random_dist_;
	int speed_;
	float scale_;
	QPoint mouse_offset_;
	QPoint panning_vector_;
	float margin_;

	[[nodiscard]] inline float tileWidth() const
	{
		return static_cast<float>(width()) / static_cast<float>(size_);
	}

	[[nodiscard]] inline float tileHeight() const
	{
		return static_cast<float>(height()) / static_cast<float>(size_);
	}

	[[nodiscard]] inline int timeoutTime() const
	{
		return 500 / (speed_ + 1);
	}

	void initEmpty();
	void initRandom();
	void initCheckered();
};

#endif //CGOL_BOARD_HPP
