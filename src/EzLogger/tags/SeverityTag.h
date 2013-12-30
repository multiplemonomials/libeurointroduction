/*
 * EnumTag.h
 *
 *  Created on: Dec 28, 2013
 *      Author: jamie
 */

#ifndef ENUMTAG_H_
#define ENUMTAG_H_

#include "TagBase.h"

class SeverityTag : public TagBase
{

public:

	enum class Severity
	{
		DEBUG,
		INFO,
		UNUSUAL,
		RECOVERABLE,
		FATAL
	};

	Severity _severity;

	virtual std::string getString();

	SeverityTag(Severity severity);

	virtual ~SeverityTag();
};

bool operator==(SeverityTag const & lhs, SeverityTag const & rhs);

#endif /* ENUMTAG_H_ */
