#include <memory>

#include "cgol_window.hpp"
#include "cgol_board.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	std::shared_ptr<CGOLBoard> board = std::make_shared<CGOLBoard>();
	CGOLWindow w{board};
	w.show();
	return a.exec();
}
