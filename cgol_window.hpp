#ifndef CGOL_WINDOW_HPP
#define CGOL_WINDOW_HPP

#include <QWidget>
#include "cgol_game.hpp"
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
	explicit CGOLWindow(QWidget *parent = nullptr);
	~CGOLWindow() override;

private slots:
	static void on_speedSlider_valueChanged(int position);

private:
	Ui::CGOLWindow *ui;
	std::unique_ptr<CGOL> cgol;

};
#endif // CGOL_H
