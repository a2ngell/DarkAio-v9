#pragma once

#include <string>

class ILogging
{
public:
	virtual ~ILogging() = default;
	
public:
	virtual void log(const std::string& file, const std::string& function, int line, const std::string& message) = 0;
};