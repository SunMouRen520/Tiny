#ifndef TINY_MATH_MATRIX_H
#define TINY_MATH_MATRIX_H

#include "RectangularMatrix.h"

namespace Tiny { namespace Math {
	template<std::size_t size, typename T> class Matrix : public RectangularMatrix<size, size, T> {
		template<std::size_t, typename> friend class Matrix;

	public:
		/*	
			Is Symmetric?
		*/
		bool Symmetric() const();
	};
} }

#endif