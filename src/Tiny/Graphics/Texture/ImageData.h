#ifndef TINY_GRAPHICS_DATA_IMAGEDATA_H
#define TINY_GRAPHICS_DATA_IMAGEDATA_H

#include "Tiny/Types.h"
#include "Tiny/Math/Vector.h"

#include <array>

namespace Tiny { namespace Graphics {

	/*
		@brief	ImageData
		Generalize image data. Can be used as the result of resource loading or feed to OpenGL.
	*/
	template<UnsignedInt dimension> class ImageData {
	public:
		explicit ImageData();

	private:
		Math::Vector<dimensation, UnsignedInt> _size;
		std::array<UnsignedByte> _data;
	};
} }

#endif // !TINY_GRAPHICS_DATA_IMAGEDATA_H
