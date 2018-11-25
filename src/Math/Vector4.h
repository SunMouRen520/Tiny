#ifndef TINY_MATH_VECTOR4_H
#define TINY_MATH_VECTOR4_H

#include "Vector3.h"

namespace Tiny { namespace Math {
	/*
		@brief 4-D vector
			Can be indexed with (x, y, z, w) (r, g, b, a)
	*/
	template<typename T> class Vector4 :public Vector<4, T> {
	public:
		/*default constructor*/
		explicit Vector4() = default;

		/*
			@brief Construct from four component
		*/
		constexpr /*explicit*/ Vector4(const T& x, const T& y, const T& z, const T& w) :Vector<4, T>(x, y, z, w) {}

		/*default copy constructor*/
		Vector4(const Vector4<T>& other) = default;
		Vector4(const Vector<4, T>& other) :Vector<4, T>(other) {}
		Vector4(const Vector3<T>& other){
			for(std::size_t i = 0 ; i < 3 ;i++)
				(*this)[i] = other[i];
			(*this)[3] = T(1);
		}

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
