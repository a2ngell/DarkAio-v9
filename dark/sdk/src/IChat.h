#pragma once

#include <string>

class IChat
{
public:
	virtual ~IChat() = default;

public:
	virtual bool isOpen() = 0;

	virtual void printChat(const char* message, unsigned int color) = 0;
};