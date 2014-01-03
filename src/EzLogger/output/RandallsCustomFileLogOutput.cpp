/*
 * RandallsCustomLogFileOutput.h
 *
 *  Created on: Jan 2, 2014
 *      Author: jamie
 */

#include "RandallsCustomFileLogOutput.h"
#include <cstring>

void RandallsCustomFileLogOutput::writeMessage(std::shared_ptr<LogMessage> messagePtr)
{
	std::ostringstream ostringstream;

	//make things a bit shorter
	LogMessage::TagMapType & tags = messagePtr->getTags();

	//the __FILE__ macro includes part of the path to the file
	const char* incorrect_filename = tags["filename"].c_str();

	const char* true_filename = strrchr(incorrect_filename, '/') ? strrchr(incorrect_filename, '/') + 1 : incorrect_filename;

	ostringstream << "[" << tags["severity"] << "] "
				  << tags["time"] << " "
	              << true_filename << ":"
	              << tags["line_number"]
	              << " ----------------------------"
	              << std::endl;

	ostringstream << messagePtr->getStream().str() << std::endl; //add an extra newline

	writeString(ostringstream.str());
}
