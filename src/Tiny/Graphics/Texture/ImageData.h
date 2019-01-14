#ifndef TINY_GRAPHICS_DATA_IMAGEDATA_H
#define TINY_GRAPHICS_DATA_IMAGEDATA_H

#include "Tiny/Types.h"
#include "Tiny/Math/Vector.h"
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
	template<UnsignedInt dimension> class ImageData {
	public:

		Using Dimensation = dimensation;

		/*
			@pararm	p	Raw memory pointer
		*/
		explicit ImageData(UnsignedByte* p, PixelFormat f, Math::Vector<dimension, UnsignedInt> size)
			:_data(p), _pixelDesc(f), _size(size) {

		}

		~ImageData() {

		}

		ImageData(const ImageData&) = delete;
		ImageData& operator = (const ImageData&) = delete;

		ImageData(ImageData&& other) { Move(other); }
		ImageData& operator = (ImageData&& other) { Move(other); }


		/*
			@brief	Get the raw data.
		*/
		const UnsignedByte *Get() const { return _data.get(); }

		/*
			@brief Get the size info.
		*/
		const Math::Vector<Dimensation, UnsignedInt>& Size() const { return _size; }

		/*
			@brief	Get the pixel format.
		*/
		PixelFormat PixelDesc() const { return _pixelDesc; }

	private:
		void Move(ImageData&& other) {
			_data.reset(other._data.release());
			_pixelDesc = other._pixelDesc;
			_size = other._size;
		}

	private:
		PixelFormat	_pixelDesc;
		Math::Vector<Dimensation, UnsignedInt> _size;
		std::unique_ptr<UnsignedByte> _data;
	};

	using ImageData1D = ImageData<1>;
	using ImageData2D = ImageData<2>;
	using ImageData3D = ImageData<3>;
} }

#endif // !TINY_GRAPHICS_DATA_IMAGEDATA_H
