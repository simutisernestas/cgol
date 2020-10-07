#ifndef CGOL_GAME_HPP
#define CGOL_GAME_HPP

#include <QFrame>
#include <QBasicTimer>

class CGOL: public QFrame
{
Q_OBJECT

public:
	explicit CGOL(QWidget *parent = nullptr);
};

#endif //CGOL_GAME_HPP
