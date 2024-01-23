#pragma once

#include <string>
#include <memory>

class ISpellData;
class ISpellInfo
{
public:
	virtual ~ISpellInfo() = default;
	
public:
	virtual uintptr_t ptr() = 0;

	virtual std::string name() = 0;

	virtual std::unique_ptr<ISpellData> data() = 0;

	virtual uint32_t nameHash() = 0;
};