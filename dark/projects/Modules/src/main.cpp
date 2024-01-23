#include <SDK/src/SDK.h>
#include <SDK/src/XorStr.h>

#include "Orbwalker.h"
#include "Version.h"
#include "Predection.h"

#define MODULE_SCRIPT(lowerName, upperName) \
	static upperName* g_##lowerName = nullptr; \
	class upperName##Module : public IModule \
	{ \
	public: \
		upperName##Module() = default; \
		~upperName##Module() {if (g_##lowerName) delete g_##lowerName; } \
	public: \
		void load() override { g_##lowerName = new upperName; g_moduleManager->set##upperName(g_##lowerName); } \
		void unload() override { delete g_##lowerName; g_##lowerName = nullptr; } \
		ModuleType type() const { return ModuleType::##upperName; } \
};

MODULE_SCRIPT(orbwalker, Orbwalker);
MODULE_SCRIPT(Predection, Predection);

std::vector<std::unique_ptr<IModule>>* g_modules = nullptr;


extern "C" __declspec(dllexport) std::vector<std::unique_ptr<IModule>>*supportedModules()
{
	if (g_modules) return g_modules;

	g_modules = new std::vector<std::unique_ptr<IModule>>();
	g_modules->push_back(std::make_unique<OrbwalkerModule>());
	return g_modules;
}

extern "C" __declspec(dllexport) PluginType scriptType()
{
	return PluginType::Modules;
}

extern "C" __declspec(dllexport) std::string name()
{
	return xorstr_("Dark Core Modules");
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
	return std::string(xorstr_("Description"));
}

extern "C" __declspec(dllexport) bool load(IPluginSDK * pluginSDK)
{
	DECLARE_SDK(pluginSDK);

	//EventHandler<Events::OnProcessSpell>::subscribe(onProcessSpell);
	//EventHandler<Events::GameUpdate>::subscribe(onUpdate);

	return true;
}

extern "C" __declspec(dllexport) bool unload()
{
	//EventHandler<Events::OnProcessSpell>::unsubscribe(onProcessSpell);
	//EventHandler<Events::GameUpdate>::unsubscribe(onUpdate);

	delete g_modules;

	return true;
}

extern "C" __declspec(dllexport) std::string sdkVersion()
{
	return SDK_VERSION;
}