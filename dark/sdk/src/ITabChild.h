#pragma once

#include <string>
#include <memory>
#include <vector>

#include "Enums.h"

class IMenuElement;
typedef IMenuElement* MenuElementPtr;

class ITabChild
{
public:
	virtual ~ITabChild() = default;

public:
	virtual MenuElementPtr addSlider(const std::string& elementName, const std::string& displayName, const int defaultValue, const int i_iMinValue, const int maxValue) = 0;
	virtual MenuElementPtr addSliderF(const std::string& elementName, const std::string& displayName, const float defaultValue, const float minValue, const float maxValue) = 0;
	virtual MenuElementPtr addCheckBox(const std::string& elementName, const std::string& displayName, const bool defaultValue) = 0;
	virtual MenuElementPtr addKeybind(const std::string& elementName, const std::string& displayName, Key key) = 0;
	virtual MenuElementPtr addComboBox(const std::string& elementName, const std::string displayName, const std::vector<std::string>& string, const std::string& defaultItem) = 0;
	virtual MenuElementPtr addColorPicker(const std::string& elementName, const std::string displayName, const float defaultR, const float defaultG, const float defaultB, const float defaultA) = 0;
	virtual MenuElementPtr addLabel(const std::string& elementName, const std::string& displayNamee, bool bold = false) = 0;
	virtual MenuElementPtr addSameLine() = 0;

	virtual MenuElementPtr element(const std::string& elementName) = 0;
	virtual std::vector<MenuElementPtr> elements() = 0;
	virtual void removeElement(MenuElementPtr element) = 0;
};