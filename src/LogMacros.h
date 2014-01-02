/*
 * LogHolder.h
 *
 *  Created on: Jan 1, 2014
 *      Author: jamie
 */

#ifndef LOGHOLDER_H_
#define LOGHOLDER_H_

#include <LogMessage.h>
#include <LogCore.h>
#include <memory>
#include <Tags.h>

#define LOG_DEBUG(args)																				\
{																									\
	std::shared_ptr<LogMessage> logMessage(new LogMessage({{"Filename", __FILE__}, {"Line", std::to_string(__LINE__)}, {"Time", currentTime()}, {"Severity", "Debug"}}));	\
	logMessage->stream() << args;\
	LogCore::instance().log(logMessage); \
}

#endif /* LOGHOLDER_H_ */
