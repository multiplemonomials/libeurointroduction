/*
 * TestEzLogger.cpp
 *
 *  Created on: Dec 28, 2013
 *      Author: jamie
 */

#include "LogMacros.h"
#include <output/LogOutput.h>
#include <output/acceptors/BasicAcceptor.h>
#include <output/formatters/JamiesPrettyFormatter.h>
#include <output/formatters/RandallsCustomFormatter.h>
#include <output/writers/BasicWriter.h>
#include <output/writers/FileWriter.h>

#include <memory>
#include <unistd.h>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "FunctionTimer/functimer.hpp"

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

void testFileLogOutput()
{

	LOG_UNITTEST("Opening FileLogOutput on file test.log");
	auto output = std::make_shared<LogOutput<BasicAcceptor, JamiesPrettyFormatter, FileWriter>>
	(
		std::make_shared<BasicAcceptor>(),
		std::make_shared<JamiesPrettyFormatter>(),
		std::make_shared<FileWriter>("test.log")
	);
	LogCore::instance().addOutput("test.log", output);

	LOG_BASIC("This should be logged to the file.")
	// Wait for time to pass.
	boost::this_thread::sleep(boost::posix_time::milliseconds(100));

	LOG_UNITTEST("Removing FileLogOutput");
	LogCore::instance().removeOutput("test.log");

	LOG_BASIC("This should be NOT logged to the file.")
	// Wait for output.
	boost::this_thread::sleep(boost::posix_time::milliseconds(100));
}

struct FilteringAcceptor
{
	bool operator()(std::shared_ptr<LogMessage> & messagePtr)
	{
		//map.count() returns 0 if the key is not found
		return !(messagePtr->getTags().count("block_this"));
	}
};

void testFilteringOutput()
{

	LOG_UNITTEST("Swapping in new output");
	LogCore::instance().removeOutput("stdio");
	auto filtering_output = std::make_shared<LogOutput<FilteringAcceptor, JamiesPrettyFormatter, BasicWriter>>
	(
		std::make_shared<FilteringAcceptor>(),
		std::make_shared<JamiesPrettyFormatter>(),
		std::make_shared<BasicWriter>()
	);
	LogCore::instance().addOutput("stdio", filtering_output);

	LOG_BASIC("You should see this")
	// Wait for time to pass.
	boost::this_thread::sleep(boost::posix_time::milliseconds(100));

	{
		std::shared_ptr<LogMessage> logMessage(new LogMessage({{"DontBlock", "YouShouldSeeThis"}})); //function from Tags.h
		logMessage->stream() << "And this, but not the next one";
		LogCore::instance().log(logMessage);
	}

	{
		std::shared_ptr<LogMessage> logMessage(new LogMessage({{"block_this", "YouShouldn'tSeeThis"}})); //function from Tags.h
		LogCore::instance().log(logMessage);
	}

	boost::this_thread::sleep(boost::posix_time::milliseconds(100));

	LOG_UNITTEST("Swapping back in new JamiesPrettyLoggingOutput");
	LogCore::instance().removeOutput("stdio");
	auto outputPtr = std::make_shared<LogOutput<BasicAcceptor, JamiesPrettyFormatter, BasicWriter>>
	(
		std::make_shared<BasicAcceptor>(),
		std::make_shared<JamiesPrettyFormatter>(),
		std::make_shared<BasicWriter>()
	);
	LogCore::instance().addOutput("stdio", outputPtr);

	boost::this_thread::sleep(boost::posix_time::milliseconds(100));

}

int main()
{

	// Add a log sink (emits stuff to std::cout).
	auto outputPtr = std::make_shared<LogOutput<BasicAcceptor, JamiesPrettyFormatter, BasicWriter>>
	(
		std::make_shared<BasicAcceptor>(),
		std::make_shared<JamiesPrettyFormatter>(),
		std::make_shared<BasicWriter>()
	);
	LogCore::instance().addOutput("stdio", outputPtr);


	// Run logging tests.
	testBasicOut();
	testCalltimeTags();
	testTimeDateTags();
	testFileLogOutput();
	testFilteringOutput();

	LOG_UNITTEST("Done");

	boost::this_thread::sleep(boost::posix_time::milliseconds(100));

	// Verify removeOutput.
	LogCore::instance().removeOutput("stdio");

	// Try M2MSLAP logging macros.
	auto randalls_output = std::make_shared<LogOutput<BasicAcceptor, RandallsCustomFormatter, BasicWriter>>
	(
		std::make_shared<BasicAcceptor>(),
		std::make_shared<RandallsCustomFormatter>(),
		std::make_shared<BasicWriter>()
	);

	LogCore::instance().addOutput("stdio", randalls_output);

	auto randalls_file_output = std::make_shared<LogOutput<BasicAcceptor, RandallsCustomFormatter, FileWriter>>
	(
		std::make_shared<BasicAcceptor>(),
		std::make_shared<RandallsCustomFormatter>(),
		std::make_shared<FileWriter>("randall.log")
	);
	LogCore::instance().addOutput("randall.log", randalls_file_output);

	LOG_DEBUG("This is a debug message.");
	LOG_INFO("This is an info message.");

	LogCore::instance().removeOutput("stdio");

	boost::this_thread::sleep(boost::posix_time::milliseconds(100));

	return 0;
}

