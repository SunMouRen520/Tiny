#ifndef TINY_MATH_MATRIX3_H
#define TINY_MATH_MATRIX3_H

#include "Matrix.h"
#include "Vector3.h"
#include "Vector2.h"

/*
	@brief 2D transformation matrix
	TODO:
		1.	Need some facility to convert between different dimension matrix easily.
*/
template<typename T> class Matrix3 : public Matrix<3, T> {
public:
	/*
		@breif construct from 3 row vector
	*/
	explicit Matrix3(const Vector3<T>& row1, const Vectr3<T>& row2, const Vector3<T>& row3):Matrix<3, T>(row1, row2, row3){}

	Matrix3(const Matrix3& other) = default;

	/* default copy constructor*/
	Matrix3(const Matrix3& other):Matrix<3, T>(other){}

	/*
		@brief scale matrix
		@param	v	scale vector
	*/
	static Matrix3<T> Scale(const Vector2<T>& v) {
		return	Matrix3<T>(Vector3<T>(v[0], T(0), T(0)),
				Vector3<T>((0), v[1], T(0)),
				Vector3<T>({T(0), T(0), T(1)) };
	}

	/*	
		@brief shear matrix
		@param	shear	shear vector
		Vector V(x, y) will be transformed to V(x + shear.x * y, y + shear,y * x).
	*/
	static Matrix3<T> Shear(const Vector2<T>& shear) {
		return Matrix3<T>(Vector3<T>(T(1), shear.y , T(0)),
						Vector3<T>(shear.x, T(1), T(0)),
						Vector3<T>(T(0), T(0), T(1)));
	}

	/*
		@brief rotation matrix
		@param	rad	the radian to rotate counter-clockwise
	*/
	static Matrix3<T> Rotate(const Rad& rad) {

	}
};

#endif 
