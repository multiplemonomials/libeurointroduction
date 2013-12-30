/*
 * LogCore.cpp
 *
 *  Created on: Dec 28, 2013
 *      Author: jamie
 */

#include "LogCore.h"

LogCore::LogCore()
:_loggingCoreMutex(),
 _outputs()
{

}

LogCore& LogCore::instance()
{
	//will be created on first use
	static LogCore localInstance;

	return localInstance;
}

void LogCore::log(LogMessage & message)
{
	for(std::map<std::string, std::shared_ptr<LogOutputBase> >::iterator it = _outputs.begin(); it != _outputs.end(); ++it)
	{
		it->second->enqueueLine(message);
	}
}

void LogCore::addOutput(std::string name, std::shared_ptr<LogOutputBase> output)
{
	_outputs[name] = output;
}

void LogCore::removeOutput(std::string name)
{
	_outputs.erase(name);
}

LogCore::~LogCore()
{

}

