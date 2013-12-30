/*
 * LoggingOutputBase.cpp
 *
 *  Created on: Dec 28, 2013
 *      Author: jamie
 */

#include <output/LogOutputBase.h>

LogOutputBase::LogOutputBase()
:inputQueue(),
_shouldStop(false),
_objectThread(&LogOutputBase::run, this) //initialize thread IN THE CONSTRUCTOR!!!
	//MUAHAHAHAHAHAAHAHAH
{

}

LogOutputBase::~LogOutputBase()
{
	//in this destructor we have to get the thread out of waiting at its condition_variable.
	//so we Enqueue an empty LogMessage
	_shouldStop = true;

	const LogMessage message = LogMessage(std::string(), std::deque<std::shared_ptr<TagBase> >());

	inputQueue.Enqueue(message, true);

	_objectThread.join();
}

//run by the object's thread
void LogOutputBase::run()
{
	std::cout << "starting output thread" << std::endl;
	while(!_shouldStop)
	{
		//blocks until there is a message
		LogMessage message = inputQueue.Dequeue();

		if(acceptMessage(message))
		{
			std::string textMessage = formatMessage(message);
			writeMessage(textMessage);
		}
	}
}

bool LogOutputBase::acceptMessage(LogMessage & message)
{
	return true;
}

std::string LogOutputBase::formatMessage(LogMessage & message)
{
	std::stringstream stringstream;
	BOOST_FOREACH(std::shared_ptr<TagBase> tag, message._tags)
	{
		stringstream << "[" << tag->getString() << "] ";
	}

	stringstream << message._textMessage;

	return stringstream.str();
}

void LogOutputBase::writeMessage(std::string message)
{
	std::cout << message << std::endl;
}

void LogOutputBase::enqueueLine(LogMessage & message)
{
	inputQueue.Enqueue(message, false);
}
