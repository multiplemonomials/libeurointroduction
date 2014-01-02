/*
 * Tags.h
 *
 *  Created on: Jan 1, 2014
 *      Author: jamie
 */

#ifndef TAGS_H_
#define TAGS_H_

#include <ctime>
#include <string>

std::string currentTime()
{
	std::time_t time = std::time(0);
	char cstr[128];
	std::strftime(cstr, sizeof(cstr), "%I:%M:%S", std::localtime(&time));

	return cstr;
}

std::string currentDate()
{
	std::time_t time = std::time(0);
	char cstr[128];
	std::strftime(cstr, sizeof(cstr), "%D", std::localtime(&time));

	return cstr;
}

#endif /* TAGS_H_ */
