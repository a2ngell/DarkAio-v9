#pragma once

class IGapcloseMenu
{
public:
	virtual ~IGapcloseMenu() = default;

public:
	virtual bool isSpellEnabled(uint32_t hash) = 0;
};