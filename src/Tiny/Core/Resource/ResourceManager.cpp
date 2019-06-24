#include "ResourceManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../plugin/STB/stb_image.h"
#include "Tiny/Core/Service.h"
#include <memory>

namespace Tiny {
	ResourceLoader& ResourceLoader::Instance()
	{
		static ResourceLoader inst;
		return inst;
	}

	std::shared_ptr<Graphics::ImageData> ResourceLoader::LoadImageData(const std::string& imagePath)
	{
		if (imageCache.find(imagePath) != imageCache.end())
			return imageCache[imagePath];

		int width = 0, height = 0, channels = 0;

		std::uint8_t* data = stbi_load(imagePath.c_str(), &width, &height, &channels, 0);
		if (!data)
		{
			Service::Log().W("load image error, path:{}", imagePath);
			return nullptr;
		}

		Tiny::Graphics::PixelFormat pf;
		if (channels == 1){
			pf = Tiny::Graphics::PixelFormat::RGB332;
		}
		else if (channels == 3) {
			pf = Tiny::Graphics::PixelFormat::RGB888;
		}
		else if (channels == 4) {
			pf = Tiny::Graphics::PixelFormat::RGBA8888;
		}
		else {
			pf = Tiny::Graphics::PixelFormat::UNKNOWN;
		}

		std::shared_ptr<UnsignedByte> _data(data, stbi_image_free);
		std::shared_ptr<Graphics::ImageData> imageData = std::make_shared<Graphics::ImageData>(_data, pf, Math::Vector2i(width, height));
		
		imageCache[imagePath] = imageData;

		return imageData;
	}

	void ResourceLoader::RecyleImageData()
	{
		for (auto it = imageCache.begin(); it != imageCache.end();)
		{
			if (it->second->_data.unique())
			{
				it->second.reset();
				imageCache.erase(it++);
			}
			else
			{
				it++;
			}
		}
	}

	std::shared_ptr<Graphics::Shader> ResourceLoader::LoadShader(const std::string& vpath, const std::string& fpath)
	{
		std::string pathkey = vpath + fpath;
		if (shaderCache.find(pathkey) != shaderCache.end())
			return shaderCache[pathkey];

		std::shared_ptr<Graphics::Shader> shader = std::make_shared<Graphics::Shader>(vpath, fpath);
		shaderCache[pathkey] = shader;

		return shader;
	}

	void ResourceLoader::RecyleShader()
	{
		for (auto it = shaderCache.begin(); it != shaderCache.end();)
		{
			if (it->second.unique())
			{
				it->second.reset();
				shaderCache.erase(it++);
			}
			else
			{
				it++;
			}
		}
	}

	std::shared_ptr<Graphics::Texture> ResourceLoader::LoadTexture(const std::string& respath, Graphics::TextureType type)
	{
		if (textureCache.find(respath) != textureCache.end())
			return textureCache[respath];

		std::shared_ptr<Graphics::Texture> texture = std::make_shared<Graphics::Texture>();
		texture->_img = ResourceLoader::Instance().LoadImageData(respath);
		if (!texture->_img)
		{
			Service::Log().W("texture creation error, path:{}", respath);
			return nullptr;
		}

		texture->_width = texture->_img->Size().X();
		texture->_height = texture->_img->Size().Y();
		texture->_format = texture->_img->PixelDesc();
		texture->_type = type;

		GLenum format;
		if (texture->_format == Graphics::PixelFormat::RGB332)
			format = GL_RED;
		else if (texture->_format == Graphics::PixelFormat::RGB888)
			format = GL_RGB;
		else if (texture->_format == Graphics::PixelFormat::RGBA8888)
			format = GL_RGBA;

		glGenTextures(1, &texture->ID);
		glBindTexture(GL_TEXTURE_2D, texture->ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, format, texture->_width, texture->_height, 0, format, GL_UNSIGNED_BYTE, texture->_img->Data().get());
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		textureCache[respath] = texture;
		return texture;
	}

	void ResourceLoader::RecyleTexture()
	{
		for (auto it = textureCache.begin(); it != textureCache.end();)
		{
			if (it->second.unique())
			{
				it->second.reset();
				textureCache.erase(it++);
			}
			else
			{
				it++;
			}
		}
	}
}