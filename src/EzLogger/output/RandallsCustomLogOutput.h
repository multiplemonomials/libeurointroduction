/*
 * RandallsCustomLogOutput.h
 *
 * Formats output like: "
 * [Time: 13:72] [Severity: Recoverable] SomeFilename:339
 * Something Has Happened
 */

#ifndef RANDALLSCUSTOMLOGOUTPUT_H_
#define RANDALLSCUSTOMLOGOUTPUT_H_

#include "LogOutputBase.h"

class RandallsCustomLogOutput : public LogOutputBase
{
public:
	virtual void writeMessage(std::shared_ptr<LogMessage> messagePtr);

};

#endif /* RANDALLSCUSTOMLOGOUTPUT_H_ */
