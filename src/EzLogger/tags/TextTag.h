/*
 * TextTag.h
 *
 *  Created on: Dec 28, 2013
 *      Author: jamie
 */

#ifndef TEXTTAG_H_
#define TEXTTAG_H_

#include "TagBase.h"

class TextTag : public TagBase
{
public:
	std::string _tag;

	virtual ~TextTag();
	TextTag(std::string tag);

	virtual std::string getString();
};

bool operator==(TextTag const & lhs, TextTag const & rhs);

#endif /* TEXTTAG_H_ */
