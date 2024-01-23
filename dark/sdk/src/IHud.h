#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include <memory>

class IInputLogic;
class IMouseLogic;
class ISpellLogic;
class IHud
{
public:
	virtual ~IHud() = default;

public:
	virtual Vector3 mousePosition() = 0;
	virtual unsigned short hoveredMouseIndex() = 0;

	virtual float currentZoom() = 0;

	virtual void setZoomValue(float value) = 0;

	virtual float zoomValue() = 0;

	virtual std::unique_ptr<ISpellLogic> spellLogic() = 0;

	virtual std::unique_ptr<IMouseLogic> mouseLogic() = 0;

	virtual std::unique_ptr<IInputLogic> inputLogic() = 0;

	virtual bool isLeagueFocused() = 0;
};