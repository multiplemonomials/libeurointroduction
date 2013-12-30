/*
 * TagBase.h
 *
 * Base class for a tag that can be put in a log message
 *
 *  Created on: Dec 28, 2013
 *      Author: jamie
 */

#ifndef TAGBASE_H_
#define TAGBASE_H_

#include <string>
#include <ostream>

struct TagBase
{
	TagBase(){}

	virtual std::string getString()
	{
		return "ERROR: Base class (TagBase) is being logged";
	}

	virtual ~TagBase(){}
};

bool operator==(TagBase const & lhs, TagBase const & rhs);
#endif /* TAGBASE_H_ */
