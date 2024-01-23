#pragma once

#include "Vector2.h"

class IInputLogic
{
public:
	virtual ~IInputLogic() = default;

public:
	virtual bool issueClick(uintptr_t order, const Vector2& position, bool triggerEvent = true) = 0;
};