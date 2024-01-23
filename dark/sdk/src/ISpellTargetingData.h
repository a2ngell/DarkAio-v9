#pragma once

#include "Vector3.h"

class ISpellTargetingData
{
public:
	virtual ~ISpellTargetingData() = default;

public:
	virtual unsigned short casterIndex() = 0;

	virtual unsigned short targetIndex() = 0;

	virtual Vector3 startPos() = 0;

	virtual Vector3 endPos() = 0;

	virtual Vector3 clickedPos() = 0;

	virtual Vector3 unknownPos() = 0;

	virtual void setCasterIndex(int index) = 0;
	
	virtual void setTargetIndex(int index) = 0;

	virtual void setStartPos(const Vector3& pos) = 0;

	virtual void setEndPos(const Vector3& pos) = 0;

	virtual void setClickedPos(const Vector3& pos) = 0;

	virtual void setUnknownPos(const Vector3& pos) = 0;
};