#pragma once
#include <iostream>
class Log
{	
public:
	enum logLevel
	{
		Warning, Error, FatalError
	};
	Log();
	~Log();

	void write(const char *error, logLevel level);
	char* levelStr(logLevel level);

};

