#ifndef CGOL_FRAME_HPP
#define CGOL_FRAME_HPP

#include <random>
#include <memory>

#include <QFrame>
#include <QBasicTimer>

#include "cgol_board.hpp"
#include "cgol_loop_thread.hpp"

using std::byte;

class CGOLFrame: public QFrame
{
Q_OBJECT

public:
	explicit CGOLFrame(std::shared_ptr<CGOLBoard> board_ptr, QWidget *parent = nullptr);
	[[nodiscard]] int getSpeed() const;

public slots:
	void start();
	void speedSliderValueChangedCallback(const int &speed);
	void sizeSliderValueChangedCallback(const int &size);

private slots:
	void updateBoard(CGOLBoard board); // intensional copy

protected:
	void paintEvent(QPaintEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;

private:
	float scale_;
	QPoint mouse_offset_;
	QPoint panning_vector_;
	float margin_;
	std::shared_ptr<CGOLBoard> board_;
	CGOLLoopThread game_loop_thread_;

	[[nodiscard]] float tileHeight() const;
	[[nodiscard]] float tileWidth() const;
};

#endif //CGOL_FRAME_HPP
