#ifndef TINY_MATH_VECTOR3_H
#define TINY_MATH_VECTOR3_H

#include "Vector.h"

namespace Tiny { namespace Math {
	/*
		@brief Three-component Vector
		Can be indexed with (x, y, z) (r, g, b)
	*/
	template<typename T> class Vector3 : public Vector<3, T> {
	public:
		/*
			@brief constructors
		*/
		Vector3() :Vector<3, T>() {}
		constexpr Vector3(T x, T y, T z) noexcept : Vector<3, T>(x, y, z) {}
		//constexpr Vector3(const T source[3]) noexcept : Vector<3, T>(source) {}

		Vector3(const Vector<3, T>& other) :Vector<3, T>(other) {}
		Vector3& operator =(const Vector3<T>& other) = default;

		/*
			@brief index first component
		*/
		T& x() { return (*this)[0]; }
		const T& x() const { return (*this)[0]; }

		/*
			@brief index second component
		*/
		T& y(){ return (*this)[1]; }
		const T& y() const { return (*this)[1]; }
		/*
			@brief index third component
		*/
		T& z() { return (*this)[2]; }
		const T& z() const { return (*this)[2]; }


		/*
			@brief index first component
		*/
		T& r() { return (*this)[0]; }
		const T& r() const { return (*this)[0]; }

		/*
			@brief index second component
		*/
		T& g() { return (*this)[1]; }
		const T& g() const { return (*this)[1]; }
		/*
			@brief index third component
		*/
		T& b() { return (*this)[2]; }
		const T& b() const { return (*this)[2]; }

		/*
			@brief Vector3 in direction of X-Axis with length,
		*/
		static Vector3<T> xAxis(T length) { return{ length, T(0), T(0) }; }

		/*
			@brief Vector3 in direction of Y-Axis with length
		*/
		static Vector3<T> yAxis(T length) { return{ T(0), length, T(0) }; }

		/*
			@brief Vector3 in direction of Z-Axis with length
		*/
		static Vector3<T> zAxis(T length) { return{ T(0), T(0), length }; }
	};
}}

#endif
