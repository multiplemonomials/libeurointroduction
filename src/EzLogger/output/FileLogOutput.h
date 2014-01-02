/*
 * FileLogOutput.h
 *
 *  Created on: Jan 2, 2014
 *      Author: jamie
 */

#ifndef FILELOGOUTPUT_H_
#define FILELOGOUTPUT_H_

#include "LogOutputBase.h"
#include <fstream>

class FileLogOutput : public LogOutputBase
{
	std::ofstream _ofstream;

public:
	FileLogOutput(const char* filename);

	//override this method of LogOutputBase
	virtual void writeString(const std::string & text);
};

#endif /* FILELOGOUTPUT_H_ */
