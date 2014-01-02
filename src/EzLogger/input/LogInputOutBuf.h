/*
 * LogInputOutBuf.h
 *
 *part of the stream-receiving code for LogInput
 *from Nicolai M. Josuttis's book;
 */

#ifndef LOGINPUTOUTBUF_H_
#define LOGINPUTOUTBUF_H_

#include <iostream>
#include <streambuf>
#include <cstdio>
#include <sstream>

class LogInputOutBuf : public std::streambuf
{

protected:

	//complete message we're writing to
	std::shared_ptr<std::ostringstream> _outputStreamPtr;

	virtual int_type overflow(int_type outputChar)
	{
		if(outputChar != EOF)
		{
			char z = outputChar;

			*(_outputStreamPtr) << z;
		}

		return outputChar;
	}

	virtual std::streamsize xsputn(char const* outputPtr, std::streamsize outputSize)
	{
		(*_outputStreamPtr) << outputPtr;
		return outputSize;
	}

public:

	explicit LogInputOutBuf(std::shared_ptr<std::ostringstream> output)
	:_outputStreamPtr(output)
	{

	}

	LogInputOutBuf(const LogInputOutBuf&) = default;

	LogInputOutBuf& operator=(const LogInputOutBuf&) = default;
};



#endif /* LOGINPUTOUTBUF_H_ */
