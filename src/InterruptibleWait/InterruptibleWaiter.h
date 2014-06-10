/*
 * InterruptibleWaiter.h
 *
 *  Created on: Jun 9, 2014
 *      Author: jamie
 */

#ifndef INTERRUPTIBLEWAITER_H_
#define INTERRUPTIBLEWAITER_H_

#include <pthread.h>
#include <chrono>
#include <condition_variable>

class InterruptibleWaiter
{

private:

	//used to communicate to the waiting thread that it was interrupted
	volatile bool _wasInterrupted;

	// true if the program is currently waiting on the condition variable
	// so it's not OK to start another block
	volatile bool _isCurrentlyBlocking;

	std::condition_variable _conditionVariable;

	std::mutex _mutex;



public:

	//wait until somebody calls awaken() or block() on the waiter
	void block();

	//wait for the provided time or until interrupt() or awaken() is called
	void wait(unsigned long milliseconds);

	//interrupt the blocking thread if there is one, throwing an interruptedexception
	//returns true if a thread was interrupted, false if not
	bool interrupt();

	//awaken the wating or blocking thread.  Does not throw an interruptedexception
	bool awaken();

	InterruptibleWaiter();

	virtual ~InterruptibleWaiter();
};

#endif /* INTERRUPTIBLEWAITER_H_ */
