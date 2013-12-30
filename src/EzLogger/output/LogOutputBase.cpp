/*
 * LoggingOutputBase.cpp
 *
 *  Created on: Dec 28, 2013
 *      Author: jamie
 */

#include <output/LogOutputBase.h>

LogOutputBase::LogOutputBase()
:inputQueue()
{
	boost::thread objectThread(&LogOutputBase::run, this); //initialize thread IN THE CONSTRUCTOR!!!
	//MUAHAHAHAHAHAAHAHAH
}

LogOutputBase::~LogOutputBase()
{
	// TODO Auto-generated destructor stub
}

//run by the object's thread
void LogOutputBase::run()
{
	std::cout << "starting output thread" << std::endl;
	while(true)
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
