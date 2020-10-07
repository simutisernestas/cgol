#include "cgol_window.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CGOLWindow w;
	w.show();
	return a.exec();
}
