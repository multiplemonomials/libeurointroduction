/*
 * DateTag.h
 *
 *  Has a generator function that return s
 */

#ifndef DATETAG_H_
#define DATETAG_H_

#include "TimeTag.h"
#include <iostream>

class DateTag : public TimeTag
{

public:
	DateTag(time_t time);

	virtual ~DateTag();

	virtual std::string getString();

	static std::shared_ptr<DateTag> dt_factory();
};

#endif /* DATETAG_H_ */
