#pragma once

#include "Utils.h"
#include "EventArgs.h"
#include "XorStr.h"
#include "IPluginSDK.h"
#include "IObjectManager.h"
#include "IGameObject.h"
#include "IGame.h"
#include "IMouseLogic.h"
#include "IHud.h"
#include "INavMesh.h"
#include "IMainMenu.h"
#include "IEventManager.h"
#include "IWorld.h"
#include "ILogging.h"
#include "IObjectStats.h"
#include "IMenu.h"
#include "IMenuElement.h"
#include "IDrawings.h"
#include "IModuleManager.h"
#include "ObjectList.h"
#include "IBuff.h"
#include "ISpellInfo.h"
#include "ISpellInstance.h"
#include "IUnitComponentInfo.h"
#include "IInventorySlot.h"
#include "IRenderer.h"
#include "IPathController.h"
#include "IDamageLib.h"
#include "IOrbwalker.h"
#include "LeagueGlobals.h"
#include "IMinionHealthPrediction.h"
#include "ISpellData.h"
#include "ITargetSelector.h"
#include "ITargetspell.h"
#include "IChat.h"
#include "IGapclose.h"
#include "IDamageDrawings.h"
#include "IGapcloseMenu.h"
#include "ITargetspellMenu.h"
#include "IInterruptibleSpell.h"
#include "IInterruptibleSpellMenu.h"
#include "ISpellTargetingData.h"
#include "ISpellLogic.h"
#include "Spells.h"
#include "IPrediction.h"
#include "ICollision.h"
#include "IPermaShow.h"
#include "ICharacterDataStack.h"
#include "ITracker.h"
#include "Geometry.h"
#include "ISpellFarming.h"
#include "IMenuTab.h"
#include "ITabChild.h"
#include "IHealthPrediction.h"
#include "IEvade.h"
#include "IModule.h"
#include "IChampionScript.h"
#include "IMiscScript.h"
#include "IChampionManager.h"
#include "IInputLogic.h"

#define SDK_VERSION xorstr_("1.0.9")

#ifdef DIST_BUILD
#define DLOG(message)
#define CRASH_LOG(message)
#else
#define DLOG(message) g_logging->log(__FILE__, __FUNCTION__, __LINE__, (std::stringstream() << message).str())

//#define USE_CRASH_LOG
#ifdef USE_CRASH_LOG
#define CRASH_LOG(message) DLOG(message)
#else
#define CRASH_LOG(message)
#endif
#endif

extern IPluginSDK* g_pluginSDK;
extern IObjectManager* g_objectManager;
extern IGameObject* g_localPlayer;
extern IGame* g_game;
extern IHud* g_hud;
extern INavMesh* g_navMesh;
extern IMainMenu* g_mainMenu;
extern IEventManager* g_eventManager;
extern IWorld* g_world;
extern ILogging* g_logging;
extern IModuleManager* g_moduleManager;
extern IDrawings* g_drawings;
extern IRenderer* g_renderer;
extern IChat* g_chat;
extern IChampionManager* g_championManager;

#define DECLARE_SDK(pluginSDK) \
	g_pluginSDK = pluginSDK;   \
	g_objectManager = pluginSDK->objectManager(); \
	g_localPlayer = g_objectManager->localPlayer(); \
	g_game = pluginSDK->game(); \
	g_hud = pluginSDK->hud(); \
	g_navMesh = pluginSDK->navMesh(); \
	g_mainMenu = pluginSDK->mainMenu(); \
	g_eventManager = pluginSDK->eventManager(); \
	g_world = pluginSDK->world(); \
	g_logging = pluginSDK->logging(); \
	g_moduleManager = pluginSDK->moduleManager(); \
	g_drawings = pluginSDK->drawings(); \
	g_renderer = pluginSDK->renderer(); \
	g_chat = pluginSDK->chat(); \
	g_championManager = pluginSDK->championManager();

template<Events Event>
struct EventHandler
{
	static void subscribe() {}
	static void unsubscribe() {}
	static void emit() {}
};

#define DEFINE_EVENT_HANDLER(EventID, EventName, EventArgsType) \
template < > \
struct EventHandler<EventID> \
{ \
	static void subscribe(void* fn) \
	{ \
		g_eventManager->subscribe(HASH(xorstr_(#EventName)), fn); \
	} \
	static void subscribe(void(*fn)(EventArgsType*)) \
	{ \
		g_eventManager->subscribe(HASH(xorstr_(#EventName)), fn); \
	} \
	\
	static void unsubscribe(void(*fn)(EventArgsType*)) \
	{ \
		g_eventManager->unsubscribe(HASH(xorstr_(#EventName)), fn); \
	} \
	\
	static void emit(EventArgsType* args) \
	{ \
		g_eventManager->emit(HASH(xorstr_(#EventName)), args); \
	} \
};

DEFINE_EVENT_HANDLER(Events::GameUpdate, GameUpdate, GameUpdateEventArgs)
DEFINE_EVENT_HANDLER(Events::Present, Present, PresentEventArgs)
DEFINE_EVENT_HANDLER(Events::ResizeBuffers, ResizeBuffers, ResizeBuffersEventArgs)
DEFINE_EVENT_HANDLER(Events::OnObjectCreate, OnObjectCreate, OnObjectCreateEventArgs)
DEFINE_EVENT_HANDLER(Events::OnObjectDelete, OnObjectDelete, OnObjectDeleteEventArgs)
DEFINE_EVENT_HANDLER(Events::OnNewPath, OnNewPath, OnNewPathEventArgs)
DEFINE_EVENT_HANDLER(Events::OnDraw, OnDraw, OnDrawEventArgs)
DEFINE_EVENT_HANDLER(Events::OnProcessSpell, OnProcessSpell, OnProcessSpellEventArgs)
DEFINE_EVENT_HANDLER(Events::OnStopCast, OnStopCast, OnStopCastEventArgs)
DEFINE_EVENT_HANDLER(Events::OnGapcloser, OnGapcloser, OnGapcloserEventArgs)
DEFINE_EVENT_HANDLER(Events::OnSpellImpact, OnSpellImpact, OnSpellImpactEventArgs)
DEFINE_EVENT_HANDLER(Events::OnTargetspell, OnTargetspell, OnTargetspellEventArgs)
DEFINE_EVENT_HANDLER(Events::OnOrbwalkerPreAttack, OnOrbwalkerPreAttack, OnOrbwalkerPreAttackEventArgs)
DEFINE_EVENT_HANDLER(Events::OnInterruptibleSpell, OnInterruptibleSpell, OnInterruptibleSpellEventArgs)
DEFINE_EVENT_HANDLER(Events::OnOrbwalkerPostAttack, OnOrbwalkerPostAttack, OnOrbwalkerPostAttackEventArgs)
DEFINE_EVENT_HANDLER(Events::OnOrbwalkerPreMove, OnOrbwalkerPreMove, OnOrbwalkerPreMoveEventArgs)
DEFINE_EVENT_HANDLER(Events::OnVisibilityChanged, OnVisibilityChanged, OnVisibilityChangedEventArgs)
DEFINE_EVENT_HANDLER(Events::OnRenderMouseOvers, OnRenderMouseOvers, OnRenderMouseOversEventArgs)
DEFINE_EVENT_HANDLER(Events::OnOrbwalkerCancelEvent, OnOrbwalkerCancelEvent, OnOrbwalkerCancelEventArgs)
DEFINE_EVENT_HANDLER(Events::OnPlayerAttack, OnPlayerAttack, OnPlayerAttackEventArgs)
DEFINE_EVENT_HANDLER(Events::OnPlayerMove, OnPlayerMove, OnPlayerMoveEventArgs)
DEFINE_EVENT_HANDLER(Events::OnTriggerSpell, OnTriggerSpell, OnTriggerSpellEventArgs);
DEFINE_EVENT_HANDLER(Events::OnWndProc, OnWndProc, OnWndProcEventArgs);
DEFINE_EVENT_HANDLER(Events::OnCastDashSpell, OnCastDashSpell, OnCastDashSpellEventArgs);
DEFINE_EVENT_HANDLER(Events::OnFinishCast, OnFinishCast, OnFinishCastEventArgs);
DEFINE_EVENT_HANDLER(Events::OnIssueClick, OnIssueClick, OnIssueClickEventArgs);
DEFINE_EVENT_HANDLER(Events::OnGetSpellPositionMouse, OnGetSpellPositionMouse, OnGetSpellPositionMouseEventArgs);
DEFINE_EVENT_HANDLER(Events::OnScreenPointToTargetResolver, OnScreenPointToTargetResolver, OnScreenPointToTargetResolverEventArgs);
DEFINE_EVENT_HANDLER(Events::OnPlayerAttackMove, OnPlayerAttackMove, OnPlayerAttackMoveEventArgs);

#define COLOR_ARGB(a,r,g,b) \
    ((DWORD)((((a)&0xff)<<24)|(((b)&0xff)<<16)|(((g)&0xff)<<8)|((r)&0xff)))
#define COLOR_RGBA(r,g,b,a) COLOR_ARGB(a,r,g,b)

#define COLOR_RGB(r, g, b) (((int)(r) << 16) | ((int)(g) << 8) | (int)(b))



struct ColorCheckbox
{
	MenuElementPtr checkbox;
	MenuElementPtr color;
};

inline ColorCheckbox addColorCheckbox(TabChildPtr menu, const std::string& name, float r, float g, float b, float a, bool defaultValue)
{
	ColorCheckbox result;
	result.checkbox = menu->addCheckBox(name + xorstr_("box"), xorstr_("Draw ") + name, defaultValue);
	result.color = menu->addColorPicker(name + xorstr_("color"), name + xorstr_(" Color"), r, g, b, a);
	return result;
}