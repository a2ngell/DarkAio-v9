#pragma once

#include <string>
#include <memory>
#include <vector>

#include "Enums.h"

class IMenu;
class IMenuElement;
class IMenuTab;
class ITabChild;
typedef IMenu* MenuPtr;
typedef IMenuElement* MenuElementPtr;
typedef IMenuTab* MenuTabPtr;
typedef ITabChild* TabChildPtr;
class IMenu
{
public:
	virtual ~IMenu() = default;
	
public:
	virtual IMenuTab* createTab(const std::string& elementName, const std::string& displayName) = 0;
	virtual void removeTab(IMenuTab* tab) = 0;

	virtual IMenuTab* tab(const std::string& elementName) = 0;
	virtual std::vector<IMenuTab*> tabs() = 0;
};