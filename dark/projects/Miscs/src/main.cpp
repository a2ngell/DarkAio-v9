#include <SDK/src/SDK.h>
#include <SDK/src/XorStr.h>

#include "Version.h"
#include "Awareness.h"
#include "Predection.h"

#define MISC_SCRIPT(scriptName) \
class scriptName##Script : public IMiscScript \
{ \
public: \
	scriptName##Script() = default; \
	~scriptName##Script() = default; \
public: \
	void load() override { return scriptName::load(); } \
	void unload() override { return scriptName::unload(); } \
	std::string name() override { return xorstr_(#scriptName); } \
};

MISC_SCRIPT(Awareness);
//MISC_SCRIPT(Predection);

std::vector<std::unique_ptr<IMiscScript>>* g_scripts = nullptr;

extern "C" __declspec(dllexport) std::vector<std::unique_ptr<IMiscScript>>*miscScripts()
{
	if (g_scripts != nullptr)
		return g_scripts;

	g_scripts = new std::vector<std::unique_ptr<IMiscScript>>();
	g_scripts->push_back(std::make_unique<AwarenessScript>());
	//g_scripts->push_back(std::make_unique<PredectionScript>());
	return g_scripts;
}

extern "C" __declspec(dllexport) PluginType scriptType()
{
	return PluginType::Misc;
}

extern "C" __declspec(dllexport) std::string name()
{
	return xorstr_("Dark Miscs");
}

extern "C" __declspec(dllexport) std::string description()
{
	std::stringstream ss;
	ss << xorstr_("Supported scripts: ") << std::endl;
	ss << xorstr_("- Awareness") << std::endl;
	return ss.str();
}

extern "C" __declspec(dllexport) std::string author()
{
	return xorstr_("Dark");
}

extern "C" __declspec(dllexport) std::string version()
{
	return VERSION;
}

extern "C" __declspec(dllexport) bool load(IPluginSDK * pluginSDK)
{
	DECLARE_SDK(pluginSDK);

	return true;
}

extern "C" __declspec(dllexport) bool unload()
{
	delete g_scripts;
	return true;
}

extern "C" __declspec(dllexport) std::string sdkVersion()
{
	return SDK_VERSION;
}

