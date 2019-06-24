#ifndef TINY_GRAPHICS_TEXTURE_H
#define TINY_GRAPHICS_TEXTURE_H

#include "gl3w/GL/gl3w.h"

#include "Tiny/Types.h"
#include "Tiny/Graphics/Texture/Definition.h"
#include "Tiny/Graphics/Texture/ImageData.h"

#include "IronBranch/Notion/Tags.h"

namespace Tiny { namespace Graphics {
	/*
		@brief	Internal representation of Texture.
		Basically, a texture object defines how images are interpreted:
			1.	width, height, depth(if depth != 1, 3D texture. if depth == 1, 2D texture).
			2.	filter mode
			3.	wrap mode
			4.	MIP maps number
			5.	is cube map
			6.	pixel format
	*/

	using TextureHandler = UnsignedInt;
	using Memory = UnsignedByte;

	class Texture {
	public:
		~Texture() { if (ID != 0) glDeleteTextures(1, &ID); }
		UnsignedInt ID; //GL texture obj

		UnsignedInt	_width;
		UnsignedInt _height;
		UnsignedInt _depth;

		PixelFormat	_format;
		TextureType _type;
		FilterMode	_filter;
		WrapMode	_wrap;
		UnsignedByte _mipNumber;

		bool _cubeMap;

		std::shared_ptr<ImageData> _img;

		explicit Texture(IronBranch::DefaultInitT = IronBranch::DefaultInit) {
			_width = 0;
			_height = 0;
			_depth = 1;
			_format = PixelFormat::UNKNOWN;
			_type = TextureType::Unknown;
			_filter = FilterMode::Linear;
			_wrap = WrapMode::Clamp;
			_mipNumber = 0;
			_cubeMap = false;
		}

		static std::shared_ptr<Texture> Texture2D(const std::string& resPath, TextureType type);
	};

	
} }

#endif // !TINY_GRAPHICS_TEXTURE_H
