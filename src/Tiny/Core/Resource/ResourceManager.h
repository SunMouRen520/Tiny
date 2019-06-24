#ifndef TINY_CORE_RESOURCEMANAGER_H
#define TINY_CORE_RESOURCEMANAGER_H

#include <string>
#include <unordered_map>
#include "Tiny/Graphics/Texture/ImageData.h"
#include "Tiny/Graphics/Shader/Shader.h"
#include "Tiny/Graphics/Texture/TextureData.h"

namespace Tiny {
	class ResourceLoader{
	public:
		static ResourceLoader& Instance();
		//load image data
		std::shared_ptr<Graphics::ImageData> LoadImageData(const std::string&);
		//when there is no object to refer to image data, recyle the image data
		void RecyleImageData();
		//load shader program
		std::shared_ptr<Graphics::Shader> LoadShader(const std::string&, const std::string&);
		//recyle shader program
		void RecyleShader();
		//load texture;
		std::shared_ptr<Graphics::Texture> LoadTexture(const std::string&, Graphics::TextureType);
		//recyle texture
		void RecyleTexture();
	private:
		/*resource manager should use hash stringid as the key, develop in the future*/
		//imagepath->imagedata
		std::unordered_map<std::string, std::shared_ptr<Graphics::ImageData>> imageCache;
		//shaderpath->shader
		std::unordered_map<std::string, std::shared_ptr<Graphics::Shader>> shaderCache;
		//imagepath->texture
		std::unordered_map<std::string, std::shared_ptr<Graphics::Texture>> textureCache;
	};
}

#endif // !TINY_CORE_RESOURCEMANAGER_H
