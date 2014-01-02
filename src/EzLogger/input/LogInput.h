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
#include "LogInputOstream.h"

class LogInput
{
private:

	//for BOOST_FOREACH
	typedef std::pair<std::string, boost::function<std::shared_ptr<TagBase> ()>> generatorMapElementType;

	// "Persistent" tags that will be applied to every log message.
	std::map<std::string, std::shared_ptr<TagBase> > _tagsToApply;

	//holds functions with definition "std::shared_ptr<TagBase> foo()"
	std::map<std::string, boost::function<std::shared_ptr<TagBase> ()>> _tagGenerators;

public:

	// Text that comprises the next log message.
	std::shared_ptr<std::ostringstream> _messageStreamPtr;

private:

	LogInputOstream _inputStream;

public:

	// "Ephemeral" tags that will be deleted after the next log message.
	LogMessage::TagMapType _stagingTags;

	LogInput();

	virtual ~LogInput();

	//takes a CONSTRUCTED tag object.
	//it will added to every tag that this logger makes
	//until it is removed
	void addTagTemplate(std::string key, std::shared_ptr<TagBase> tag);

	//overload allowing addTagTemplate(new SomeTag()) instead
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

	//add a tag to the list of tags
	LogInput & addTag(std::string const & key, std::shared_ptr<TagBase> tag)
	{
		_stagingTags[key] = tag;

		return *this;
	}

	//pointer overload for above
	LogInput & addTag(std::string const & key, TagBase * tag)
	{
		return addTag(key, std::shared_ptr<TagBase>(tag));
	}

	//sends the current message to all of the outputs and starts a new one.
	//automatically called by operator<<(
	void sendMessage();

	void reInitMessage();

	//gets a stream for making the log message
	LogInputOstream & stream()
	{
		return _inputStream;
	}

};

#endif /* LOGGERINPUT_H_ */
