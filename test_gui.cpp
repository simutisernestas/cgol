#include "test_gui.hpp"
#include <QSignalSpy>
#include <QSlider>
#include <QObject>

void TestGUI::testSlider()
{
	auto *slider = w.findChild<QSlider *>("speedSlider");
	QVERIFY(slider != nullptr);

	QSignalSpy spy(slider, SIGNAL(valueChanged(int)));
	QCOMPARE(spy.isValid(), true);

	slider->setValue(55);

	QCOMPARE(w.getSpeed(), 55);
	QCOMPARE(spy.count(), 1);
}

QTEST_MAIN(TestGUI)
