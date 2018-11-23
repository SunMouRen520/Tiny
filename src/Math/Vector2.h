#ifndef TINY_MATH_VECTOR2_H
#define TINY_MATH_VECTOR2_H

#include "Vector.h"

namespace Tiny { namespace Math {
	/*
		@brief Two-component Vector
		@param T		Data type

		TODO:
			1.	Need some facilities to convert between different dimensions easily.
	*/

	template<typename T> class Vector2 : public Vector<2, T> {
	public:
		/*
			@brief Constructors
		*/
		Vector2() : Vector<2, T>() {}
		//constexpr Vector2(const T source[2]) noexcept :Vector<2, T>(source) {}
		constexpr Vector2(T x, T y) noexcept : Vector<2, T>(x, y) {}

		constexpr Vector2(const Vector<2, T>& other) noexcept : Vector<2, T>(other) {}
		Vector2& operator=(const Vector2<T>& other) = default;

		/*@berif destructor*/
		~Vector2() = default;

		/*
			@brief index fist component
		*/
		T& X() { return (*this)[0]; }
		/*const overload*/
		const T& X() const { return (*this)[0]; }

		/*
			@brief index second component
		*/
		T& Y() { return (*this)[1]; }
		/*const overload*/
		const T& Y() const { return (*this)[1]; }

		/*
			@brief Vector2 in direction of X-Axis with length
		*/
		static Vector2<T> XAxis(T length) ;
		/*
			@brief Vector2 in direction of Y-Axis with length
		*/
		static Vector2<T> YAxis(T length);

		/*
			@brief	Project current vector to param other
			@return	The projected vector on other

			This interface is mathematically wrong. Project should be done with Matirx3.
		*/
		//Vector2<T> Project(const Vector2<T>& other);

		/*
			@brief Get a 2d vector which is perpendicular to this.
			The direction of perpendicular vector is counter-clockwise 90 degree.
		*/
		Vector2<T> Perpendicular() const { return{ -Y(), X() }; }
	};

	template<typename T> Vector2<T> Vector2<T>::XAxis(T length) {
		return Vector2<T>(length, T(0));
	}

	template<typename T> Vector2<T> Vector2<T>::YAxis(T length){
		return Vector2<T>(T(0), length);
	}

	//template<typename T> Vector2<T>	Vector2<T>::Project(const Vector2<T>& other) {
	//	return other * ((*this) * other / (other.Magnitude() * other.Magnitude()))
	//}
	/*
		@brief Get the inner angle between two vectors, no direction involved.
		@return Radian in [0, M_PI]
	*/
	template<typename T> Rad<T> inner_angle(const Vector2<T>& a, const Vector2<T>& b) {
		return Rad<T>(T(std::acos(a * b / (a.Magnitude() * b.Magnitude()))));
	}

	/*
		@brief Get the counter-clock wise angle from vector a to vector b
		@return Radian in [-M_PI, M_PI]
	*/
	template<typename T> Rad<T> angle(const Vector2<T>& a, const Vector2<T>& b) {
		Vector2<T> norm_a = a.Normalize();
		Vector2<T> norm_b = b.Normalize();
		T inner = norm_a.X() * norm_b.X() + norm_a.Y() * norm_b.Y();
		T det = norm_a.X() * norm_b.Y() - norm_a.Y() * norm_b.X();
		return std::atan2(det, inner);
	}
}
}

#endif