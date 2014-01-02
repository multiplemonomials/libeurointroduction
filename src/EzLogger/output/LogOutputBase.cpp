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
	//MUAHAHAHAHAHAHAHAH
{

}

LogOutputBase::~LogOutputBase()
{
	//in this destructor we have to get the thread out of waiting at its condition_variable.
	//so we Enqueue an empty LogMessage
	_shouldStop = true;

	std::shared_ptr<LogMessage> message(new LogMessage({{"foo", "bar"}}));

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
		std::shared_ptr<LogMessage> messagePtr = inputQueue.Dequeue();


		if(!_shouldStop)
		{
			if(acceptMessage(messagePtr))
			{
				writeMessage(messagePtr);
			}
		}
	}

	std::cout << "stopping output thread" << std::endl;
}

bool LogOutputBase::acceptMessage(std::shared_ptr<LogMessage> messagePtr)
{
	return true;
}

void LogOutputBase::writeMessage(std::shared_ptr<LogMessage> messagePtr)
{
	std::ostringstream ostringstream;
	BOOST_FOREACH(LogMessage::TagMapElementType tag, messagePtr->getTags())
	{
		ostringstream << "[" << tag.first << ": " << tag.second << "] ";
	}

	ostringstream << messagePtr->getStream().str();

	writeString(ostringstream.str());
}

void LogOutputBase::writeString(const std::string & text)
{
	std::cout << text << std::endl;
}

void LogOutputBase::enqueueMessage(std::shared_ptr<LogMessage> messagePtr)
{
	inputQueue.Enqueue(messagePtr, false);
}
