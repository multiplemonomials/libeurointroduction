/*
 * LogMessage.h
 *
 *  Created on: Dec 28, 2013
 *      Author: jamie
 */

#ifndef LOGMESSAGE_H_
#define LOGMESSAGE_H_

#include "tags/TagBase.h"
#include <memory>
#include <queue>
#include <map>
/**
 * A LogMessage contains all of the data for one message that will be written to the log.
 * It can hold an infinite number of tags and one text message
 * LoggerOutput takes care of the formatting
 */
class LogMessage
{
public:
	std::string _textMessage;

	typedef std::map<std::string, std::shared_ptr<TagBase>> TagMapType;
	typedef std::pair<std::string, std::shared_ptr<TagBase>> TagMapElementType;
	TagMapType _tags;

	LogMessage(std::string message, TagMapType tags);

	std::ost

	virtual ~LogMessage();
};

#endif /* LOGMESSAGE_H_ */
