#pragma once

#include <memory>
#include <string>
#include <vector>

class IMenuTab;
class IMenu;
class IMainMenu
{
public:
	virtual ~IMainMenu() = default;
	
public:
	virtual IMenu* createMenu(const std::string& elementName, const std::string& displayName) = 0;
	virtual void removeMenu(const std::string& elementName) = 0;
	virtual void removeMenu(IMenu* menu) = 0;
	virtual IMenu* menu(const std::string& elementName) = 0;
	virtual std::vector<IMenu*> menus() = 0;

	virtual IMenu* settingsMenu() = 0;
	virtual IMenuTab* generalSettings() = 0;

	virtual IMenu* operator[](const std::string& elementName) = 0;

	virtual bool isShown() = 0;
};