#ifndef TINY_GRAPHICS_TEXTURE_DEFINITION_H
#define TINY_GRAPHICS_TEXTURE_DEFINITION_H

namespace Tiny { namespace Graphics {

	/*
		@brief	Pixel Format 
		TODO:
			1. 
	*/
    enum class PixelFormat{
		UNKNOWN,

		RGB888,
		RGB332,
		RGB565,
		RGBA8888,
		RGBA4444,
	};

	enum class WrapMode {
		Clamp,
		Wrap,
	};

	enum class FilterMode {
		Linear,
	};

	enum class TextureType {
		Unknown,
		Diffuse,
		Specular,
	};
} }

#endif // !TINY_GRAPHICS_TEXTURE_DEFINITION_H
