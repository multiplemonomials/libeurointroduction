/*
 * LoggingOutputBase.h
 *
 *  Created on: Dec 28, 2013
 *      Author: jamie
 */

#ifndef LOGGINGOUTPUTBASE_H_
#define LOGGINGOUTPUTBASE_H_

#define BOOST_THREAD_DYN_LINK

#include <LogMessage.h>
#include "ThreadSafeQueue.h"
#include <boost/thread/thread.hpp>
#include <boost/foreach.hpp>
#include <memory>
#include <iostream>

class LogOutputBase
{
	//holds all of the messages to be logged
	ThreadSafeQueue<std::shared_ptr<LogMessage>> inputQueue;

	volatile bool _shouldStop;

	//is run in a different thread.
	//(every logger object has its own thread)
	//gets a message out of the queue and then calls acceptMessage, formatMessage, and writeString();
	void run();

	boost::thread _objectThread;

protected:

	/*
	 * These three functions are designed to be overridden by whoever subclasses this base
	 *
	 * acceptMessage returns a boolean that decides whether the output will log this message.
	 * writeMessage converts the message and tags into a string to output and then puts it where it's supposed to go
	 * in the default implementation, writeString actually writes a string to the output
	 */
	virtual bool acceptMessage(std::shared_ptr<LogMessage> messagePtr);

	virtual void writeMessage(std::shared_ptr<LogMessage> messagePtr);

	virtual void writeString(const std::string & text);

public:
	LogOutputBase();

	void enqueueMessage(std::shared_ptr<LogMessage> messagePtr);

	virtual ~LogOutputBase();
};

#endif /* LOGGINGOUTPUTBASE_H_ */
