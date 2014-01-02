/*
 * LogMessage.cpp
 *
 *  Created on: Dec 28, 2013
 *      Author: jamie
 */

#include "LogMessage.h"

LogMessage::LogMessage(std::string message, TagMapType tags)
:_textMessage(message),
 _tags(tags)
{

}

LogMessage::~LogMessage()
{

}

