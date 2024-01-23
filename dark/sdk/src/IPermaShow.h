#pragma once

#include "IMenuElement.h"
#include "IMenu.h"

class IPermaShow
{
public:
	virtual ~IPermaShow() = default;

public:
	virtual void addToggle(const std::string& name, MenuElementPtr checkbox, MenuElementPtr keybind, bool showDefault = true) = 0;

	virtual void addToggle(const std::string& name, MenuElementPtr keybind, bool showDefault = true) = 0;

	virtual void removeToggle(const std::string& name) = 0;
};