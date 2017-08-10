#pragma once
#include <iostream>
#include <string>
class Log
{	
public:
	enum logLevel
	{
		Warning, Error, FatalError
	};
	Log();
	~Log();

	static void write(const char *error, logLevel level);
	static void write(std::string error, logLevel level);
	static char* levelStr(logLevel level);

};

