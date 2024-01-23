#pragma once

#include <memory>
#include <string>
#include <vector>

class ITabChild;
class IMenuTab
{
public:
	virtual ~IMenuTab() = default;

public:
	virtual ITabChild* createTabChild(const std::string& elementName, const std::string& displayName, bool champBased) = 0;
	virtual ITabChild* tabChild(const std::string& elementName) = 0;
	virtual std::vector<ITabChild*> tabChildren() = 0;
	virtual void removeTabChild(ITabChild* tabChild) = 0;
};