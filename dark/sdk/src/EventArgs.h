#pragma once

#include <optional>

#include "IGameObject.h"
#include "Vector2.h"
#include "Vector3.h"
#include "ICastInfo.h"
#include "IRenderer.h"
#include "IGapclose.h"

struct GameUpdateEventArgs
{
	
};

struct PresentEventArgs
{

};

struct ResizeBuffersEventArgs
{

};

struct OnObjectCreateEventArgs
{
	IGameObject* object;
};

struct OnObjectDeleteEventArgs
{
	IGameObject* object;
};

struct OnNewPathEventArgs
{
	IGameObject* object;
	std::vector<Vector3> points;

	PathType type;

	std::optional<float> dashSpeed;
};

struct OnDrawEventArgs
{
	
};

struct OnProcessSpellEventArgs
{
	IGameObject* caster;
	std::unique_ptr<ICastInfo> castInfo;
};

struct OnStopCastEventArgs
{
	std::unique_ptr<ICastInfo> castInfo;
	bool animationCancel;
	bool execute;
	bool force;
	bool missileDestroy;
	int missileID;
};

struct OnWndProcEventArgs
{
	uint32_t msg;
	uint32_t wParam;
	uint32_t lParam;
};

struct OnGapcloserEventArgs
{
	uint32_t spellHash;
	IGameObject* caster;
	IGameObject* nearestAlly;
	bool toLocalPlayer;
	PathType type;
	std::vector<Vector3> path;
	Vector3 endPosition;
	float pathLength;
	float estimatedDashSpeed;
	int arrivalTick;
};


struct OnCastDashSpellEventArgs
{
	OnProcessSpellEventArgs* processSpellArgs;
	GapcloseInfo* info;
	Vector3 startPosition;
	Vector3 endPosition;
};

struct OnTargetspellEventArgs
{
	uint32_t spellHash;
	IGameObject* caster;
	IGameObject* target;
	SpellSlot slot;

	bool waitCastDelay; // important for missile target spells
	float castDelay;

	std::vector<TargetspellType> type;
};

struct OnSpellImpactEventArgs
{
	std::unique_ptr<ICastInfo> castInfo;
};

struct OnFinishCastEventArgs
{
	std::unique_ptr<ICastInfo> castInfo;
	IGameObject* owner;
};

struct OnInterruptibleSpellEventArgs
{
	IGameObject* caster;
	SpellSlot slot;
	int startTime;
	int endTime;
	DangerLevel level;
};

struct OnOrbwalkerPreAttackEventArgs
{
	IGameObject* target;
	bool process;
};

struct OnOrbwalkerPostAttackEventArgs
{
	IGameObject* target;
};

struct OnOrbwalkerPreMoveEventArgs
{
	Vector3 position;
	bool process;
};

struct OnOrbwalkerCancelEventArgs
{
	
};

struct OnVisibilityChangedEventArgs
{
	IGameObject* object;
	bool isVisible;
};

struct OnRenderMouseOversEventArgs
{
	tLeagueScreenBuffer screenBufferPtr;
};

struct OnPlayerMoveEventArgs
{
	Vector3 position;
	bool process;
};

struct OnIssueClickEventArgs
{
	bool process;
};

struct OnPlayerAttackEventArgs
{
	Vector3 position;
	IGameObject* target;
	bool process;
};

struct OnPlayerAttackMoveEventArgs
{
	Vector3 position;
	bool process;
};

struct OnTriggerSpellEventArgs
{
	SpellSlot slot;
	int state;
	bool process;
};

struct OnGetSpellPositionMouseEventArgs
{
	Vector3* position;
};

struct OnScreenPointToTargetResolverEventArgs
{
	__int64 screenX;
	__int64 screenY;
	uintptr_t* outTargetAddress1;
	uintptr_t* outTargetAddress2;
};