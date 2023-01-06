#include "LogOutput.h"

void DebugLog(LogMessage logDebugType, const std::string& message)
{
	int color = 0;

	if (logDebugType == LogMessage::WARNING)
	{
		color = 33;
	}
	else if (logDebugType == LogMessage::ERROR)
	{
		color = 31;
	}
	else
	{
		color = 37;
	}

	std::cout << "\033[" << color << "m" << message << "\033[0m" << std::endl;
}
