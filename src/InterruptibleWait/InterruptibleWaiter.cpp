/*
 * InterruptibleWaiter.cpp
 *
 *  Created on: Jun 9, 2014
 *      Author: jamie
 */

#include <InterruptibleWait/InterruptibleWaiter.h>
#include <InterruptibleWait/ThreadInterruptedException.h>

InterruptibleWaiter::InterruptibleWaiter()
:_wasInterrupted(false),
 _conditionVariable()
{

}

InterruptibleWaiter::~InterruptibleWaiter()
{

}

void InterruptibleWaiter::block()
{
	std::unique_lock<std::mutex> lock(_mutex);

	_conditionVariable.wait(lock);

	if(_wasInterrupted == true)
	{
		_wasInterrupted = false;
		throw ThreadInterruptedException();
	}

	return;
}

void InterruptibleWaiter::block(std::unique_lock<std::mutex> & callersLock)
{
	callersLock.unlock();

	block();

	callersLock.lock();

	return;
}

bool InterruptibleWaiter::wait(Time::Duration duration)
{
	std::unique_lock<std::mutex> lock(_mutex);

	std::cv_status waitResult = _conditionVariable.wait_until(lock, Time::TimepointToChrono(Time::GetTime() + duration));

	if(_wasInterrupted == true)
	{
		_wasInterrupted = false;
		throw ThreadInterruptedException();
	}

	return waitResult == std::cv_status::timeout;
}

void InterruptibleWaiter::interrupt()
{
	_wasInterrupted = true;
	_conditionVariable.notify_one();
}

void InterruptibleWaiter::awaken()
{
	_conditionVariable.notify_one();

}

