#pragma once

#include <memory>
#include <string>
#include <vector>

class ICharacterStackData
{
public:
	virtual ~ICharacterStackData() = default;

public:
	virtual std::string model() = 0;
	virtual unsigned int skin() = 0;
	virtual unsigned char gear() = 0;

	virtual void setSkin(unsigned int skin) = 0;
	virtual void setGear(unsigned char gear) = 0;
};

class ICharacterDataStack
{
public:
	virtual ~ICharacterDataStack() = default;

public:
	virtual void update(bool change) = 0;
	
	virtual void push(const std::string& model, int skin) = 0;

	virtual std::vector<std::unique_ptr<ICharacterStackData>> stack() = 0;

	virtual void clearStack() = 0;

	virtual std::unique_ptr<ICharacterStackData> baseSkin() = 0;
};