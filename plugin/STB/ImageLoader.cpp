#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "ImageLoader.h"
#include "Tiny/Core/Plugin/PluginManager.h"

Tiny::Graphics::ImageData ImageLoader::Image(const std::string& path) {
	int x = 0, y = 0, channelNum = 0;
	std::uint8_t *data = stbi_load(path.c_str(), &x, &y, &channelNum, 0);
	if(!data)
		throw Tiny::PLUGIN::ImportFailed(("Load texture from file " + path + "failed!").c_str());

	Tiny::Graphics::PixelFormat pf;
	if(channelNum == 3){
			pf = Tiny::Graphics::PixelFormat::RGB888;
	}else if(channelNum == 4){
			pf = Tiny::Graphics::PixelFormat::RGBA8888;
	}else{
		throw Tiny::PLUGIN::ImportFailed(("Unknown channel num" + std::to_string(channelNum)).c_str());
	}

	return Tiny::Graphics::ImageData(data, pf, {x, y});
}
