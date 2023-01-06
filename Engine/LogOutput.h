#pragma once

#include <iostream>

enum class LogMessage
{
	LOG,
	WARNING,
	ERROR
};

void DebugLog(LogMessage logDebugType, const std::string& message);