/*
 * RandallsCustomLogFileOutput.h
 *
 *  Created on: Jan 2, 2014
 *      Author: jamie
 */

#include "RandallsCustomFileLogOutput.h"

void RandallsCustomFileLogOutput::writeMessage(std::shared_ptr<LogMessage> messagePtr)
{
	std::ostringstream ostringstream;

	//make things a bit shorter
	LogMessage::TagMapType & tags = messagePtr->getTags();

	ostringstream << "[" << "Time: " << tags["time"] << "] [Severity: " << tags["severity"] << "] "
	              << tags["filename"] << ":" << tags["line_number"] << std::endl;


	ostringstream << messagePtr->getStream().str();

	writeString(ostringstream.str());
}
