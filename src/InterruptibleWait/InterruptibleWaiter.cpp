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
 _isCurrentlyBlocking(false),
 _conditionVariable()
{

}

InterruptibleWaiter::~InterruptibleWaiter()
{

}

void InterruptibleWaiter::block()
{
	if(!_isCurrentlyBlocking)
	{
		std::unique_lock<std::mutex> lock(_mutex);

		_isCurrentlyBlocking = true;

		_conditionVariable.wait(lock);

		_isCurrentlyBlocking = false;

		if(_wasInterrupted == true)
		{
			_wasInterrupted = false;
			throw ThreadInterruptedException();
		}
	}
	else
	{
		//error
	}

	return;
}

void InterruptibleWaiter::wait(unsigned long milliseconds)
{
	if(!_isCurrentlyBlocking)
	{
		std::unique_lock<std::mutex> lock(_mutex);

		_isCurrentlyBlocking = true;

		_conditionVariable.wait_for(lock, std::chrono::milliseconds(milliseconds));

		_isCurrentlyBlocking = false;

		if(_wasInterrupted == true)
		{
			_wasInterrupted = false;
			throw ThreadInterruptedException();
		}
	}
	else
	{
		//error
	}

	return;
}

bool InterruptibleWaiter::interrupt()
{
	if(_isCurrentlyBlocking)
	{
		_wasInterrupted = true;
		_conditionVariable.notify_all();
		return true;
	}
	else
	{
		return false;
	}

}

bool InterruptibleWaiter::awaken()
{
	if(_isCurrentlyBlocking)
	{
		_conditionVariable.notify_all();
		return true;
	}
	else
	{
		return false;
	}

}

