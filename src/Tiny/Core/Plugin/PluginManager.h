#ifndef TINY_CORE_PLUGIN_PLUGINMANAGER_H
#define TINY_CORE_PLUGIN__PLUGINMANAGER_H

#include "Tiny/Core/Plugin/AbstractImporter.h"

#include <unordered_map>
#include <string>

namespace Tiny { namespace PLUGIN {
	template<class Plugin> class PluginManager {
	public:
		static PluginManager& Instance() {
			static PluginManager inst;
			return inst;
		}

		void RegisterPlugin(const std::string& name, Plugin* p) {
			if (_map.find(name) != _map.end()) {
				throw std::exception(("Duplicated plugin: " + name).c_str());
			}
			_map[name] = p;
		}

		Plugin* GetPlugin(const std::string& name) {
			auto p = _map.find(name);
			if (p == _map.end()) {
				throw std::exception(("No plugin: " + name).c_str());
			}
			return p->second;
		}

	private:
		std::unordered_map<std::string, Plugin*> _map;
	};

	using ImporterManager = PluginManager<AbstractImporter>;

	void Init();
}
}

#endif // !TINY_CORE_PLUGINMANAGER_H
