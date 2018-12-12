#ifndef TINY_MATH_MATHFORWARD_H
#define TINY_MATH_MATHFORWARD_H

#include <cstddef>

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

	using Matrix3f = Matrix3<float>;
	using Matrix4f = Matrix4<float>;

	template<std::size_t, typename> class Vector;
	template<typename> class Vector2;
	template<typename> class Vector3;
	template<typename> class Vector4;

	using Vector2f = Vector2<float>;
	using Vector3f = Vector3<float>;
	using Vector4f = Vector4<float>;

	template<template<typename> class, typename> class MeasurementUnit;
	template<typename> class Rad;
	template<typename> class Deg;

	using Radf = Rad<float>;
	using Degf = Deg<float>;
}
}

#endif //TINY_MATH_MATHFORWARD_H
