#include "Tiny/config.h"

#include "Tiny/Core/Resource/ResourceManager.h"
#include "Tiny/Core/Plugin/PluginManager.h"
#include "Tiny/FileSystem/Utility.h"

#include "IronBranch/Utility/String.h"
#include "IronBranch/Utility/Log.h"

#include "Tiny/FileSystem/FileSystem.h"

#ifdef TINY_PLATFORM_WINDOWS
#undef GameObject
#undef LoadImage
#endif

#include "rapidjson/document.h"

using IronBranch::Optional;


namespace Tiny {
	ResourceLoader& ResourceLoader::Instance() {
		static ResourceLoader inst;
		return inst;
	}

	void ResourceLoader::Init() {
		rapidjson::Document config;
		std::string data = FileSystem::ReadChar("plugin/ImporterDef.json");
		config.Parse(data.c_str());

		for (auto& m : config.GetObject()) {
			_fileSuffixToPlugin[m.name.GetString()] = m.value.GetString();
		}
	}

	Optional<Graphics::ImageData> ResourceLoader::LoadImage(const std::string& path) {
		std::string fileType = FileSystem::FileType(path);
		if (fileType.empty()) {
			IronBranch::Utility::Log::E("ResourceLoader:LoadImage without file type:{}", path);
			return IronBranch::NoInit;
		}

		auto pluginName = _fileSuffixToPlugin.find(fileType);
		if (pluginName == _fileSuffixToPlugin.end()) {
			IronBranch::Utility::Log::E("ResourceLoader:No loader for : {}", fileType);
			return IronBranch::NoInit;
		}

		PLUGIN::AbstractImporter *p = nullptr;
		try {
			p = PLUGIN::PluginManager<PLUGIN::AbstractImporter>::Instance().GetPlugin(pluginName->second);
		}
		catch (std::exception e) {
			IronBranch::Utility::Log::E(e.what());
			return IronBranch::NoInit;
		}
		
		try {
			return p->Image(FileSystem::GetResourceFullPath(path));
		}
		catch (PLUGIN::ImportFailed e) {
			IronBranch::Utility::Log::E("ResourceLoader:Failed to resolve Image: {}", e.what());
		}
		return IronBranch::NoInit;
	}
}