/*
 * TestEzLogger.cpp
 *
 *  Created on: Dec 28, 2013
 *      Author: jamie
 */

#include "EzLogger/input/LoggerInput.h"
#include <tags/TextTag.h>
#include <tags/SeverityTag.h>
#include <output/LogOutputBase.h>
#include <memory>
#include <unistd.h>

LoggerInput * setupLogBasic()
{
	LoggerInput * log = new LoggerInput();

	std::shared_ptr<LogOutputBase> output(new LogOutputBase());

	LogCore::instance().addOutput("stdio", output);

	return log;
}

void testBasicOut(LoggerInput * log)
{
	std::cout << ">> " << "Testing basic output" << std::endl;

	*log << (const char*)("Hello World!") << (*log).endl;

	//sleep(1);

	std::cout << ">> " << "Testing number output" << std::endl;

	*log << 7 << (*log).endl;

	//sleep(250);

	std::cout << ">> " << "Testing std::string output" << std::endl;

	std::string string("this is a std::string");
	*log << string << (*log).endl;

	//sleep(250);

	std::cout << ">> " << "Testing double output" << std::endl;

	*log << 9.543 << (*log).endl;

	sleep(1);
}

void testCalltimeTags(LoggerInput * log)
{
	std::cout << ">> " << "Testing TextTag" << std::endl;

	*log << new TextTag("foo") << "bar" << (*log).endl;

	std::cout << ">> " << "Testing SeverityTag" << std::endl;

	*log << new SeverityTag(SeverityTag::Severity::UNUSUAL) << (const char*)("This is weird...") << (*log).endl;

	std::cout << ">> " << "Testing SeverityTag AND TextTag" << std::endl;

	*log << new SeverityTag(SeverityTag::Severity::UNUSUAL) << new TextTag("foo") << (const char*)("unusual foo...") << (*log).endl;

	sleep(1);
}

void testPermanentTagTemplates(LoggerInput * log)
{
	std::cout << ">> " << "Testing Permanent TextTag" << std::endl;

	log->addTagTemplate(std::string("foo"), new TextTag("foo"));

	*log << "bar" << (*log).endl;

	sleep(1);
}

int main()
{
	LoggerInput * log = setupLogBasic();
	testBasicOut(log);
	testCalltimeTags(log);
	testPermanentTagTemplates(log);
	return 0;
}


