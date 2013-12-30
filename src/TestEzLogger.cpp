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

void testBasicOut(LogInput * log)
{
	FUNC_TIMER;

	std::cout << ">> " << "Testing basic output" << std::endl;

	*log << (const char*)("Hello World!") << (*log).endl;

	std::cout << ">> " << "Testing number output" << std::endl;

	*log << 7 << (*log).endl;

	std::cout << ">> " << "Testing std::string output" << std::endl;

	std::string string("this is a std::string");
	*log << string << (*log).endl;

	std::cout << ">> " << "Testing double output" << std::endl;

	*log << 9.543 << (*log).endl;

	boost::this_thread::sleep(boost::posix_time::milliseconds(100));

}

void testCalltimeTags(LogInput * log)
{
	std::cout << ">> " << "Testing TextTag" << std::endl;

	*log << new TextTag("foo") << "bar" << (*log).endl;

	std::cout << ">> " << "Testing SeverityTag" << std::endl;

	*log << new SeverityTag(SeverityTag::Severity::UNUSUAL) << (const char*)("This is weird...") << (*log).endl;

	std::cout << ">> " << "Testing SeverityTag AND TextTag" << std::endl;

	*log << new SeverityTag(SeverityTag::Severity::UNUSUAL) << new TextTag("foo") << (const char*)("unusual foo...") << (*log).endl;

	boost::this_thread::sleep(boost::posix_time::milliseconds(100));
}

void testPermanentTagTemplates(LogInput * log)
{
	std::cout << ">> " << "Testing Permanent TextTag" << std::endl;

	log->addTagTemplate(std::string("foo"), new TextTag("foo"));

	*log << "bar" << (*log).endl;

	*log << "d" << (*log).endl;

	boost::this_thread::sleep(boost::posix_time::milliseconds(100));

	std::cout << ">>" << "Removing tag" << std::endl;

	log->removeTagTemplate("foo");

	*log << "It should be gone now" << (*log).endl;

	boost::this_thread::sleep(boost::posix_time::milliseconds(100));
}

void testPermanentTagGenerators(LogInput * log)
{
	std::cout << ">> " << "Testing Permanent TimeTag" << std::endl;
	log->addTagGenerator("time_generator", boost::function<std::shared_ptr<TagBase> ()>(&TimeTag::factory));

	*log << "now" << (*log).endl;
	boost::this_thread::sleep(boost::posix_time::seconds(1));
	*log << "1 second from now" << (*log).endl;

	boost::this_thread::sleep(boost::posix_time::milliseconds(100));

	log->addTagGenerator("date_generator", boost::function<std::shared_ptr<TagBase> ()>(&DateTag::dt_factory));
	std::cout << ">>" << "Adding tag generator for DateTag" << std::endl;
	*log << "is the current date" << (*log).endl;

	boost::this_thread::sleep(boost::posix_time::milliseconds(100));

	std::cout << ">>" << "Removing tag generators" << std::endl;

	log->removeTagGenerator("time_generator");
	log->removeTagGenerator("date_generator");

	*log << "It should be gone now" << (*log).endl;

	boost::this_thread::sleep(boost::posix_time::milliseconds(100));
}

int main()
{
	LogInput * log = new LogInput();

	std::shared_ptr<LogOutputBase> output(new LogOutputBase());

	LogCore::instance().addOutput("stdio", output);

	testBasicOut(log);
	testCalltimeTags(log);
	testPermanentTagTemplates(log);
	testPermanentTagGenerators(log);

	delete log;

	LogCore::instance().removeOutput("stdio");

	//destroy output
	output.reset();

	return 0;
}


