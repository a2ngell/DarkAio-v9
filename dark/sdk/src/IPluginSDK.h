#pragma once

#include "IObjectManager.h"
#include "IGame.h"
#include "IHud.h"
#include "INavMesh.h"
#include "IMainMenu.h"
#include "IEventManager.h"
#include "IWorld.h"
#include "ILogging.h"
#include "IModuleManager.h"
#include "IDrawings.h"
#include "IRenderer.h"
#include "IChat.h"
#include "IChampionManager.h"

class IPluginSDK
{
public:
	virtual ~IPluginSDK() = default;

public:
	virtual IObjectManager* objectManager() = 0;
	virtual IGame* game() = 0;
	virtual IHud* hud() = 0;
	virtual INavMesh* navMesh() = 0;
	virtual IMainMenu* mainMenu() = 0;
	virtual IEventManager* eventManager() = 0;
	virtual IWorld* world() = 0;
	virtual ILogging* logging() = 0;
	virtual IModuleManager* moduleManager() = 0;
	virtual IDrawings* drawings() = 0;
	virtual IRenderer* renderer() = 0;
	virtual IChat* chat() = 0;
	virtual IChampionManager* championManager() = 0;
};