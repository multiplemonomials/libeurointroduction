/*
  * LoggerInput.cpp
 *
 *  Created on: Dec 28, 2013
 *      Author: jamie
 */

#include "LoggerInput.h"

logger_custom log::custom;
logger_endl log::endl;


LoggerInput::LoggerInput()
:_tagsToApply(),
 _tagGenerators(),
 _messageText(this)
{
	reInitMessage();
}

void LoggerInput::reInitMessage()
{
	//re-construct the tag queue that will be passed on to the message
	stagingTags = std::deque<std::shared_ptr<TagBase> >();

	//clear stringstream
	_messageText.str(std::string());
}

void LoggerInput::sendMessage()
{
	//Add in predefined tags.

	//this is different because we're FOREACH-ing through a map
	BOOST_FOREACH(tagMapElementType tagPair, _tagsToApply)
	{
		stagingTags.push_back(tagPair.second);
	}

	BOOST_FOREACH(generatorMapElementType generatorPair, _tagGenerators)
	{
		stagingTags.push_back((generatorPair.second()));
	}

	//construct message and send it
	std::string messageText = _messageText.str();

	LogMessage message = LogMessage(messageText, stagingTags);

	LogCore::instance().log(message);

	reInitMessage();
}

//adds a function that GENERATES a tag to the logger.
//whenever a message is logged a copy of this object will be added as a tag
//and the result will be added to the message
void LoggerInput::addTagTemplate(std::string key, std::shared_ptr<TagBase> tag)
{
	_tagsToApply[key] = tag;
}

//adds a function that GENERATES a tag to the logger.
//whenever a message is logged this function will be called
//and the result will be added to the message
void LoggerInput::addTagGenerator(std::string key, boost::function<std::shared_ptr<TagBase> ()> generator)
{
	_tagGenerators[key] = generator;
}

//removes the tag from the list of those that are applied to a new object
void LoggerInput::removeTagTemplate(const std::string & key)
{
	_tagsToApply.erase(key);
}

//remove the tag from the list of tag generators
void LoggerInput::removeTagGenerator(const std::string & key)
{
	_tagGenerators.erase(key);
}

LoggerInput::~LoggerInput()
{

}


//// General template operator.
//template<typename T>
//LoggerInput & operator<<(LoggerInput & logger, T const & arg1)
//{
//	std::cout << "LoggerInput.operator<<<T> called" << std::endl;
//	return (logger._messageText << arg1);
//}
//
//
//// Specialization for logger_endl.
//template<>
//LoggerInput & operator<< <logger_endl>(LoggerInput & logger, logger_endl const & arg1)
//{
//	std::cout << "LoggerInput.operator<<<endl> called" << std::endl;
//	logger.sendMessage();
//	return logger;
//}
//
//
//// Specialization for TagBase.
//template<>
//LoggerInput & operator<<<TextTag>(LoggerInput & logger, const TextTag & arg1)
//{
//	std::cout << "LoggerInput.operator<<<TextTag> called" << std::endl;
//	logger.stagingTags.push(arg1);
//	return logger;
//}

LoggerInput & operator<<(LoggerInput & logger, TagBase * tag)
{
	logger.stagingTags.push_back(std::shared_ptr<TagBase>(tag));
	return logger;
}

LoggerInput & operator<<(std::ostream & stream, const logger_endl & endl)
{
	endl._logger.sendMessage();
	return endl._logger;
}

LoggerInput & operator<<(LoggerInput & stream, const logger_endl & endl)
{
	endl._logger.sendMessage();
	return endl._logger;
}

std::ostream & operator<<(LoggerInput & logger, const char* arg1)
{
	return (logger._messageText << arg1);
}

std::ostream & operator<<(LoggerInput & logger, const std::string & arg1)
{
	return (logger._messageText << arg1);
}

std::ostream & operator<<(LoggerInput & logger, const int & arg1)
{
	return (logger._messageText << arg1);
}

std::ostream & operator<<(LoggerInput & logger, const double & arg1)
{
	return (logger._messageText << std::to_string(arg1));
}

std::ostream & operator<<(LoggerInput & logger, logger_custom & arg1)
{
	return logger._messageText;
}
