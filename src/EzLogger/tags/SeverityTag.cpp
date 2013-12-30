/*
 * SeverityTag.cpp
 *
 *  Created on: Dec 28, 2013
 *      Author: jamie
 */
#include "SeverityTag.h"

SeverityTag::SeverityTag(Severity severity)
:_severity(severity)
{

}

SeverityTag::~SeverityTag()
{

}

std::string SeverityTag::getString()
{
	//switch on the enums and print their names.
	//not sure if there's a bettwer way to do this
	switch(_severity)
	{
		case Severity::DEBUG:
			return "Debug";

		case Severity::INFO:
			return "Info";

		case Severity::UNUSUAL:
			return "Unusual";

		case Severity::RECOVERABLE:
			return "Recoverable";

		case Severity::FATAL:
			return "Fatal";

		default:
			return "ERROR: severity not found";
	}
}

bool operator==(SeverityTag const & lhs, SeverityTag const & rhs)
{
	return lhs._severity == lhs._severity;
}

