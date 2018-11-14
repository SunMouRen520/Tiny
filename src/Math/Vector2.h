#ifndef TINY_MATH_VECTOR2_H
#define TINY_MATH_VECTOR2_H

#include "Vector.h"

/*
	@brief Two-component Vector
	@param T		Data type
*/
namespace Tiny { namespace Math {
	template<typename T> class Vector2 : public Vector<2, T> {
	public:
		/*
			@brief Constructors
		*/
		Vector2() : Vector<2, T>() {}
		constexpr Vector2(const T source[2]) noexcept :Vector<2, T>(source) {}
		constexpr Vector2(T x, T y) noexcept : Vector<2, T>(x, y) {}

		constexpr Vector2(const Vector<2, T>& other) noexcept : Vector<2, T>(other) {}
		Vector2& operator=(const Vector2<T>& other) = default;

		/*@berif destructor*/
		~Vector2() = default;

		/*
			@brief index fist component
		*/
		T& x() { return (*this)[0]; }
		/*const overload*/
		const T& x() const { return (*this)[0]; }

		/*
			@brief index second component
		*/
		T& y() { return (*this)[1]; }
		/*const overload*/
		const T& y() const { return (*this)[1]; }

		/*
			@brief Vector2 in direction of X-Axis with length
		*/
		static Vector2<T> xAxis(T length) ;

		/*
			@brief Vector2 in direction of Y-Axis with length
		*/
		static Vector2<T> yAxis(T length);
	};

	template<typename T> Vector2<T> Vector2<T>::xAxis(T length) {
		return Vector2<T>(length, T(0));
	}

	template<typename T> Vector2<T> Vector2<T>::yAxis(T length){
		return Vector2<T>(T(0), length);
	}
}
}

#endif