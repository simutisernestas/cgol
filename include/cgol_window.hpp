#ifndef CGOL_WINDOW_HPP
#define CGOL_WINDOW_HPP

#include <QWidget>
#include "cgol_frame.hpp"
#include "cgol_board.hpp"
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui
{
class CGOLWindow;
}
QT_END_NAMESPACE

class CGOLWindow: public QWidget
{
Q_OBJECT

public:
	static const int BOARD_SIZE_RANGE_MIN = 20;
	static const int BOARD_SIZE_RANGE_MAX = 1000;
	static const int BOARD_SIZE_DEFAULT = 50;
	static const int GAME_SPEED_RANGE_MIN = 1;
	static const int GAME_SPEED_RANGE_MAX = 1000;
	static const int GAME_SPEED_DEFAULT = 10;

	explicit CGOLWindow(std::shared_ptr<CGOLBoard> board, QWidget *parent = nullptr);
	~CGOLWindow() override;

private:
	std::unique_ptr<Ui::CGOLWindow> ui_;
	std::shared_ptr<CGOLBoard> cgol_board_;
	std::unique_ptr<CGOLFrame> cgol_frame_;
};
#endif // CGOL_H
