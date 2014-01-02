/*
 * FileLogOutput.cpp
 *
 *  Created on: Jan 2, 2014
 *      Author: jamie
 */

#include <output/FileLogOutput.h>

FileLogOutput::FileLogOutput(const char* filename)
:_ofstream(filename)
{
	if(!_ofstream)
	{
		std::cerr << "FileLogOutput: file \"" << filename << "\" could not be opened.";
	}
	LogOutputBase(); //invoke superconstructor second because that may immediately try to write data
}

void FileLogOutput::writeString(const std::string & text)
{
	_ofstream << text << std::endl;
}
