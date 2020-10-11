#ifndef TESTGAMELOGIC_HPP
#define TESTGAMELOGIC_HPP

#include <QTest>

class TestGameLogic: public QObject
{
Q_OBJECT

private slots:
	void test_rule_1();
	void test_rule_2();
	void test_rule_3();
	void test_rule_4();
};


#endif //TESTGAMELOGIC_HPP
