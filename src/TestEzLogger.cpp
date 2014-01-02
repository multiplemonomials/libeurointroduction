/*
 * TestEzLogger.cpp
 *
 *  Created on: Dec 28, 2013
 *      Author: jamie
 */

#include <input/LogInput.h>
#include <tags/TextTag.h>
#include <tags/TimeTag.h>
#include <tags/DateTag.h>
#include <tags/SeverityTag.h>
#include <output/LogOutputBase.h>
#include <memory>
#include <unistd.h>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "test/functimer.hpp"

void testBasicOut(std::shared_ptr<LogInput> log)
{
	FUNC_TIMER;

	std::cout << "-- " << "Testing basic output" << std::endl;
	log->stream() << (const char*)("Hello World!") << std::endl;

	std::cout << "-- " << 7 << "Testing number output" << std::endl;
	log->stream() << 7 << std::endl;

	std::cout << "-- " << "Testing std::string output" << std::endl;
	std::string string("this is a std::string");
	log->stream() << string << std::endl;

	std::cout << "-- " << "Testing double output" << std::endl;
	log->stream() << std::to_string(9.543) << std::endl;


	// Wait for output.
	boost::this_thread::sleep(boost::posix_time::milliseconds(100));
}

void testCalltimeTags(std::shared_ptr<LogInput> log)
{
	std::cout << "-- " << "Testing TextTag" << std::endl;
	log->addTag("Text", new TextTag("foo")).stream() << "bar" << std::endl;

	std::cout << "-- " << "Testing SeverityTag" << std::endl;
	log->addTag("Severity", new SeverityTag(SeverityTag::Severity::UNUSUAL)).stream() << (const char*)("This is weird...") << std::endl;

	std::cout << "-- " << "Testing SeverityTag AND TextTag" << std::endl;
	log->addTag("Severity", new SeverityTag(SeverityTag::Severity::UNUSUAL)).addTag("Text", new TextTag("foo")).stream() << (const char*)("unusual foo...") << std::endl;


	// Wait for output.
	boost::this_thread::sleep(boost::posix_time::milliseconds(100));
}

void testPermanentTagTemplates(std::shared_ptr<LogInput> log)
{
	std::cout << "-- " << "Testing Permanent TextTag" << std::endl;
	log->addTagTemplate(std::string("foo"), new TextTag("foo"));
	log->stream() << "bar" << std::endl;
	log->stream() << "d" << std::endl;


	// Wait for output.
	boost::this_thread::sleep(boost::posix_time::milliseconds(100));


	std::cout << "--" << "Removing tag" << std::endl;
	log->removeTagTemplate("foo");
	log->stream() << "It should be gone now" << std::endl;


	// Wait for output.
	boost::this_thread::sleep(boost::posix_time::milliseconds(100));
}

void testPermanentTagGenerators(std::shared_ptr<LogInput> log)
{
	// Report the time on each log entry.
	std::cout << "-- " << "Testing Permanent TimeTag" << std::endl;
	log->addTagGenerator("time_generator", boost::function<std::shared_ptr<TagBase>()>(&TimeTag::factory));
	log->stream() << "now" << std::endl;

	// Wait for time to pass.
	boost::this_thread::sleep(boost::posix_time::seconds(1));
	log->stream() << "1 second from now" << std::endl;


	// Wait for output.
	boost::this_thread::sleep(boost::posix_time::milliseconds(100));


	// Report the date on each log entry.
	log->addTagGenerator("date_generator", boost::function<std::shared_ptr<TagBase> ()>(&DateTag::dt_factory));
	std::cout << "--" << "Adding tag generator for DateTag" << std::endl;
	log->stream() << "is the current date" << std::endl;


	// Wait for output.
	boost::this_thread::sleep(boost::posix_time::milliseconds(100));


	// We can remove the generators.
	std::cout << "--" << "Removing tag generators" << std::endl;
	log->removeTagGenerator("time_generator");
	log->removeTagGenerator("date_generator");

	log->stream() << "It should be gone now" << std::endl;


	// Wait for output.
	boost::this_thread::sleep(boost::posix_time::milliseconds(100));
}

int main()
{
	// Build object for sourcing stuff into the log.
  	auto log = std::make_shared<LogInput>();


	// Add a log sink (emits stuff to std::cout).
	std::shared_ptr<LogOutputBase> output(new LogOutputBase());
	LogCore::instance().addOutput("stdio", output);


	// Run logging tests.
	testBasicOut(log);
	testCalltimeTags(log);
	testPermanentTagTemplates(log);
	testPermanentTagGenerators(log);


	// Verify removeOutput.
	LogCore::instance().removeOutput("stdio");

//#define LOG_DEBUG(...) LogContainer::instance().logDebug.addTag(new TextTag(__FILENAME__)).addTag(new TextTag(__LINE__)).stream() << __VA_ARGS__


	// Try M2MSLAP logging macros.
	//LOG_DEBUG("This is a debug message.");

	return 0;
}


void foo()
{


}
}


