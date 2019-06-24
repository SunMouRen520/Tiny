#include <memory>
#include "TextureData.h"
#include "Tiny/Core/Resource/ResourceManager.h"
#include "Tiny/Core/Service.h"


namespace Tiny {
	namespace Graphics {
		std::shared_ptr<Texture> Texture::Texture2D(const std::string& resPath, TextureType type)
		{
			std::shared_ptr<Texture> texture = ResourceLoader::Instance().LoadTexture(resPath, type);
			return texture;
		}
	}
}