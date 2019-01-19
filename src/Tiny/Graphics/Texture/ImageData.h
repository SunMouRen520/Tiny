#ifndef TINY_GRAPHICS_DATA_IMAGEDATA_H
#define TINY_GRAPHICS_DATA_IMAGEDATA_H

#include "Tiny/Types.h"
#include "Tiny/Math/Vector2.h"
#include "Tiny/Math/MathForward.h"
#include "Tiny/Graphics/Texture/Definition.h"

#include <array>
#include <memory>

namespace Tiny { namespace Graphics {

	/*
		@brief	ImageData
		Generalize image data, typically constructed by image loading plugin and servered as data source of graphics texture object.

		Due to the fact that ImageData takes quite a few memory,
		so we should avoid copy the memory from image loading plugin.

		Take stbi for example, memory obtained by stdbi_load should be managed by ImageData, so we shall never use stbi_image_free.

		TODO:
			1. We shall use engine-managed memory, not the raw UnsignedByte pointer.
	*/
	class ImageData {
	public:
		/*
			@pararm	p	Raw memory pointer
		*/
		explicit ImageData(UnsignedByte* p, PixelFormat f, Math::Vector2i size)
			:_data(p), _pixelDesc(f), _size(size) {

		}

		~ImageData() = default;

		ImageData(const ImageData&) = delete;
		ImageData& operator = (const ImageData&) = delete;

		ImageData(ImageData&& other) { swap(*this, other); }
		ImageData& operator = (ImageData&& other) { swap(*this, other); return *this; }

		/*
			@brief	Get the raw data.
		*/
		const UnsignedByte *Get() const { return _data.get(); }

		/*
			@brief Get the size info.
		*/
		const Math::Vector2i& Size() const { return _size; }

		/*
			@brief	Get the pixel format.
		*/
		PixelFormat PixelDesc() const { return _pixelDesc; }

		friend void swap(ImageData& first, ImageData& second); // nothrow

	private:
		PixelFormat	_pixelDesc;
		Math::Vector2i _size;
		std::unique_ptr<UnsignedByte> _data;
	};

	inline void swap(ImageData& first, ImageData& second)// nothrow
	{
		// enable ADL (not necessary in our case, but good practice)
		// by swapping the members of two objects,
		// the two objects are effectively swapped
		std::swap(first._size, second._size);
		std::swap(first._pixelDesc, second._pixelDesc);
		first._data.swap(second._data);
	}

}
}

#endif // !TINY_GRAPHICS_DATA_IMAGEDATA_H
