/*
 * DateTag.cpp
 *
 *  Created on: Dec 30, 2013
 *      Author: jamie
 */

#include <tags/DateTag.h>

//just invoke the super constructor
DateTag::DateTag(time_t time)
:TimeTag(time)
{

}

DateTag::~DateTag()
{

}

std::string DateTag::getString()
{
	char cstr[128];
	std::strftime(cstr, sizeof(cstr), "%D", std::localtime(&_time));

	return cstr;
}

std::shared_ptr<DateTag> DateTag::dt_factory()
{
	return std::make_shared<DateTag>(std::time(0));
}
