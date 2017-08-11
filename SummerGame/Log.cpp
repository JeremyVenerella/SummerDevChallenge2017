#include "Log.h"
#include "SDL.h"


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
	if (level == Log::FatalError)
	{
		SDL_Quit();
		std::cin >> temp;
		--temp;
		exit(1);
	}
}

void Log::write(std::string error, logLevel level)

{
	int temp;
	std::cout << "[" << levelStr(level) << "] " << error << std::endl;
	if (level == Log::FatalError)
	{
		SDL_Quit();
		std::cin >> temp;
		--temp;
		exit(1);
	}
}

char * Log::levelStr(logLevel level)
{
	char *ErrorTypes[] =
	{
		"Warning",
		"Error",
		"FatalError",
		"Info"
	};

	return ErrorTypes[level];
}
