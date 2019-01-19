#ifndef TINY_CORE_RESOURCEMANAGER_H
#define TINY_CORE_RESOURCEMANAGER_H

#include "Tiny/Graphics/Texture/TextureData.h"
#include "IronBranch/Notion/Optional.h"

#include <string>
#include <unordered_map>

namespace Tiny {
	class ResourceLoader{
	public:
		static ResourceLoader& Instance();
		void Init();
		~ResourceLoader() = default;

		//Graphics::TextureData LoadTexture(const std::string& path);

		//LoadImage is a tempory interface. After the skeleton of engine finished, we should load texture instead of load image directly.
		IronBranch::Optional<Graphics::ImageData> LoadImage(const std::string& path);

	private:
		ResourceLoader() = default;

	private:
		std::unordered_map<std::string, std::string> _fileSuffixToPlugin;
	};
}

#endif // !TINY_CORE_RESOURCEMANAGER_H
