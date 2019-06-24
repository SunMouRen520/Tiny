#ifndef TINY_MATH_MATRIX4_H
#define TINY_MATH_MATRIX4_H

#include "Tiny/Math/Matrix3.h"
#include "Tiny/Math/Vector4.h"
#include "Tiny/Math/Angle.h"

namespace Tiny { namespace Math {
	/*
		@brief	3D Transformation matrix
		TODO:
			1.	Incompletge transformation support:
				a.	Complex for 2D rotation.
				b.	Normal Transformtion facility.
				c.	For complete transformation reference, see: https://doc.magnum.graphics/magnum/transformations.html
	*/
	template<typename T> class Matrix4 :public Matrix<4, T> {
		using Vec2 = Vector2<T>;
		using Vec3 = Vector3<T>;
		using Vec4 = Vector4<T>;

	public:
		/*
		  @brief Default identity construction
		*/
		/*explicit*/ Matrix4(IdentityInitT = IdentityInit)
			:Matrix<4, T>(IdentityInit) {}

		/*
		  @brief	Zero-clear construction
		*/
		explicit Matrix4(ZeroInitT)
			:Matrix<4, T>(ZeroInit) {}

		/*
		  @brief	Set all entries with uniform
		*/
		explicit Matrix4(const T& uniform)
			:Matrix<4, T>(uniform) {}

		/*
		  @brief Construct from other dimension.
		  If otherSize >= size, first 4x4 data will be taken from other.
		  otherwise, <other> will be copied to matrix4 and empty space will be full-filled with 0
		*/
		template<std::size_t otherSize> Matrix4(const RectangularMatrix<otherSize, otherSize, T>& other)
			: Matrix<4, T>(other) {}

		/*
			@brief Construct from 4D vectors
		*/
		Matrix4(const Vec4& a1, const Vec4& a2, const Vec4& a3, const Vec4& a4) :Matrix<4, T>(a1, a2, a3, a4) {}

		/*copy constructor*/
		Matrix4(const Matrix4<T>& other) = default;
		Matrix4(const Matrix<4, T>& other) :Matrix<4, T>(other) {};


		/*
		  @brief	Tranform Point
		*/
		Vector3<T> TransformPoint(const Vector3<T>& point) const {
			Vector4<T> t = (Vector4<T>(point, T(1)) * (*this));
			return t.XYZ() / t.W();
		}

		/*
		  @brief	Tranform vector
		*/
		Vector3<T> TransformVector(const Vector3<T>& vector) const{
			return Vector4<T>(Vector4<T>(vector, T(0)) * (*this)).XYZ();
		}

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
			@brief	3d Translation matrix
			@param	transpose	The transpose vector
		*/
		static Matrix4<T> Translation(const Vec3& transpose);


		/*
			@brief	Tranform from local coordinate to the coordinate whre basis and pos define
			@param	basis	basis coordinate
			@param	pos		pos
		*/
		static Matrix4<T> InnterToOuter(const Matrix3<T>& basis, const Vector3<T>& pos);

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
			@brief	Perspective projection. Map from view frustum to canonical view volume, with view direction -z.

			@param	rect	rect.x is the horizontal length of near clipping plane
							rect.y is the vertical length of near clipping plane
			@param	near	The near clipping plane distance
			@param	fat		The far clipping plane distance

			TODO: what if far is infinity?
		*/
		static Matrix4<T> Perspective(const Vec2& rect, const T& near, const T& far);

		/*
			@brief	Perspective projection. Map from view frustum to canonical view volume, with view direction -z.

			@param	fieldOfView		Horizontal field of view angle in Rad (0, M_PI)
			@param	aspectRatio		Horizontal : vertical aspect ratio
			@param	near			The near clipping plane distance
			@param	far				The far clipping plane distance

			This is the same as Perspective(rect, near, far) when:
				1.	fieldOfView = 2 * atan(rect.x / (2 * near))
				2.	aspectRatio = rect.x / rect.y
		*/
		static Matrix4<T> Perspective(const Rad<T>& fieldOfView, const T& aspectRatio, const T& near, const T& far);

		/*
			@brief	Orthographic projection. Map from orthographic view volume to canonical view volume, with view direction -z.

			@param	rect	rect.x is the horizontal length of orthographic view volume
							rect.y is the vertical length of orthographic view volume
			@param	near	The near clipping plane of orghographic view volume.
			@param	far		The far	clipping plane of orghographic view volume.
		*/
		static Matrix4<T> Orthographic(const Vec2& rect, const T& near, const T& far);

		/*
			@brief	Map from view frustum to orthographic view volume, with view direction -z.

			@param	near	near clipping plane
			@param	far		far clipping plane
		*/
		static Matrix4<T> PerspectiveToOrthographic(const T& near, const T& far);

		/*
		  @brief	Build camera tranform matrix where camera at eye, target sit at view  direction, and has up-direction insipred by up.
		  @caution	upHint cannot parallize with (eye - target)
		  @param	eye		camera position
		  @param	target	lookat target
		  @param	upHint	hint for up-direction of camera. Should not be parallize with (eye - target).
		*/
		static Matrix4<T> LookAt(const Vector3<T>& eye, const Vector3<T>& target, const Vector3<T>& upHint);
	};

	template<typename T> Matrix4<T> Matrix4<T>::Scale(const Vec3& scale) {
		return{ {scale.X(), T(0), T(0), T(0)},
				{T(0), scale.Y(), T(0), T(0)},
				{T(0), T(0), scale.Z(), T(0)},
				{T(0), T(0), T(0), T(1)}};
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
		return{ { T(1)		, shear.X()	, shear.X()	, T(0)},
				{shear.Y()	, T(1)		, shear.Y()	, T(0)},
				{shear.Z()	, shear.Z()	, T(1)		, T(0)},
				{T(0)		, T(0)		, T(0)		, T(1)}};
	}

	template<typename T> Matrix4<T> Matrix4<T>::Translation(const Vec3& tran) {
		return{ {T(1), T(0), T(0), T(0)},
				{T(0), T(1), T(0), T(0)},
				{T(0), T(0), T(1), T(0)},
				{tran.X(), tran.Y(), tran.Z(), T(1)}};
	}
	//in left-hand
	template<typename T> Matrix4<T> Matrix4<T>::RotationX(const Rad<T>& rad) {
		const T val = T(rad);
		const T sin_val = std::sin(val);
		const T cos_val = std::cos(val);
		return{ {T(1), T(0), T(0), T(0)},
				{T(0), cos_val, -sin_val, T(0)},
				{T(0), sin_val, cos_val, T(0)},
				{T(0), T(0), T(0), T(1)}};
	}
	//in left-hand
	template<typename T> Matrix4<T> Matrix4<T>::RotationY(const Rad<T>& rad) {
		const T val = T(rad);
		const T sin_val = std::sin(val);
		const T cos_val = std::cos(val);
		return{ {cos_val, T(0), sin_val, T(0)},
				{T(0), T(1), T(0), T(0)},
				{-sin_val, T(0), cos_val, T(0)},
				{T(0), T(0), T(0), T(1)}};
	}
	//in left-hand
	template<typename T> Matrix4<T> Matrix4<T>::RotationZ(const Rad<T>& rad) {
		const T val = T(rad);
		const T sin_val = std::sin(val);
		const T cos_val = std::cos(val);
		return{ {cos_val, -sin_val, T(0), T(0)},
				{sin_val, cos_val, T(0), T(0)},
				{T(0), T(0), T(1), T(0)},
				{T(0), T(0), T(0), T(1)}};
	}

	template<typename T> Matrix4<T> Matrix4<T>::Rotation(const Vec3& n, const Rad<T>& rad) {
		assert(n.IsNormalized());

		const T val = static_cast<float>(rad);
		const T cosR= std::cos(val), sinR = std::sin(val);
		const T nx2 = std::pow(n.X(), 2), ny2 = std::pow(n.Y(), 2), nz2 = std::pow(n.Z(), 2);
		const T index = 1 - cosR, nxy = n.X() * n.Y(), nxz = n.X() * n.Z(), nyz = n.Y() * n.Z();
		return{ {nx2 * index + cosR			, nxy * index + n.Z() * sinR, nxz * index - n.Y() * sinR, T(0)},
				{nxy * index - n.Z() * sinR	, ny2 * index + cosR		, nyz * index + n.X() * sinR, T(0)},
				{nxz * index + n.Y() * sinR	, nyz * index - n.X() * sinR, nz2 * index + cosR		, T(0)},
				{T(0)						, T(0)						, T(0)						, T(1)} };
	}

	template<typename T> Matrix4<T> Matrix4<T>::Perspective(const Vec2& rect, const T& n, const T& f) {
		assert(n > 0 && f > 0 && f > n);
		const Vec2 xyScale = T(2) * n / rect;
		const T v00 = xyScale.X(), v11 = xyScale.Y(), v22 = (f + n) / (f - n), v32 = T(2) * f * n / (n - f);
		return{	{v00	, T(0)	, T(0)	, T(0)},
				{T(0)	, v11, T(0)	, T(0)},
				{T(0)	, T(0)	, v22, T(1)},
				{T(0)	, T(0)	, v32, T(0)}};
	}

	template<typename T> Matrix4<T> Matrix4<T>::Perspective(const Rad<T>& fieldOfView, const T& aspectRatio, const T& n, const T& f) {
		assert(fieldOfView > Rad<T>(0) && fieldOfView < Rad<T>(M_PI));
		assert(aspectRatio > 0);
		assert(n > 0 && f > 0 && f > n);
		//const T width = T(2) * std::abs(near) * std::tan(T(fieldOfView) / T(2));
		//const T height = width / aspectRatio;
		//return Perspective(Vec2(width, height), n, f);
		T const tanHalfFov = std::tan(static_cast<T>(fieldOfView) / T(2));
		const T v00 = T(1) / tanHalfFov, v11 = aspectRatio / tanHalfFov, v22 = (f + n) / (f - n), v32 = T(2) * f * n / (n - f);
		return{	{T(v00)	, T(0)	, T(0)	, T(0)},
				{T(0)	, T(v11), T(0)	, T(0)},
				{T(0)	, T(0)	, T(v22), T(1)},
				{T(0)	, T(0)	, v32, T(0)}};
	}

	template<typename T> Matrix4<T> Matrix4<T>::Orthographic(const Vec2& rect, const T& n, const T& f) {
		assert(n > 0 && f > 0 && f > n);
		const Vec2 xyScale = T(2) / rect;
		const T v22 = T(2) / (f - n);
		const T v00 = xyScale.X(), v11 = xyScale.Y(), v32 = (n + f) / (n - f);
		return{ {v00	, T(0)	, T(0), T(0)},
				{T(0)	, v11	, T(0), T(0)},
				{T(0)	, T(0)	, v22 , T(0)},
				{T(0)	, T(0)	, v32 , T(1)} };
	}
	
	//Use caution,Deduce again
	template<typename T> Matrix4<T> Matrix4<T>::PerspectiveToOrthographic(const T& n, const T& f) {
		return{ {n		, T(0)	, T(0)	, T(0)},
				{T(0)	, n		, T(0)	, T(0)},
				{T(0)	, T(0)	, n + f	, T(1)},
				{T(0)	, T(0)	, -f * n, T(0)}};
	}

	template<typename T> Matrix4<T> Matrix4<T>::LookAt(const Vector3<T>& eye, const Vector3<T>& target, const Vector3<T>& upHint){
		const Vector3<T> z = (eye - target).Normalize();
		const Vector3<T> x = Cross(upHint, z).Normalize();
		const Vector3<T> y = Cross(z, x);
		return{ {x.X(), y.X(), z.X(), T{0} },
				{x.Y(), y.Y(), z.Y(), T{0}},
				{x.Z(), y.Z(), z.Z(), T{0}},
				{-eye * x, -eye * y, -eye * z, T{1}}};
	}

	template<typename T> Matrix4<T> Matrix4<T>::InnterToOuter(const Matrix3<T>& basis, const Vector3<T>& pos) {
		return Matrix4<T>(basis) * Matrix4<T>::Translation(pos);
	}
} }

#endif // !TINY_MATH_MATRIX4_H
