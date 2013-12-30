/*
 * TextTag.cpp
 *
 *  Created on: Dec 28, 2013
 *      Author: jamie
 */

#include "TextTag.h"

TextTag::~TextTag()
{

}

TextTag::TextTag(std::string tag)
:_tag(tag)
{

}

std::string TextTag::getString()
{
	return _tag;
}

bool operator==(TextTag const & lhs, TextTag const & rhs)
{
	return rhs._tag == lhs._tag;
}
