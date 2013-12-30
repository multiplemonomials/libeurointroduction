/*
 * LoggerInput.h
 *
 *  Created on: Dec 28, 2013
 *      Author: jamie
 */

#ifndef LOGGERINPUT_H_
#define LOGGERINPUT_H_

#include <tags/TagBase.h>
#include <tags/TextTag.h>
#include <queue>
#include <list>
#include <string>
#include <sstream>
#include <utility>
#include <boost/foreach.hpp>
#include <memory>
#include <boost/function.hpp>

#include "LogMessage.h"
#include "LogCore.h"

//predeclare this so it can be used in log_ostringstream
class LoggerInput;

//flag to end the line
class logger_endl
{

};

//flag to return a stringstream
class logger_custom
{

};

namespace log
{
	static logger_custom custom;

	static logger_endl endl;
} /*namespace log*/

class log_ostringstream : public std::ostringstream
{
public:
	std::shared_ptr<LoggerInput> _logger;

	log_ostringstream(LoggerInput * logger)
	:std::stringstream(),
	_logger(logger)
	{

	}
};

class LoggerInput
{
private:

	//for BOOST_FOREACH
	typedef std::pair<std::string, std::shared_ptr<TagBase> > tagMapElementType;
	typedef std::pair<std::string, boost::function<std::shared_ptr<TagBase> ()>> generatorMapElementType;

	std::map<std::string, std::shared_ptr<TagBase> > _tagsToApply;

	//holds functions with definition "std::shared_ptr<TagBase> foo()"
	std::map<std::string, boost::function<std::shared_ptr<TagBase> ()>> _tagGenerators;

public:

	LoggerInput();

	virtual ~LoggerInput();

	//takes a CONSTRUCTED tag object.
	//it will added to every tag that this logger makes
	//until it is removed
	void addTagTemplate(std::string key, std::shared_ptr<TagBase> tag);

	//overload so you can use addTagTemplate(new SomeTag()) instead
	void addTagTemplate(std::string key, TagBase * tag)
	{
		addTagTemplate(key, std::shared_ptr<TagBase>(tag));
	}

	//adds a function that GENERATES a tag to the logger.
	//whenever a message is logged this function will be called
	//and the result will be added to the message
	void addTagGenerator(std::string key, boost::function<std::shared_ptr<TagBase> ()> generator);

	//removes the tag from the list of those that are applied to a new object
	void removeTagTemplate(const std::string & key);

	//remove the tag from the list of tag generators
	void removeTagGenerator(const std::string & key);

	//sends the current message to all of the outputs and starts a new one.
	//automatically called by operator<<(
	void sendMessage();

	void reInitMessage();

	log_ostringstream _messageText;

	std::deque<std::shared_ptr<TagBase> > stagingTags;

};

//// General template operator.
//template<typename T>
//LoggerInput & operator<<(LoggerInput & logger, T const & arg1);
//
//// Specialization for logger_endl.
//template<>
//LoggerInput & operator<< <logger_endl>(LoggerInput & stringstream, logger_endl const & arg1);
//
//// Specialization for TagBase.
//template<>
//LoggerInput & operator<<<TextTag>(LoggerInput & logger, TextTag const & arg1);

LoggerInput & operator<<(LoggerInput & logger, TagBase * tag);

LoggerInput & operator<<(std::ostream & stream, const logger_endl & endl);

LoggerInput & operator<<(LoggerInput & logger, const logger_endl & endl);

std::ostream & operator<<(LoggerInput & logger, const char* arg1);

std::ostream & operator<<(LoggerInput & logger, const std::string & arg1);

std::ostream & operator<<(LoggerInput & logger, const int & arg1);

std::ostream & operator<<(LoggerInput & logger, const double & arg1);

std::ostream & operator<<(LoggerInput & logger, logger_custom & arg1);
#endif /* LOGGERINPUT_H_ */
