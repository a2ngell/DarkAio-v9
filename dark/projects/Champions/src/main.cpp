#include <Windows.h>
#include <string>

#include <SDK/src/SDK.h>
#include <SDK/src/XorStr.h>

#include "Version.h"

#include "Seraphine.h"
#include "Sivir.h"
#include "Katarina.h"
#include "Riven.h"
#include "Aatrox.h"
#include "Amumu.h"
#include "Varus.h"
#include "Ezreal.h"
#include "Draven.h"
#include "Jinx.h"

#define CHAMPION_SCRIPT(Champion) \
class Champion##Script : public IChampionScript \
{ \
public: \
	Champion##Script() = default; \
	~Champion##Script() = default; \
public: \
	void load() override { return Champion::load(); } \
	void unload() override { return Champion::unload(); } \
	ChampionID championID() override { return ChampionID::Champion; } \
};

CHAMPION_SCRIPT(Katarina);
CHAMPION_SCRIPT(Riven);
CHAMPION_SCRIPT(Aatrox);
CHAMPION_SCRIPT(Amumu);
CHAMPION_SCRIPT(Varus);
CHAMPION_SCRIPT(Ezreal);
CHAMPION_SCRIPT(Draven);
CHAMPION_SCRIPT(Jinx);
//CHAMPION_SCRIPT(Seraphine);

std::vector<std::unique_ptr<IChampionScript>>* g_champions = nullptr;

extern "C" __declspec(dllexport) std::vector<std::unique_ptr<IChampionScript>>*supportedChampions()
{
	if (g_champions != nullptr)
		return g_champions;
	g_champions = new std::vector<std::unique_ptr<IChampionScript>>();
	//g_champions->push_back(std::make_unique<SivirScript>());
	//g_champions->push_back(std::make_unique<SeraphineScript
	g_champions->push_back(std::make_unique<AmumuScript>());
	g_champions->push_back(std::make_unique<VarusScript>());
	g_champions->push_back(std::make_unique<AatroxScript>());
	g_champions->push_back(std::make_unique<KatarinaScript>());
	g_champions->push_back(std::make_unique<EzrealScript>());
	g_champions->push_back(std::make_unique<DravenScript>());
	g_champions->push_back(std::make_unique<JinxScript>());
	//g_champions->push_back(std::make_unique<RivenScript>());
	return g_champions;
}

extern "C" __declspec(dllexport) PluginType scriptType()
{
	return PluginType::Champions;
}

extern "C" __declspec(dllexport) std::string name()
{
	return xorstr_("Dark Aio");
}

extern "C" __declspec(dllexport) std::string author()
{
	return xorstr_("Dark");
}

extern "C" __declspec(dllexport) std::string version()
{
	return VERSION;
}

extern "C" __declspec(dllexport) std::string description()
{
	std::stringstream ss;
	ss << xorstr_("Supported champions: ") << std::endl;
	for (auto& champion : *supportedChampions())
	{
		ss << xorstr_("- ") << toString(champion->championID()) << std::endl;
	}
	return ss.str();
}

extern "C" __declspec(dllexport) bool load(IPluginSDK * pluginSDK)
{
	DECLARE_SDK(pluginSDK);
	return true;
}

extern "C" __declspec(dllexport) bool unload()
{
	delete g_champions;
	return true;
}

extern "C" __declspec(dllexport) std::string sdkVersion()
{
	return SDK_VERSION;
}

