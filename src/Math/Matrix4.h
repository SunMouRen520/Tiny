#ifndef TINY_MATH_MATRIX4_H
#define TINY_MATH_MATRIX4_H

#include "Matrix3.h"
#include "Vector4.h"
#include "Angle.h"

namespace Tiny { namespace Math {
	/*
		@brief	3D Transformation matrix
		TODO:
			1.	Incompletge transformation support. Must provide the following:
				a.	Complex for 2D rotation and Quaternion for 3D rotation
				b.	Normal Transformtion facility.
				c.	For complete transformation reference, see: https://doc.magnum.graphics/magnum/transformations.html
			3.	Need some facilities to convert between different dimensions easily.
	*/
	template<typename T> class Matrix4 :public Matrix<4, T> {
		using Vec2 = Vector2<T>;
		using Vec3 = Vector3<T>;
		using Vec4 = Vector4<T>;

	public:
		/*default constructor*/
		explicit Matrix4() = default;

		/*
			@brief Construct from 4D vectors
		*/
		Matrix4(const Vec4& a1, const Vec4& a2, const Vec4& a3, const Vec4& a4) :Matrix<4, T>(a1, a2, a3, a4) {}

		/*copy constructor*/
		Matrix4(const Matrix4<T>& other) = default;
		Matrix4(const Matrix<4, T>& other) :Matrix<4, T>(other) {};

		/*
			@brief	3D scaling matrix
			@param	scale	The scale vector
		*/
		static Matrix4<T> Scale(const Vec3& scale);

		/*
			@brief	scale along arbitrary normalized vector n with factor k

		*/
		static Matrix4<T> ScaleAlongVector(const Vec3& n, const T& k);

		/*
			@brief	3d shearing matix
			@param	shear	The shear vector
		*/
		static Matrix4<T> Shear(const Vec3& shear);

		/*
			@brief	3d transpose matrix
			@param	transpose	The transpose vector
		*/
		static Matrix4<T> Transpose(const Vec3& transpose);

		/*
			@brief	Rotate around axis rad in right-hand rule.
			@param	axis	The rotate axis, expected normalized
			@param	rad		The rotation unit in radian, right-hand rule, defined in the plane perpendicular to axis, in range [-M_PI, M_PI].

		*/
		static Matrix4<T> Rotation(const Vec3& axis, const Rad<T>& rad);


		/*
			@brief	Convinent function for rotate around x axis.
		*/
		static Matrix4<T> RotationX(const Rad<T>& rad);
		/*
			@brief	Convinent function for rotate around y axis.
		*/
		static Matrix4<T> RotationY(const Rad<T>& rad);
		/*
			@brief	Convinent function for rotate around z axis.
		*/
		static Matrix4<T> RotationZ(const Rad<T>& rad);

		/*
			@brief	Perspective projection. Map from view frustum to canonical view volume, view direction is -z.
			@param	rect	rect.x is the horizontal vector of near clipping plane 
							rect.y is the vertical vector of near clipping plane
			@param	near	The near clipping plane distance
			@param	fat		The far clipping plane distance
		*/
		static Matrix4<T> Perspective(const Vec2& rect, T near, T far);

		/*
			@brief	Perspective projection. Map from view frustum to canonical view volume, view direction is -z.
			@param	fieldOfView		Horizontal field of view angle
			@param	aspectRatio		Horizontal : vertical aspect ratio
			@param	near			The near clipping plane distance
			@param	far				The far clipping plane distance

			This is the same as Perspective(rect, near, far) when:
				1.	fieldOfView = 2 * atan(rect.x / (2 * near))
				2.	aspectRatio = rect.x / rect.y 
		*/
		static Matrix4<T> Perspective(T fieldOfView, T aspectRatio, T near, T far);

		/*
			@brief	Orthographic projection. Map from orthographic view volume to canonical view volume, view direction is -z.
			@param	rect	rect.x is the horizontal length of orthographic view volume
							rect.y is the vertical length of orthographic view volume
			@param	near	The near clipping plane of orghographic view volume.
			@param	far		The far	clipping plane of orghographic view volume.
		*/
		static Matrix4<T> Orthograpic(const Vec2& rect, T near, T far);

		/*
			@brief	Map from view frustum to orthographic view volume, view direction is -z.
			@ref	Params are same as Perspective(rect, near, far)
		*/
		static Matrix4<T> PerspectiveToOrthographic(const Vec2& rect, T near, T far);
		/*
			@brief	Map from view frustum to orthographic view volume, view direction is -z.
			@ref	Params are same as Perspective(fieldOfView, apsecRatio, near, far)
		*/
		static Matrix4<T> PerspectiveToOrthographic(T fieldOfView, T aspectRatio, T near, T far);
	};

	template<typename T> Matrix4<T> Matrix4<T>::Scale(const Vec3& scale) {
		return{ {scale.X(), T(0), T(0), T(0)},
				{T(0), scale.Y(), T(0), T(0)},
				{T(0), T(0), scale.Z(), T(0)},
				{T(0), T(0), T(0), T(0)}};
	}

	template<typename T> Matrix4<T> Matrix4<T>::ScaleAlongVector(const Vec3& n, const T& k) {
		assert(n.IsNormalized());

		const T nx2 = std::pow(n.X(), 2), ny2 = std::pow(n.Y(), 2), nz2 = std::pow(n.Z(), 2);
		const T nxy = n.X() * n.Y(), nxz = n.X() * n.Z(), nyz = n.Y() * n.Z();
		const T index = k - 1;
		return{ { 1 + index *nx2, index * nxy, index * nxz, T(0)},
				{index * nxy, 1 + index * ny2, index * nyz, T(0)},
				{index * nxz, index * nyz, 1 + index * nz2, T(0)},
				{T(0),T(0), T(0), T(1)} };
	}

	template<typename T> Matrix4<T> Matrix4<T>::Shear(const Vec3& shear) {
		return{ { shear.X(), T(0), T(0), T(0)},
				{T(0), shear.Y(), T(0), T(0)},
				{T(0), T(0), shear.Z(), T(0)},
				{T(0), T(0), T(0), T(0)}};
	}

	template<typename T> Matrix4<T> Matrix4<T>::Transpose(const Vec3& tran) {
		return{ { tran.X(), T(0), T(0), T(0)},
				{T(0), tran.Y(), T(0), T(0)},
				{T(0), T(0), tran.Z(), T(0)},
				{T(0), T(0), T(0), T(0)}};
	}

	template<typename T> Matrix4<T> Matrix4<T>::RotationX(const Rad<T>& rad) {
		const T val = static_cast<float>(rad);
		const T sin_val = std::sin(val);
		const T cos_val = std::cos(val);
		return{ {T(1), T(0), T(0), T(0)},
				{T(0), cos_val, sin_val, T(0)},
				{T(0), -sin_val, cos_val, T(0)},
				{T(0), T(0), T(0), T(1)}};
	}

	template<typename T> Matrix4<T> Matrix4<T>::RotationY(const Rad<T>& rad) {
		const T val = static_cast<float>(rad);
		const T sin_val = std::sin(val);
		const T cos_val = std::cos(val);
		return{ {cos_val, T(0), sin_val, T(0)},
				{T(0), T(1), T(0), T(0)},
				{-sin_val, T(0), cos_val, T(0)},
				{T(0), T(0), T(0), T(1)}};
	}

	template<typename T> Matrix4<T> Matrix4<T>::RotationZ(const Rad<T>& rad) {
		const T val = static_cast<float>(rad);
		const T sin_val = std::sin(val);
		const T cos_val = std::cos(val);
		return{ {cos_val, sin_val, T(0), T(0)},
				{-sin_val, cos_val, T(0), T(0)},
				{T(0), T(0), T(1), T(0)},
				{T(0), T(0), T(0), T(1)}};
	}

	template<typename T> Matrix4<T> Matrix4<T>::Rotation(const Vec3& n, const Rad<T>& rad) {
		assert(n.IsNormalized());

		const T val = static_cast<float>(rad);
		const T cosR= std::cos(val), sinR = std::sin(val);
		const T nx2 = std::pow(n.X(), 2), ny2 = std::pow(n.Y(), 2), nz2 = std::pow(n.Z(), 2);
		const T index = 1 - cosR, nxy = n.X() * n.Y(), nxz = n.X() * n.Z(), nyz = n.Y() * n.Z();
		return{ {nx2 * index + cosR, nxy * index + n.Z() * sinR, nxz * index - n.Y() * sinR, T(0)},
				{nxy * index - n.Z() * sinR, ny2 * index + cosR, nyz * index + n.Z() * sinR, T(0)},
				{nxz * index + n.Y() * sinR, nyz * index - n.X() * sinR, nz2 * index + cosR, T(0)}.
				{T(0), T(0), T(0), T(1)} };
	}

	template<typename T> Matrix4<T> Matrix4<T>::Perspective(const Vec2& rect, T near, T far) {
		const T left = -rect.X() / 2, right = rect.X() / 2, up = rect.Y() / 2, bottom = -rect.Y() / 2;
		TOBECONTINUE
	}
} }

#endif // !TINY_MATH_MATRIX4_H
