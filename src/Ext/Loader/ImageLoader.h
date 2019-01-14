#ifndef EXT_LOADER_IMAGELOADER_H
#define EXT_LOADER_IMAGELOADER_H

#include "Tiny/Core/Plugin/AbstractImporter.h"

namespace EXT {

	/*
		@brief	This is a simple wrapper class of stb library.
	*/
	class ImageLoader : public Tiny::PLUGIN::AbstractImporter{
	public:
		static ImageLoader& Instance();
		void Init();

	private:
		Tiny::Graphics::ImageData2D DoImage2D(const std::string& path) override;
		
	};
}

#endif