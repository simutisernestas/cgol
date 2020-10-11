#ifndef CGOL_LOOP_THREAD_HPP
#define CGOL_LOOP_THREAD_HPP

#include <QThread>
#include <QMutex>

#include "cgol_board.hpp"

class CGOLLoopThread: public QThread
{
Q_OBJECT

public:
	explicit CGOLLoopThread(QObject *parent = nullptr);
	~CGOLLoopThread() override;

	void reset(CGOLBoard::State state, int size = 0);

	void setSpeed(const int& speed);
	[[nodiscard]] int getSpeed() const;

signals:
	void boardReady(CGOLBoard board);

protected:
	void run() override;

private:
	QMutex mutex_;
	std::shared_ptr<CGOLBoard> board_;
	int speed_;
	bool abort_;

};


#endif //CGOL_LOOP_THREAD_HPP
