#ifndef TINY_CORE_PLUGIN_PLUGINMANAGER_H
#define TINY_CORE_PLUGIN__PLUGINMANAGER_H

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
			_map[name] = p;
		}

		Plugin* GetPlugin(const std::string& name) {
			auto p = _map.find(name);
			if (p == _map.end()) {
				throw std::exception("No plugin: " + name);
			}
			return p->second;
		}

	private:
		std::unordered_map<std::string, Plugin*> _map;
	};
}
}

#endif // !TINY_CORE_PLUGINMANAGER_H
