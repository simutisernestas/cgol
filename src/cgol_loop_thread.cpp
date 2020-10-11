#include "include/cgol_loop_thread.hpp"
#include "include/cgol_logic.hpp"

#include <QTimerEvent>

CGOLLoopThread::CGOLLoopThread(QObject *parent)
	: QThread(parent),
	  board_{std::make_shared<CGOLBoard>()}, speed_{0}, abort_{false}
{

}
CGOLLoopThread::~CGOLLoopThread()
{
	mutex_.lock();
	abort_ = true;
	mutex_.unlock();

	wait();
}

int CGOLLoopThread::getSpeed() const
{
	return speed_;
}

void CGOLLoopThread::setSpeed(const int &speed)
{
	speed_ = speed;
}

void CGOLLoopThread::run()
{
	forever {
		if (abort_)
			return;
		mutex_.lock();
		CGOLLogic::runGeneration(board_);
		mutex_.unlock();
		emit boardReady(*board_); // copy
		msleep(500 / speed_);
	}
}

void CGOLLoopThread::reset(CGOLBoard::State state, int size)
{
	QMutexLocker locker(&mutex_);

	if (size == 0)
		board_->initState(state);
	else
		board_->initBoard(size, state);

	if (!isRunning())
		start(HighPriority);
}
