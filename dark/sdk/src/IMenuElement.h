#pragma once

#include <string>
#include <Windows.h>

class IMenuElement
{
public:
	virtual ~IMenuElement() = default;

public:
	virtual const std::string& elementName() const = 0;
	virtual const std::string& displayName() const = 0;
	
	virtual bool isVisible() const = 0;
	
	virtual bool getBool() const = 0;
	virtual int getInt() const = 0;
	virtual DWORD getColor() const = 0;
	virtual int getHexColor() const = 0;
	virtual float getFloat() const = 0;
	virtual std::string getString() const = 0;
	virtual bool isPressed() const = 0;

	virtual void setDisplayName(const std::string& displayName) = 0;

	virtual void setVisibility(const bool value) = 0;

	virtual void setBool(bool value) = 0;
	virtual void setInt(int value) = 0;
	virtual void setColor(DWORD color) = 0;
	virtual void setHexColor(int color) = 0;
	virtual void setFloat(float value) = 0;
	virtual void setString(const std::string& string) = 0;
};