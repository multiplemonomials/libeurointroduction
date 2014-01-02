/*
  * LoggerInput.cpp
 *
 *  Created on: Dec 28, 2013
 *      Author: jamie
 */

#include "LogInput.h"

#define LOG(...)  std::cout << "--> " << __VA_ARGS__ << std::endl

LogInput::LogInput()
:_tagsToApply(),
 _tagGenerators(),
 _messageStreamPtr(new std::ostringstream()),
 _inputStream(_messageStreamPtr, boost::function<void (LogInput*)>(&LogInput::sendMessage), *this)
{
	reInitMessage();
}

void LogInput::reInitMessage()
{
	//re-construct the tag queue that will be passed on to the message
	_stagingTags = LogMessage::TagMapType();

	_messageStreamPtr->str("");
}

void LogInput::sendMessage()
{
	//Add in predefined tags.

	//this is different because we're FOREACH-ing through a map
//	for(auto tagPair : _tagsToApply)
//	{
//		_stagingTags.push_back(tagPair.second);
//	}

	BOOST_FOREACH(LogMessage::TagMapElementType tagPair, _tagsToApply)
	{
		_stagingTags[tagPair.first] = tagPair.second;
	}

	BOOST_FOREACH(generatorMapElementType generatorPair, _tagGenerators)
	{
		//execute the function pointer and add its result to stagingTags
		_stagingTags[generatorPair.first] = generatorPair.second();
	}

	//construct message and send it
	LogMessage message = LogMessage(_messageStreamPtr->str(), std::move(_stagingTags));

	LogCore::instance().log(message);

	reInitMessage();
}

//adds a function that GENERATES a tag to the logger.
//whenever a message is logged a copy of this object will be added as a tag
//and the result will be added to the message
void LogInput::addTagTemplate(std::string key, std::shared_ptr<TagBase> tag)
{
	_tagsToApply[key] = tag;
}

//adds a function that GENERATES a tag to the logger.
//whenever a message is logged this function will be called
//and the result will be added to the message
void LogInput::addTagGenerator(std::string key, boost::function<std::shared_ptr<TagBase> ()> generator)
{
	_tagGenerators[key] = generator;
}

//removes the tag from the list of those that are applied to a new object
void LogInput::removeTagTemplate(const std::string & key)
{
	_tagsToApply.erase(key);
}

//remove the tag from the list of tag generators
void LogInput::removeTagGenerator(const std::string & key)
{
	_tagGenerators.erase(key);
}

LogInput::~LogInput()
{

}

//LogInput & operator<<(LogInput & logger, TagBase * tag)
//{
//	logger.stagingTags.push_back(std::shared_ptr<TagBase>(tag));
//	return logger;
//}
//
//LogInput & operator<<(std::ostream & stream, const logger_endl & endl)
//{
//	endl._logger.sendMessage();
//	return endl._logger;
//}
//
//LogInput & operator<<(LogInput & stream, const logger_endl & endl)
//{
//	endl._logger.sendMessage();
//	return endl._logger;
//}
//
//std::ostream & operator<<(LogInput & logger, const char* arg1)
//{
//	return (logger._messageText << arg1);
//}
//
//std::ostream & operator<<(LogInput & logger, const std::string & arg1)
//{
//	return (logger._messageText << arg1);
//}
//
//std::ostream & operator<<(LogInput & logger, const int & arg1)
//{
//	return (logger._messageText << arg1);
//}
//
//std::ostream & operator<<(LogInput & logger, const double & arg1)
//{
//	return (logger._messageText << std::to_string(arg1));
//}
