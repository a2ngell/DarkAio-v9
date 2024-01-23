#pragma once

class ITargetspellMenu
{
public:
	virtual ~ITargetspellMenu() = default;

public:
	virtual bool isSpellEnabled(uint32_t spellHash) = 0;
};