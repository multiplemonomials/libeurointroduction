/*
 * RandallsCustomLogFileOutput.h
 *
 *  Created on: Jan 2, 2014
 *      Author: jamie
 */

#ifndef RANDALLSCUSTOMFILELOGOUTPUT_H_
#define RANDALLSCUSTOMFILELOGOUTPUT_H_

#include "FileLogOutput.h"

class RandallsCustomFileLogOutput : public FileLogOutput
{

public:
	RandallsCustomFileLogOutput(const char* filename)
	:FileLogOutput(filename)
	{

	}

	virtual void writeMessage(std::shared_ptr<LogMessage> messagePtr);

};



#endif /* RANDALLSCUSTOMFILELOGOUTPUT_H_ */
