#ifndef TINY_MATH_MATRIX3_H
#define TINY_MATH_MATRIX3_H

#include "Tiny/Math/Matrix.h"
#include "Tiny/Math/Vector3.h"

namespace Tiny { namespace Math {
	/*
		@brief 2D transformation matrix
	*/
	template<typename T> class Matrix3 : public Matrix<3, T> {
		using Vec2 = Vector2<T>;
		using Vec3 = Vector3<T>;

	public:

		/*
			@brief	Default constructor, idendity
		*/
		/*explicit*/ Matrix3(IdentityInitT = IdentityInit)
			:Matrix<3, T>(IdentityInit){}

		/*
			@brief	Zero-clear matrix
		*/
		explicit Matrix3(ZeroInitT) :Matrix<3, T>(ZeroInit) {}

		/*
		  @brief	Set all entries with uniform
		*/
		explicit Matrix3(const T& uniform)
			:Matrix<3, T>(uniform) {}

		/*
			@brief	Construct from different dimension
		*/
		template<std::size_t otherSize> Matrix3(const RectangularMatrix<otherSize, otherSize, T>& other)
			:Matrix<3, T>(other){}

		/*
			@breif Construct from 3 row vector
		*/
		Matrix3(const Vec3& row1, const Vec3& row2, const Vec3& row3) :Matrix<3, T>(row1, row2, row3) {}

		Matrix3(const Matrix3& other) = default;

		/*
			@breief Construct from Euler angles, order by z, x, y
		*/
		static Matrix3<T> FromEuler(const Vector3<T>& eulerAngles);

		/*
			@breief Matrix to Euler, order by z, x, y
		*/
		static Vector3<T> ToEuler(const Matrix3<T>& matrix);
		/*
			@brief	Convinent function to construct scale matrix.
			@param	v	v.x is the x scale factor, x.y is the y scale factor
		*/
		static Matrix3<T> Scale(const Vec2& v);

		/*
			@brief	Shear matrix
			@param	shear	shear vector
			Vector V(x, y) will be transformed to V(x + shear.x * y, y + shear.y * x).
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
			@brief	Translation matrix by vec2(x, y)
			@pram	v	Transpose matrix by v.x, v.y
		*/
		static Matrix3<T> Translation(const Vec2& v);

		/*
			@brief	2D relection about arbitrary normalized vector n

			Reflection can be viewed in two ways:
			1.	Transfer vector v to standard cartesian basis, then rotate, then trasfer back t o vector v
			2.	scale along v's perpendicular vector with factor -1.
			Here we take way 2, due to it cost less computation.
		*/
		static Matrix3<T> Reflection(const Vec2& n);

		/*
			@brief	Scale along normalized vector n with factor k.
		*/
		static Matrix3<T> ScaleAlongVector(const Vec2& n, const T& k);

		/*
			@brief		Project to the vector n

			Projection can be viewd as scale along n's perpendicular vector with factor 0.
		*/
		static Matrix3<T> Projection(const Vec2& n);
	};
	//in left-hand
	template<typename T> Matrix3<T> Matrix3<T>::FromEuler(const Vector3<T>& eulerAngles)
	{
		T x = T(Math::Rad<T>(Math::Deg<T>(eulerAngles.X())));
		T y = T(Math::Rad<T>(Math::Deg<T>(eulerAngles.Y())));
		T z = T(Math::Rad<T>(Math::Deg<T>(eulerAngles.Z())));
		T sin_x = std::sin(x), cos_x = std::cos(x);
		T sin_y = std::sin(y), cos_y = std::cos(y);
		T sin_z = std::sin(z), cos_z = std::cos(z);

		return{ {cos_z*cos_y - sin_z*sin_x*sin_y, -sin_z*cos_x, cos_z*sin_y+sin_z*sin_x*cos_y},
				{sin_z*cos_y+cos_z*sin_x*sin_y, cos_z*cos_x, sin_z*sin_y - cos_z*sin_x*cos_y},
				{-cos_x*sin_y, sin_x, cos_x*cos_y}};
	}
	//in left-hand
	template<typename T> Vector3<T> Matrix3<T>::ToEuler(const Matrix3<T>& matrix)
	{
		T sp = matrix[2][1];

		if (sp >= T(1))
			sp = T(1);
		else if (sp <= -1)
			sp = T(-1);

		T pitch = std::asin(sp);
		T yaw, roll;
		if (equals(std::fabs(sp), T(1)))
		{
			yaw = std::atan2(matrix[0][2], matrix[0][0]);
			roll = T(0);
		}
		else
		{
			yaw = std::atan2(-matrix[2][0], matrix[2][2]);
			roll = std::atan2(-matrix[0][1], matrix[1][1]);
		}

		return { T(Deg<T>(Rad<T>(pitch))), T(Deg<T>(Rad<T>(yaw))), T(Deg<T>(Rad<T>(roll))) };
	}

	template<typename T> Matrix3<T> Matrix3<T>::Scale(const Vec2& v) {
		return{ { v[0], T(0), T(0)},
				{ T(0), v[1], T(0)},
				{ T(0), T(0), T(1)} };
	}

	template<typename T> Matrix3<T> Matrix3<T>::Shear(const Vec2& shear) {
		return{ { T(1), shear.Y(), T(0)},
				{ shear.X(), T(1), T(0)},
				{ T(0), T(0), T(1) } };
	}

	template<typename T> Matrix3<T> Matrix3<T>::Rotate(const Rad<T>& rad) {
		T v = static_cast<T>(rad);
		const T cos_val = static_cast<T>(std::cos(v));
		const T sin_val = static_cast<T>(std::sin(v));
		return{ { cos_val, sin_val, T(0)},
				{ -sin_val, cos_val, T(0)},
				{ T(0), T(0), T(1) } };
	}

	template<typename T> Matrix3<T> Matrix3<T>::Translation(const Vec2& t) {
		return{ { T(1), T(0), T(0) },
				{ T(0), T(1), T(0) },
				{ t.X(), t.Y(), T(1)} };
	}

	template<typename T> Matrix3<T> Matrix3<T>::Reflection(const Vec2& n) {
		assert(n.IsNormalized());

		Vec2 perpenN = n.Perpendicular();

		const T nx2 = std::pow(perpenN.X(), 2), ny2 = std::pow(perpenN.Y(), 2), nxy = perpenN.X() * perpenN.Y();
		return { { 1 - 2 * nx2, -2 * nxy, T(0)},
				{ -2 * nxy, 1 - 2 * ny2, T(0) },
				{ T(0), T(0), T(1) }};
	}

	template<typename T> Matrix3<T> Matrix3<T>::ScaleAlongVector(const Vec2& n, const T& k) {
		assert(n.IsNormalized());

		const T nx2 = std::pow(n.X(), 2), ny2 = std::pow(n.Y(), 2), nxy = n.X() * n.Y();
		return { {1 + (k - 1)* nx2, (k - 1) * nxy, T(0)},
				{ (k - 1) * nxy , 1 + (k - 1) * ny2, T(0) },
				{ T(0), T(0), T(1) }};
	}

	template<typename T> Matrix3<T> Matrix3<T>::Projection(const Vec2& n) {
		assert(n.IsNormalized());

		Vec2 perpenN = n.Perpendicular();

		const T nx2 = std::pow(perpenN.X(), 2), ny2 = std::pow(perpenN.Y(), 2), nxy = perpenN.X() * perpenN.Y();
		return { { 1 - nx2, -nxy, T(0)},
				{ -nxy, 1 - ny2, T(0)},
				{ T(0), T(0), T(1) }};
	}
}}
#endif
