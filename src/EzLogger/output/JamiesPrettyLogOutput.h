/*
 * JamiesPrettyLogOutput.h
 *
 *	I don't really like the default formatting
 *
 *  Created on: Jan 1, 2014
 *      Author: jamie
 */

#ifndef JAMIESPRETTYLOGOUTPUT_H_
#define JAMIESPRETTYLOGOUTPUT_H_

#include "LogOutputBase.h"

class JamiesPrettyLogOutput : public LogOutputBase
{
	virtual void writeMessage(std::shared_ptr<LogMessage> messagePtr);

public:
	JamiesPrettyLogOutput();

	virtual ~JamiesPrettyLogOutput();
};

#endif /* JAMIESPRETTYLOGOUTPUT_H_ */
