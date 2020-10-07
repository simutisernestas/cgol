#include <QTest>
#include "cgol_window.hpp"


class TestGUI: public QObject
{
Q_OBJECT

private:
	CGOLWindow w;

private slots:
	void testSlider();
};
