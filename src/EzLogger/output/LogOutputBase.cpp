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

	const LogMessage message = LogMessage(std::string(), LogMessage::TagMapType());

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


		if(!_shouldStop)
		{
			if(acceptMessage(message))
			{
				std::string textMessage = writeMessage(message);
				writeString(textMessage);
			}
		}
	}

	std::cout << "stopping output thread" << std::endl;
}

bool LogOutputBase::acceptMessage(LogMessage & message)
{
	return true;
}

std::string LogOutputBase::writeMessage(LogMessage & message)
{
	std::stringstream stringstream;
	BOOST_FOREACH(LogMessage::TagMapElementType tag, message._tags)
	{
		stringstream << "[" << tag.first << ": " << tag.second->getString() << "] ";
	}

	stringstream << message._textMessage;

	std::cout << message << std::endl;

	return stringstream.str();
}

void LogOutputBase::writeString(std::string message)
{
}

void LogOutputBase::enqueueMessage(LogMessage & message)
{
	inputQueue.Enqueue(message, false);
}
