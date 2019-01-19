#ifndef EXT_LOADER_IMAGELOADER_H
#define EXT_LOADER_IMAGELOADER_H

#include "Tiny/Core/Plugin/AbstractImporter.h"


/*
@brief	This is a simple wrapper class of stb library.
*/
class ImageLoader : public Tiny::PLUGIN::AbstractImporter{
public:
	Tiny::Graphics::ImageData Image(const std::string& path) override;
};

extern "C" _declspec(dllexport) ImageLoader* Create() {
	return new ImageLoader();
}

#endif
