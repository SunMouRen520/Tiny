#ifndef TINY_GRAPHICS_TEXTURE_H
#define TINY_GRAPHICS_TEXTURE_H

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

	struct TextureDesc {
		UnsignedInt	_width;
		UnsignedInt _height;
		UnsignedInt _depth;

		PixelFormat	_format;

		FilterMode	_filter;
		WrapMode	_wrap;
		UnsignedByte _mipNumber;

		bool _cubeMap;

		std::unique_ptr<ImageData> _img;

		explicit TextureDesc(IronBranch::DefaultInitT = IronBranch::DefaultInit) {
			_width = _img->Size().X();
			_height = _img->Size().Y();
			_depth = 1;
			_format = PixelFormat::RGB888;
			_filter = FilterMode::Linear;
			_wrap = WrapMode::Clamp;
			_mipNumber = 0;
			_cubeMap = false;
		}
	};

	TextureHandler CreateTexture(const TextureDesc& info, const Memory *data);
	void UpdateTexture(TextureHandler tex, const Memory *data);
	void DestroyTexture(TextureHandler tex);

} }

#endif // !TINY_GRAPHICS_TEXTURE_H
