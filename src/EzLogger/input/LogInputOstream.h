/*
 * LogInputOstream.h
 *
 *  Created on: Dec 30, 2013
 *      Author: jamie
 */

#ifndef LOGINPUTOSTREAM_H_
#define LOGINPUTOSTREAM_H_

#include "LogInputOutBuf.h"
#include <boost/function.hpp>
#include <memory>

class LogInput;

class LogInputOstream : protected virtual LogInputOutBuf, public std::ostream
{
private:

	//this is kind of a tricky one.
	//we have to tell the LogInput when we receive a std::endl
	//but taking a LogInput in our constructor would cause a circular inclusion.
	//so instead we forward declare the class and take a member function pointer to where we're supposed to call back.

	//matches "void foo()"
	boost::function<void (LogInput*)> _sendCallback;

	LogInput & _logger;

public:

	explicit LogInputOstream
	(
		std::shared_ptr<std::ostringstream> output,
		boost::function<void (LogInput*)> sendCallback,
		LogInput & logger
	)
	: LogInputOutBuf(output),
	  std::ostream(dynamic_cast<LogInputOutBuf *>(this)),
	  _sendCallback(sendCallback),
	  _logger(logger)
	{

	}

	LogInputOstream & operator=(const LogInputOstream&) = default;

	virtual ~LogInputOstream()
	{

	}

	// For un-specialized types, just invoke the "normal" ostream behavior.
	template<typename T>
	LogInputOstream & operator<<(const T& arg)
	{
		(*_outputStreamPtr) << arg;
		return *this;
	}

	typedef LogInputOstream& (*LogOstreamManipulator)(LogInputOstream&);

	//accepts custom manipulator
	LogInputOstream& operator<<(LogOstreamManipulator manipulator)
	{
		return manipulator(*this);
	}

	static LogInputOstream& endl(LogInputOstream& stream)
	{
		stream._sendCallback(&(stream._logger));
		return stream;
	}

	//type of std::cout
	typedef std::basic_ostream<char, std::char_traits<char> > CoutType;

	//signature of std::endl
	typedef CoutType& (*StandardEndLine)(CoutType&);

	LogInputOstream& operator<<(StandardEndLine manip)
	{
		(*this)._sendCallback(&_logger);

		return *this;
	}
};

#endif /* LOGINPUTOSTREAM_H_ */
