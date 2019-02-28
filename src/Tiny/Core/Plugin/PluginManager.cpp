#include "Tiny/Core/Plugin/PluginManager.h"

#include "rapidjson/document.h"
#include "Tiny/FileSystem/FileSystem.h"

#include "Tiny/config.h"

#include "Tiny/Core/Service.h"

#ifdef TINY_PLATFORM_WINDOWS
#include "windows.h"
#undef GetObject
#endif

namespace Tiny { namespace PLUGIN {
#ifdef TINY_PLATFORM_WINDOWS
	typedef void* (*Instance) (void);
	static void* LoadPluginInstance(const std::string& dll) {
		HINSTANCE hinstDLL;
		Instance Factory;
		void* Plugin = NULL;

		hinstDLL = LoadLibrary((dll + ".dll").c_str());

		if (hinstDLL != NULL)
		{
			Factory = (Instance)GetProcAddress(hinstDLL, "Create");

			if (Factory != NULL)
				Plugin = (Factory());
		}
		return Plugin;
	}
#else

#endif

	void Init() {
		std::unordered_map<std::string, AbstractImporter*> cache;
		FileSystem::SetBaseDir(FileSystem::GetExePath());
		rapidjson::Document config;
		std::string data = FileSystem::ReadChar("plugin/PluginConfig.json");
		//std::string data(" { \"PNGImporter\":\"STBPlugin\", \"JPGImporter\" : \"STBPlugin\", }");
		if (config.Parse(data.c_str()).HasParseError()) {
			Service::Log().E("plugin/PluginConfig.json parse failed!");
			rapidjson::ParseErrorCode code = config.GetParseError();
			return;
		}

		for (auto& m : config.GetObject()) {
			auto& subConfig = m.value.GetObject();
			std::string cfgName = m.name.GetString();
			if (!cfgName.compare("Importer")) {
				for (auto& cfg : subConfig) {
					std::string dllName = cfg.value.GetString();
					auto loadedInst = cache.find(dllName);
					if (loadedInst != cache.end()) {
						PluginManager<AbstractImporter>::Instance().RegisterPlugin(cfg.name.GetString(), loadedInst->second);
						continue;
					}
					AbstractImporter *pImporter = (AbstractImporter*)LoadPluginInstance(dllName);
					if (pImporter) {
						PluginManager<AbstractImporter>::Instance().RegisterPlugin(cfg.name.GetString(), pImporter);
						cache[dllName] = pImporter;
					}
					else {
						Service::Log().E("Cannot Load Importer:{}", cfg.value.GetString());
					}

				}
			}
		}
	}
}
}
