#pragma once

#include <string>

class IMiscScript
{
public:
	virtual ~IMiscScript() = default;

public:
	virtual void load() = 0;
	virtual void unload() = 0;
	virtual std::string name() = 0;
};