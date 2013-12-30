/*
 * TimeTag.cpp
 *
 *  Created on: Dec 29, 2013
 *      Author: jamie
 */

#include <tags/TimeTag.h>

TimeTag::TimeTag(std::time_t time)
:_time(time)
{

}

TimeTag::~TimeTag()
{

}

std::shared_ptr<TimeTag> TimeTag::factory()
{
	return std::make_shared<TimeTag>(std::time(0));
}

std::string TimeTag::getString()
{
	char cstr[128];
	std::strftime(cstr, sizeof(cstr), "%I:%M:%S", std::localtime(&_time));

	return cstr;
}
