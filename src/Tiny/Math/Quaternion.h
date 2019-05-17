#ifndef TINY_MATH_QUATERNION_H
#define TINY_MATH_QUATERNION_H

#include "Tiny/Math/Vector3.h"
#include "Tiny/Math/Angle.h"
#include "Tiny/Math/Tags.h"
#include "Tiny/Math/Matrix.h"
#include "Tiny/Math/Tools.h"

#include <cmath>

#ifdef TINY_TEST
#include <iostream>
#endif

/*
	Quaternion can be used to representing 3D rotations.
	Quaternions are composed of two components:
		(theta, vector) or [w, v]
		vector represents the axis about which to rotate.
		theta represents the rotation angle.

	Mathematically, quaternion(w, x, y, z) represents complex number:
		w + xi + yj + zk
		which constrainted by:
			1.	i * i = j * j = k * k = -1
			2.	i * j = k, j * i = -k
			3.	j * k = i, k * j = -i
			4.	k * i = j, i * k = -j

	Given normalized rotation axis N and rotation angle Theta,
		Q	= [cos(Theta / 2), sin(Theta / 2) * N]
			= [cos(Theta / 2), sin(Theta / 2) * Nx, sin(Theta / 2) * Ny, sin(Theta / 2) * Nz)  --Formula Q.1

	Norm ||Q||:
		norm = sqrt(w * w +  v * v).
		Norms of quaternions constructed ay Formula Q.1 always are 1.

	Negative -Q:
		-Q = [-w, -x, -y, -z], which represents the same rotation as Q.

	Idendity:
		Q = [1, 0, 0, 0].  In computer graphics , [-1, 0, 0, 0] can also be idendity quaternion.
		Do no rotation at all.

	Conjugate Q*:
		Q* = [w, -x, -y, -z].

	Inverse QN:
		Qinver = Q* / ||Q||
		Due to the fact that quaternions in computer graphics always has norm to be 1, so QN = Q*.
		Qinver represents the inverse rotation of Q.

	Multiplication:
		one of two definitions, using this def we can represent rotation combination with multiply from left to right
		Q3	= Q1 * Q2
			= [w1 x1 y1 z1] * [w2 x2 y2 z2]
			= [	w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2,
				w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2,
				w1 * y2 + y1 * w2 + z1 * x2 - x1 * z2,
				w1 * z2 + z1 * w2 + x1 * y2 - y1 * x2 ]

		(A * B) * C = A * (B * C)
		A * B != B * A

		Given 3D-vector p, we extern p to quaternion: p = [0, p] then we can transfrom p to p':
			p' = Qinver * p * Q
			p' = (xy)inver * p * (xy)

		Given rotation A, B  and A * D = B,
			D = Ainver * B
			So D is the "difference" between A and B.
	Dot:
		Dot(Q1, Q2) = w1 * w2 + x1 * x2 + y1 * y2 + z1 * z2
		As vector dot product, the dot product result of Quaternion is scalar too.

	Log:
		Set Q = [cos(Alpha), n * sin(Alpha)]
		logQ = log([cos(Aplha), n * sin(Alpha)])
			 = [0, Alpha * n]

	Exponential :
		Q must has form: [0, Alpha * n]
		exp(Q) = [cos(Aplha), n * sin(Alpha)]

		exp(logQ) = Q.

	Exponentiation:
		Say quaternion Q represents some rotation.
		q' = exp(t * log(Q)) represent repeat rotation by t times.

	Tranform between Quaternion and Matrix:
		see code blow.
*/

namespace Tiny { namespace Math {
	template<typename T> class Quaternion;

	/*
	  @brief	Shortest path linear lerp from q1  to q2 with coeffcient t.
	*/
	template<typename T> Quaternion<T> Lerp(const Quaternion<T>& q1, const Quaternion<T>& q2, const T& t) {
		const Quaternion<T> shortestQ1 = Dot(q1, q2) < 0 ? -q1 : q1;
		return Quaternion<T>(Lerp(shortestQ1.Scalar(), q2.Scalar(), t), Lerp(shortestQ1.Vector(), q2.Vector(), t)).Normalize();
	}

	/*
	  @brief	Shortest path spherical lerp
	  @caution	Spherical slerp only works with rotation quaternion.
				If q1 and q2 represents the same rotation, then q1 will be returned.
	*/
	template<typename T> Quaternion<T> Slerp(const Quaternion<T>& q1, const Quaternion<T>& q2, const T& t) {
		assert(q1.IsNormalized() && q2.IsNormalized());

		const T cosHalfTheta = Dot(q1, q2);
		if (std::abs(cosHalfTheta) >= (T{ 1 } -std::numeric_limits<T>::epsilon()))
			return q1;

		const Quaternion<T> shortestQ1 = (cosHalfTheta < 0) ? -q1 : q1;

		const T a = std::acos(std::abs(cosHalfTheta));
		return (std::sin((T(1) - t) * a) * shortestQ1 + std::sin(t * a) * q2) / std::sin(a);
	}

	/*
	  @brief	Dot-Product
	  @return	Half-angle for q1 and q2
	*/
	template<typename T> T Dot(const Quaternion<T>& q1, const Quaternion<T>& q2){
		return q1.Scalar() * q2.Scalar() + q1.Vector() * q2.Vector();
	}


	/*
	  @brief	Represents 3D rotation.
	  TOOD:
	  	1. multiply with matrix
	*/
	template<typename T> class Quaternion {
	public:
		using Type = T;

		/*
		  @brief	Construct rotation quaternion.
		  @param	angle	rotation angle.
		  @param	axis	rotation axis
		*/
		static Quaternion<T> Rotate(const Rad<T>& angle, const Vector3<T>& axis);

		/*
		  @brief	Constuct rotation quaternion from rotation matrix.
		*/
		static Quaternion<T> FromMatrix(const Matrix<3, T>& m);

		/*
		@brief	Construct rotation quaternion from Euler angles
		*/
		static Quaternion<T> FromEuler(const Vector3<T>& eulerAngles);

		/*
		  @brief	Default identity quaternion.
		*/
		/*explicit*/ Quaternion(IdentityInitT = IdentityInit) noexcept
			:_w(T{ 1 }), _v(ZeroInit) {}

		/*
		  @brief	Zero-clear quaternion
		*/
		explicit Quaternion(ZeroInitT) noexcept
			:_w(T{ 0 }), _v(ZeroInit) {}

		/*
		  @brief	Construct with scalar part and vector part
		*/
		explicit Quaternion(const T& scalar, const Vector3<T>& imaginary)
			:_w(scalar), _v(imaginary) {}

		/*
		  @brief	Rotate target in right-hand rule.
		*/
		Vector3<T> Tranform(const Vector<3, T>& target) const;

		/*
		  @brief	Get the vector part
					For now, i think wo do not need to modify quaternion from outer directly.
		*/
		const Vector3<T>& Vector() const { return _v; }

		/*
		  @brief	Get the scalar part
		*/
		T Scalar() const { return _w; }


		/*
		  @brief	Get the rotation angle for rotation quaternion.
		  @caution	Due to the precision of floating-point number, the return value of Angle cannot be equal to input angle excatly.
		*/
		T  Angle() const { return 2 * static_cast<T>(std::acos(_w)); }

		/*
		  @brief	Convert to matrix form.
		*/
		Matrix<3, T> ToMatrix() const;
		/*
		  @brief	covert to euler angles
		*/
		Vector3<T> ToEuler() const;
		/*
		  @brief	Get the norm of quaternion.
		*/
		T Norm() const;

		/*
		  @brief	Check if quaternion is normalized
		*/
		bool IsNormalized() const { return equals(Norm(), T{ 1 }); }

		/*
		  @brief	Get the normalized quaternion.
		*/
		Quaternion<T> Normalize() const { return (*this) / Norm(); }

		/*
		  @brief	Get the conjugate quaternion.
		*/
		Quaternion<T> Conjugate() const { return Quaternion<T>(_w, -_v); }

		/*
		  @brief	Get the inverse quaternion.
					In the case of rotation, Q.Inverse() is the inverse rotation of Q.
		*/
		Quaternion<T> Inverse() const;

		/*
		  @brief	Return the negative of quaternion
		  @caution	In the case of rotation, -Q is same as Q.
					To get inverse of Q, using Q.Inverse() instead.
		*/
		Quaternion<T> operator-() const { return Quaternion<T>(-_w, -_v); }

		Quaternion<T> operator + (const Quaternion<T>& other) const{ return Quaternion(*this) += other; }
		Quaternion<T>& operator+=(const Quaternion<T>& other) { _w += other._w; _v += other._v; return *this; }

		Quaternion<T> operator - (const Quaternion<T>& other) const{ return Quaternion(*this) -= other; }
		Quaternion<T>& operator-=(const Quaternion<T>& other) { _w -= other._w; _v -= other._v; return *this; }


		Quaternion<T> operator * (const T& a) const { return Quaternion<T>(_w * a, _v * a); }
		Quaternion<T> operator *(const Quaternion<T>& other) const;
		Quaternion<T>& operator *=(const Quaternion<T>& other);

		/*
		  @brief	Divide by denomitor.
		*/
		Quaternion<T> operator / (const T& denomitor) const { assert(denomitor); return Quaternion<T>(_w / denomitor, _v / denomitor); }

	private:
		T _w;
		Vector3<T>	_v;
	};

	template<typename T> Quaternion<T> Quaternion<T>::Rotate(const Rad<T>& angle, const Vector3<T>& axis) {
		T halfAngle = static_cast<T>(angle) / T{ 2 };
		Vector3<T> n = axis.Normalize();
		T sinVal = static_cast<T>(std::sin(halfAngle));
		T w = static_cast<T>(std::cos(halfAngle));

		return Quaternion<T>(w, n * sinVal);
	}

	template<typename T> Quaternion<T> Quaternion<T>::FromEuler(const Vector3<T>& eulerAngles)
	{
		T x = T(Math::Rad<T>(Math::Deg<T>(eulerAngles.X()))) / 2;
		T y = T(Math::Rad<T>(Math::Deg<T>(eulerAngles.Y()))) / 2;
		T z = T(Math::Rad<T>(Math::Deg<T>(eulerAngles.Z()))) / 2;
		T sin_x = std::sin(x), cos_x = std::cos(x);
		T sin_y = std::sin(y), cos_y = std::cos(y);
		T sin_z = std::sin(z), cos_z = std::cos(z);
		T q0 = cos_x * cos_y*cos_z - sin_x * sin_y*sin_z;
		T q1 = sin_x * cos_y*cos_z - cos_x * sin_y*sin_z;
		T q2 = cos_x * sin_y*cos_z + sin_x * cos_y*sin_z;
		T q3 = cos_x * cos_y*sin_z + sin_x * sin_y*cos_z;

		return Quaternion<T>(q0, Math::Vector3<T>(q1, q2, q3));
	}

	template<typename T> Quaternion<T> Quaternion<T>::FromMatrix(const Matrix < 3, T> &m) {
		T vals[] = { m[0][0] + m[1][1] + m[2][2], m[0][0] - m[1][1] - m[2][2], m[1][1] - m[0][0] - m[2][2], m[2][2] - m[0][0] - m[1][1] };

		T* max = std::max_element(vals, vals + sizeof(vals) / sizeof(T));
		int index = std::distance(vals, max);
		T biggest = std::sqrt(*max + T{ 1 }) * T { 0.5 };
		T mult = T{ 0.25 } / biggest;

		T w{ 0 }, x{ 0 }, y{ 0 }, z{ 0 };
		switch (index)
		{
		case 0:
			w = biggest;
			x = (m[1][2] - m[2][1]) * mult;
			y = (m[2][0] - m[0][2]) * mult;
			z = (m[0][1] - m[1][0]) * mult;
			break;

		case 1:
			x = biggest;
			w = (m[1][2] - m[2][1]) * mult;
			y = (m[0][1] + m[1][0]) * mult;
			z = (m[2][0] + m[0][2]) * mult;
			break;

		case 2:
			y = biggest;
			w = (m[2][0] - m[0][2]) * mult;
			x = (m[0][1] + m[1][0]) * mult;
			z = (m[1][2] + m[2][1]) * mult;
			break;

		case 3:
			z = biggest;
			w = (m[0][1] - m[1][0]) * mult;
			x = (m[2][0] + m[0][2]) * mult;
			y = (m[1][2] + m[2][1]) * mult;

			break;
		}
		return Quaternion<T>(w, {x, y, z});
	}

	template<typename T> Matrix<3, T> Quaternion<T>::ToMatrix() const {
		T w = _w, x = _v.X(), y = _v.Y(), z = _v.Z();
		T one(1), two(2);
		return {Math::Vector<3, T>(one - two * y * y - two * z * z,two * x * y - two * w * z , two * x * z + two * w * y),
				Math::Vector<3, T>(two * x * y + two * w * z, one - two * x * x - two * z * z, two * y * z - two * w * x),
				Math::Vector<3, T>(two * x * z - two * w * y,two * y * z + two * w * x, one - two * x * x - two * y * y)};
	}

	template<typename T> Vector3<T> Quaternion<T>::ToEuler() const {
		T w = _w, x = _v.X(), y = _v.Y(), z = _v.Z();
		T one(1), two(2);
		T sin_pitch = two * (y*z + w * x);
		T pitch = std::asin(sin_pitch);
		T yaw, roll;
		if (equals(sin_pitch, T(1)))
		{
			yaw = atan2(two * (x*z + w * y), one - two * y*y - two * z*z);
			roll = T(0);
		}
		else
		{
			yaw = atan2(two*(w * y - x*z), one - two * y*y - two * x*x);
			roll = atan2(two*(w * z - x*y), one - two * x*x - two * z*z);
		}

		return { T(Deg<T>(Rad<T>(pitch))), T(Deg<T>(Rad<T>(yaw))), T(Deg<T>(Rad<T>(roll))) };
	}

	template<typename T> T Quaternion<T>::Norm() const {
		return std::sqrt(std::pow(_w, 2) + _v.Dot());
	}

	template<typename T> Quaternion<T> Quaternion<T>::Inverse() const {
		return this->Conjugate() / this->Norm();
	}

	template<typename T> Quaternion<T> Quaternion<T>::operator *(const Quaternion<T>& other) const {
		return Quaternion<T>(*this) *= other;
	}

	template<typename T> Quaternion<T>& Quaternion<T>::operator *=(const Quaternion<T>& other) {
		T _wBackup = _w;
		_w = _w * other._w - _v * other._v;
		_v = _wBackup * other._v + other._w * _v + Cross(_v, other._v);
		return *this;
	}

	/*
		@caution	This is mathematically equality test, not geometrically.
	*/
	template<typename T> bool operator == (const Quaternion<T>& q1, const Quaternion<T>& q2) {
		return equals(q1.Scalar(), q2.Scalar()) && q1.Vector() == q2.Vector();
	}

	template<typename T> bool operator != (const Quaternion<T>& q1, const Quaternion<T>& q2) {
		return !(q1 == q2);
	}

	/*
		Given 3D-vector p, we extern p to quaternion: p = [0, p] then we can transfrom p to p':
			p' = Qinver * p * Q
	*/
	template<typename T> Vector3<T> Quaternion<T>::Tranform(const Math::Vector<3, T>& target) const{
		return (Inverse() * Quaternion<T>(0, target) * (*this)).Vector();
	}


	template<typename T> Quaternion<T> operator * (const T& a, const Quaternion<T>& q) {
		return Quaternion<T>(a * q.Scalar(), a * q.Vector());
	}

#ifdef TINY_TEST
	template<typename T> std::ostream& operator<<(std::ostream& os, const Quaternion<T>& q) {
		os << "[" << q.Scalar() << ", " << q.Vector().X() << ", " << q.Vector().Y() << ", " << q.Vector().Z() << "]" << std::endl;
		return os;
	}
#endif
} }

#endif // !TINY_MATH_QUATERNION_H
