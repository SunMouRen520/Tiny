#ifndef TINY_MATH_VECTOR3_H
#define TINY_MATH_VECTOR3_H

#include "Tiny/Math/Vector2.h"

namespace Tiny { namespace Math {
	/*
		@brief Three-component Vector
		Can be indexed with (x, y, z) (r, g, b)
	*/
	template<typename T> class Vector3 : public Vector<3, T> {
	public:
		/*
			@brief Defaul zero-clear.
		*/
		/*explicit*/ Vector3(ZeroInitT = ZeroInit) :Vector<3, T>(ZeroInit) {}

		/*
		  @brief Construct from three entries
		*/
		constexpr Vector3(const T& x, const T& y, const T& z) noexcept : Vector<3, T>(x, y, z) {}

		/*
		  @brief Construct from vector2 and z
		*/
		explicit Vector3(const Vector2<T>& xy, const T& z) noexcept : Vector<3, T>(xy.X(), xy.Y(), z) {}

		/*
		  @brief Set all entries to uniform
		*/
		explicit Vector3(const T& uniform) noexcept : Vector<3, T>(uniform) {}


		/*
		  @brief Default copy constructor
		*/
		Vector3(const Vector<3, T>& other) :Vector<3, T>(other) {}
		Vector3& operator =(const Vector3<T>& other) = default;

		/*
			@brief index first component
		*/
		T& X() { return (*this)[0]; }
		const T& X() const { return (*this)[0]; }

		/*
			@brief index second component
		*/
		T& Y(){ return (*this)[1]; }
		const T& Y() const { return (*this)[1]; }
		/*
			@brief index third component
		*/
		T& Z() { return (*this)[2]; }
		const T& Z() const { return (*this)[2]; }


		/*
			@brief index first component
		*/
		T& R() { return (*this)[0]; }
		const T& R() const { return (*this)[0]; }

		/*
			@brief index second component
		*/
		T& G() { return (*this)[1]; }
		const T& G() const { return (*this)[1]; }
		/*
			@brief index third component
		*/
		T& B() { return (*this)[2]; }
		const T& B() const { return (*this)[2]; }

		/*
			@brief Get the xy component
		*/
		Vector2<T>& XY() { return (Vector2<T>&)Vector<2, T>::From(Vector<3,T>::Get()); }
		Vector2<T> XY() const { return (Vector2<T>)Vector<2, T>::From(Vector<3, T>::Get()); }

		/*
			@brief Vector3 in direction of X-Axis with length,
		*/
		static Vector3<T> XAxis(T length) { return{ length, T(0), T(0) }; }
		static Vector3<T> XAxis() { return{ T(1), T(0), T(0) }; }

		/*
			@brief Vector3 in direction of Y-Axis with length
		*/
		static Vector3<T> YAxis(T length) { return{ T(0), length, T(0) }; }
		static Vector3<T> YAxis() { return{ T(0), T(1), T(0) }; }
		/*
			@brief Vector3 in direction of Z-Axis with length
		*/
		static Vector3<T> ZAxis(T length) { return{ T(0), T(0), length }; }
		static Vector3<T> ZAxis() { return{ T(0), T(0), T(1) }; }
	};

	/*
		@brief Cross product of two vector, right-hand rule.
	*/
	template<typename T> Vector3<T> Cross(const Vector3<T>& a, const Vector3<T>& b) {
		return Vector3<T>(a.Y() * b.Z() - a.Z() * b.Y(), a.Z() * b.X() - a.X() * b.Z(), a.X() * b.Y() - a.Y() * b.X());
	}
}}

#endif
