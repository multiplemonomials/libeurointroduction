/*
 * TimeTag.h
 *
 * Tag that displays the current time in hours, minutes, and seconds that factory() was called
 */

#ifndef TIMETAG_H_
#define TIMETAG_H_

#include <ctime>
#include <memory>
#include <sstream>
#include "TagBase.h"

class TimeTag : public TagBase
{

public:
	std::time_t _time;

	TimeTag(std::time_t);

	virtual ~TimeTag();

	//simple factory function that returns a shared pointer with a TimeTag that's initialized to the current (local) time.
	//for use with LoggerInput.addTagGenerator()
	static std::shared_ptr<TimeTag> factory();

	virtual std::string getString();
};

#endif /* TIMETAG_H_ */
