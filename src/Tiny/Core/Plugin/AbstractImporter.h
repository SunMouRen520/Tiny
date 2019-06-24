#ifndef TINY_CORE_PLUGIN_APBSTRACTPLUGIN_H
#define TINY_CORE_PLUGIN_APBSTRACTPLUGIN_H

#include "Tiny/Graphics/Texture/ImageData.h"
#include <exception>

namespace Tiny { namespace PLUGIN{
	class ImportFailed : public std::exception { 
	public:
		ImportFailed(const char *what)
			:std::exception(what) {

		}
	};


	class AbstractImporter{
	public:
		virtual Graphics::ImageData Image(const std::string& path){
			assert(false);
			return Tiny::Graphics::ImageData(NULL, Tiny::Graphics::PixelFormat::RGB332, { 0, 0 });
		}

		
	};
} }

#endif // !TINY_CORE_APBSTRACTPLUGIN_H
