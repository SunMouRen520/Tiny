#ifndef TINY_MATH_VECTOR4_H
#define TINY_MATH_VECTOR4_H

#include "Math/Vector3.h"

namespace Tiny { namespace Math {
	/*
		@brief 4-D vector
			Can be indexed with (x, y, z, w) (r, g, b, a)
	*/
	template<typename T> class Vector4 :public Vector<4, T> {
	public:
		/*
			@brief	Default zero-clear 
		*/
		/*explicit*/ Vector4(ZeroInitT = ZeroInit) : Vector<4, T>(ZeroInit) {}

		/*
		  @brief Set all entries to uniform
		*/
		explicit Vector4(const T& uniform) : Vector<4, T>(uniform) {}

		/*
		  @brief Create from xyz and w
		*/
		explicit Vector4(const Vector3<T>& xyz, const T& w) :Vector<4, T>(xyz.X(), xyz.Y(), xyz.Z(), w) {}

		/*
		  @brief Create from xy z w
		*/
		explicit Vector4(const Vector2<T>& xy, const T& z, const T& w) : Vector<4, T>(xy.X(), xy.Y(), z, w) {}


		/*
			@brief Construct from four component
		*/
		constexpr /*explicit*/ Vector4(const T& x, const T& y, const T& z, const T& w) :Vector<4, T>(x, y, z, w) {}

		/*default copy constructor*/
		Vector4(const Vector4<T>& other) = default;
		Vector4(const Vector<4, T>& other) :Vector<4, T>(other) {}

		/*
			@brief	Construct from different dimension
		*/
		template<std::size_t otherSize> Vector4(const Vector<otherSize, T>& other)
			: Vector<4, T>(other) {}
			
		/*
			@brief X component
		*/
		T& X() { return (*this)[0]; }
		T X() const{ return (*this)[0]; }

		/*
			@brief Y component
		*/
		T& Y() { return (*this)[1]; }
		T Y() const{ return (*this)[1]; }

		/*
			@brief Z component
		*/
		T& Z() { return (*this)[2]; }
		T Z() const{ return (*this)[2]; }

		/*
			@brief W component
		*/
		T& W() { return (*this)[3]; }
		T W() const{ return (*this)[3]; }

		/*
			@brief R component
		*/
		T& R() { return (*this)[0]; }
		T R() const{ return (*this)[0]; }

		/*
			@brief G component
		*/
		T& G() { return (*this)[1]; }
		T G() const{ return (*this)[1]; }

		/*
			@brief B component
		*/
		T& B() { return (*this)[2]; }
		T B() const{ return (*this)[2]; }

		/*
			@brief A component
		*/
		T& A() { return (*this)[3]; }
		T A() const{ return (*this)[3]; }

		/*
			@brief Get xyz component
		*/
		Vector3<T>& XYZ() { return (Vector3<T>&)Vector<3, T>::From(Vector<4, T>::Get()); }
		Vector3<T> XYZ() const { return (Vector3<T>)Vector<3, T>::From(Vector<4,T>::Get()); }

		/*
			@brief Get xy component
		*/
		Vector2<T>& XY() { return (Vector2<T>&)Vector<2, T>::From(Vector<4, T>::Get()); }
		Vector2<T> XY() const{ return (Vector2<T>)Vector<2, T>::From(Vector<4, T>::Get()); }
	};
} }

#endif // !TINY_MATH_VECTOR4_H
