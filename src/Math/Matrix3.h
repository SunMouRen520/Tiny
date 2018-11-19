#ifndef TINY_MATH_MATRIX3_H
#define TINY_MATH_MATRIX3_H

#include "Matrix.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Angle.h"


namespace Tiny { namespace Math {
	/*
		@brief 2D transformation matrix
		TODO:
			1.	Need some facilities to convert between different dimension matrix easily.
	*/
	template<typename T> class Matrix3 : public Matrix<3, T> {
		using Vec2 = Vector3<T>;
		using Vec3 = Vector3<T>;

	public:
		/*
			@breif Construct from 3 row vector
		*/
		explicit Matrix3(const Vec3& row1, const Vec3& row2, const Vec3& row3) :Matrix<3, T>(row1, row2, row3) {}

		Matrix3(const Matrix3& other) = default;

		/*
			@brief	Scale matrix
			@param	v	scale vector
		*/
		static Matrix3<T> Scale(const Vec2& v);

		/*
			@brief	Shear matrix
			@param	shear	shear vector
			Vector V(x, y) will be transformed to V(x + shear.x * y, y + shear,y * x).
		*/
		static Matrix3<T> Shear(const Vec2& shear);
		/*
			@brief	Rotation matrix
			@param	rad	The radian to rotate counter-clockwise
			| cos(rad)	sin(rad) |
			| -sin(rad) cos(rad) |
		*/
		static Matrix3<T> Rotate(const Rad<T>& rad);

		/*
			@brief Transponse matrix by vec2(x, y)
			@pram	v	Transpose matrix by v.x, v.y
		*/
		static Matrix3<T> Transpose(const Vec2& v);

		/*
			@brief 
		*/

	};
	
	template<typename T> Matrix3<T> Matrix3<T>::Scale(const Vec2& v) {
		return	Matrix3<T>(Vec3(v[0], T(0), T(0)),
			Vec3((0), v[1], T(0)),
			Vec3(T(0), T(0), T(1)));
	}

	template<typename T> Matrix3<T> Matrix3<T>::Shear(const Vec2& shear) {
		return Matrix3<T>(Vec3(T(1), shear.y, T(0)),
			Vec3(shear.x, T(1), T(0)),
			Vec3(T(0), T(0), T(1)));
	}

	template<typename T> Matrix3<T> Matrix3<T>::Rotate(const Rad<T>& rad) {
		T v = static_cast<T>(rad);
		T cos_val = static_cast<T>(std::cos(v));
		T sin_val = static_cast<T>(std::sin(v));
		return Matrix3<T>(Vec3(cos_val, sin_val, T(0)),
			Vec3(-sin_val, cos_val, T(0)),
			Vec3(T(0), T(0), T(1)));
	}

	template<typename T> Matrix3<T> Matrix3<T>::Transpose(const Vec2& shear) {
		return Matrix3<T>(Vec3(T(1), T(0), T(0)),
			Vec3(T(0), T(1), T(0)),
			Vec3(v.x, v.y, T(1)));
	}
}}
#endif 
