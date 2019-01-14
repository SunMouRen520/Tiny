#include "Ext/Loader/ImageLoader.h"
#include "Tiny/Core/Plugin/PluginManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Ext/Loader/stb_image.h"

using namespace Tiny::PLUGIN;

namespace EXT {
	ImageLoader& ImageLoader::Instance() {
		static ImageLoader inst;
		return inst;
	}

	void ImageLoader::Init() {
		PluginManager<AbstractImporter>::Instance().RegisterPlugin("PNGImporter", this);
		PluginManager<AbstractImporter>::Instance().RegisterPlugin("JPGImporter", this);
	}

	Tiny::Graphics::ImageData2D ImageLoader::DoImage2D(const std::string& path) {
		
	}
}
