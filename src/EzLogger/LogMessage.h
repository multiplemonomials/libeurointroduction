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
/**
 * A LogMessage contains all of the data for one message that will be written to the log.
 * It can hold an infinite number of tags and one text message
 * LoggerOutput takes care of the formatting
 */
class LogMessage
{
public:
	std::string _textMessage;

	std::deque<std::shared_ptr<TagBase> > _tags;

	LogMessage(std::string message, std::deque<std::shared_ptr<TagBase> > tags);

	virtual ~LogMessage();
};

#endif /* LOGMESSAGE_H_ */
