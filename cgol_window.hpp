#ifndef CGOL_WINDOW_HPP
#define CGOL_WINDOW_HPP

#include <QWidget>
#include "cgol_board.hpp"
#include <memory>
#include <QtWidgets/QPushButton>

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
	explicit CGOLWindow(QWidget *parent = nullptr);
	~CGOLWindow() override;

private:
	Ui::CGOLWindow *ui;
	CGOLBoard *cgol_board_;
};
#endif // CGOL_H
