#include "Log.h"



Log::Log()
{
}


Log::~Log()
{
}

void Log::write(const char * error, logLevel level)
{
	int temp;
	std::cout << "[" << levelStr(level) << "] " << error << std::endl;
	std::cin >> temp;
	--temp;
}

char * Log::levelStr(logLevel level)
{
	char *ErrorTypes[] =
	{
		"Warning",
		"Error",
		"FatalError"
	};

	return ErrorTypes[level];
}
