#ifndef TINY_MATH_MATHFORWARD_H
#define TINY_MATH_MATHFORWARD_H

#include <cstddef>
#include "Tiny/Types.h"

namespace Tiny { namespace Math {
	template<std::size_t, std::size_t, typename> class RectangularMatrix;
	template<typename T> using Matrix23 = RectangularMatrix<2, 3, T>;
	template<typename T> using Matrix32 = RectangularMatrix<3, 2, T>;
	template<typename T> using Matrix24 = RectangularMatrix<2, 4, T>;
	template<typename T> using Matrix42 = RectangularMatrix<4, 2, T>;
	template<typename T> using Matrix34 = RectangularMatrix<3, 4, T>;
	template<typename T> using Matrix43 = RectangularMatrix<4, 3, T>;

	template<std::size_t, typename> class Matrix;
	template<typename T> using Matrix22 = Matrix<2, T>;
	template<typename T> using Matrix33 = Matrix<3, T>;
	template<typename T> using Matrix44 = Matrix<4, T>;

	template<typename> class Matrix3;
	template<typename> class Matrix4;

	using Matrix3f = Matrix3<Float>;
	using Matrix4f = Matrix4<Float>;

	template<std::size_t, typename> class Vector;
	template<typename> class Vector2;
	template<typename> class Vector3;
	template<typename> class Vector4;

	using Vector2f = Vector2<Float>;
	using Vector3f = Vector3<Float>;
	using Vector4f = Vector4<Float>;

	using Vector2i = Vector2<Int>;

	template<template<typename> class, typename> class MeasurementUnit;
	template<typename> class Rad;
	template<typename> class Deg;

	using Radf = Rad<Float>;
	using Degf = Deg<Float>;

	template<typename T> class Quaternion;
	using Quaternionf = Quaternion<Float>;
}
}

#endif //TINY_MATH_MATHFORWARD_H
