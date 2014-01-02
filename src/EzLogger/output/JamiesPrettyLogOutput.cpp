/*
 * JamiesPrettyLogOutput.cpp
 *
 *  Created on: Jan 1, 2014
 *      Author: jamie
 */

#include <output/JamiesPrettyLogOutput.h>

//just invoke superconstructor
JamiesPrettyLogOutput::JamiesPrettyLogOutput()
:LogOutputBase()
{

}

JamiesPrettyLogOutput::~JamiesPrettyLogOutput()
{

}

void JamiesPrettyLogOutput::writeMessage(std::shared_ptr<LogMessage> messagePtr)
{
	std::ostringstream ostringstream;
	BOOST_FOREACH(LogMessage::TagMapElementType tag, messagePtr->getTags())
	{
		ostringstream << "[" << tag.second << "] ";
	}

	ostringstream << messagePtr->getStream().str();

	writeString(ostringstream.str());
}
