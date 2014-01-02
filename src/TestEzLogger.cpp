/*
 * TestEzLogger.cpp
 *
 *  Created on: Dec 28, 2013
 *      Author: jamie
 */

#include "LogMacros.h"
#include <output/JamiesPrettyLogOutput.h>
#include <memory>
#include <unistd.h>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "test/functimer.hpp"

#define LOG_BASIC(args)																				\
{																									\
	std::shared_ptr<LogMessage> logMessage(new LogMessage());	\
	logMessage->stream() << args; \
	LogCore::instance().log(logMessage); \
}


void testBasicOut()
{
	FUNC_TIMER;

	std::cout << "-- " << "Testing basic output" << std::endl;
	LOG_BASIC("Hello World")

	std::cout << "-- " << 7 << "Testing number output" << std::endl;
	LOG_BASIC(7)

	std::cout << "-- " << "Testing std::string output" << std::endl;
	std::string string("this is a std::string");
	LOG_BASIC(string)


	std::cout << "-- " << "Testing double output" << std::endl;
	LOG_BASIC(9.543)

	std::cout << "-- " << "Testing multiple item output" << std::endl;
	LOG_BASIC("foo " << "bar")


	// Wait for output.
	boost::this_thread::sleep(boost::posix_time::milliseconds(100));
}

//now that basic logging works, use it!
#define LOG_UNITTEST(args)																				\
{																									\
	std::shared_ptr<LogMessage> logMessage(new LogMessage({{"Test", "Test"}}));	\
	logMessage->stream() << args; \
	LogCore::instance().log(logMessage); \
}

void testCalltimeTags()
{
	LOG_UNITTEST("Testing Custom Tag")
	std::shared_ptr<LogMessage> logMessage(new LogMessage({{"Tag", "Custom"}}));
	logMessage->stream() << "foo";
	LogCore::instance().log(logMessage);

	// Wait for output.
	boost::this_thread::sleep(boost::posix_time::milliseconds(100));
}

void testTimeDateTags()
{

	// Report the time on each log entry.
	LOG_UNITTEST("Testing Time Tag")
	{
		std::shared_ptr<LogMessage> logMessage(new LogMessage({{"Time", currentTime()}})); //function from Tags.h
		logMessage->stream() << "Now";
		LogCore::instance().log(logMessage);
	}
	// Wait for time to pass.
	boost::this_thread::sleep(boost::posix_time::seconds(1));
	{
		std::shared_ptr<LogMessage> logMessage(new LogMessage({{"Time", currentTime()}}));
		logMessage->stream() << "1 second from now";
		LogCore::instance().log(logMessage);
	}


	// Wait for output.
	boost::this_thread::sleep(boost::posix_time::milliseconds(100));


	// Report the date on each log entry.
	LOG_UNITTEST("Testing Date Tag")
	{
		std::shared_ptr<LogMessage> logMessage(new LogMessage({{"Date", currentDate()}}));
		LogCore::instance().log(logMessage);
	}

	// Wait for output.
	boost::this_thread::sleep(boost::posix_time::milliseconds(100));
}

int main()
{

	// Add a log sink (emits stuff to std::cout).
	std::shared_ptr<JamiesPrettyLogOutput> output(new JamiesPrettyLogOutput());
	LogCore::instance().addOutput("stdio", output);


	// Run logging tests.
	testBasicOut();
	testCalltimeTags();
	testTimeDateTags();


	// Verify removeOutput.
	LogCore::instance().removeOutput("stdio");

	// Try M2MSLAP logging macros.
	//LOG_DEBUG("This is a debug message.");

	return 0;
}

