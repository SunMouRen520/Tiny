#ifndef TINY_CORE_PLUGIN_APBSTRACTPLUGIN_H
#define TINY_CORE_PLUGIN__APBSTRACTPLUGIN_H

#include "Tiny/Graphics/Texture/ImageData.h"

namespace Tiny { namespace PLUGIN{
	class AbstractImporter{
	public:
		Graphics::ImageData2D Image2D(const std::string& path);

	private:
		virtual Graphics::ImageData2D DoImage2D(const std::string& path);
		
	};
} }

#endif // !TINY_CORE_APBSTRACTPLUGIN_H
