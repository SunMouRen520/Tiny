#ifndef Tiny_MATH_VECTOR_H
#define Tiny_MATH_VECTOR_H


#include <cstddef> //TODO:Check if we realy need this include
#include <cstdlib>
#include <cmath>
#include <cassert>

#include "Math/Tools.h"
#include "Math/Angle.h"
#include "Math/Tags.h"

#ifdef TINY_TEST
#include <iostream>
#endif

namespace Tiny { namespace Math {
	template<std::size_t , typename > class Vector;
	namespace Implementation {
		template<std::size_t ...seq> struct Sequence{};
		
		template<std::size_t N, std::size_t ...seq> struct GenerateSeq
			: GenerateSeq<N - 1, N - 1, seq...>{};

		template<std::size_t ...seq> struct GenerateSeq<0, seq...> {
			using Type = Sequence<seq...>;
		};

		template<typename T> T Repeat(T value, std::size_t) {
			return value;
		}

		template<std::size_t otherSize, typename T> T FetchOrZero(const Vector<otherSize, T>& other, std::size_t index) {
			return index >= otherSize ? 0 : other[index];
		}
	}

	/*
		@brief Row vector, eg.[a b c]
		@param size		Vector size
		@param T		Data type

		Vector propertied:
			For Vector a and b:
			1.	Inner product: a * b = a.Mag() * b.Mag() * cos(theta)
			2.	Cross product: a x b = a.Mag() * b.mag() * sin(theta)
				a.	For 2D, this is the area.
				b.	For 3D, thish is the volume.

	*/
	template<std::size_t size, typename T> class Vector {
		static_assert(size != 0, "Vector cannot have 0 size elements!");

		template<std::size_t, typename> friend class Vector;

	public:
		typedef T Type;

		enum : std::size_t {
			Size = size
		};

		/*
			@brief Create Vector from data.
			@attention Use this carefully. No check with data at all.
		*/
		static Vector<size, T>& From(T* data) {
			return *reinterpret_cast<Vector<size, T>*>(data);
		}

		/*const overload*/
		static const Vector<size, T>& From(const T* data) {
			return *reinterpret_cast<const Vector<size, T>*>(data);
		}

		/*constructor*/
		/*Variadic template constructor, seems like redundancy*/
		template<typename ...U, typename std::enable_if<sizeof...(U)+1 == size, T>::type* = nullptr> constexpr /*explicit*/ Vector(T first, U... next) noexcept: _data{ first, next... }{
			//static_assert(sizeof...(U)+1 == size, "invalid parameter length in variadic template constructor");
		}

		/*
			@brief	Construct the vector with same value , delegating constructor
		*/
		explicit Vector(const T uniform)
			:Vector(Implementation::GenerateSeq<size>::Type(), uniform) {}

		/*
			@brief	Default constructor for vector, all elements iniatialize to 0.
		*/
		/*explicit*/ Vector(ZeroInitT = ZeroInit) noexcept :Vector(0) {}


		/*
			@brief	Default copy constructor
		*/
		Vector(const Vector<size, T>& another) = default;

		/*destructor*/
		~Vector() = default;

		/*
			@brief Check if zero vector
		*/
		bool Zero() const { return equals(Magnitude(), T(0)); }

		/*
			@brief Normalized
			@caution Only avaliable for float-point Vector.
		*/
		typename std::enable_if<std::is_floating_point<T>::value, Vector<size, T>>::type Normalize() const;

		/*
			@brief Whether the vector is normalized
		*/
		bool IsNormalized() const;

		/*
			@brief Vector Magnitude
		*/
		template<typename U = T> typename std::enable_if<std::is_floating_point<U>::value, U>::type Magnitude() const{ return std::sqrt(Dot()); }

		/*
			@brief Sum of values in the vector
		*/
		T Sum() const;

		/*
			@brief Dot product of vector itself
		*/
		T Dot() const;

		/* Get raw data*/
		T* Get() { return _data; }
		/*const overload*/
		/*constexpr*/ const T* Get() const { return _data; }

		/*
			@brief	Vector assign
		*/
		Vector<size, T>& operator = (const Vector<size, T> &other) = default;


		/*
			@brief	Vector equal
		*/
		bool operator==(const Vector<size, T> &other) const;

		/*
			@brief	Return true when component-wise bigger than other
		*/
		bool operator > (const Vector<size, T> &other) const;

		/*
			@brief	Reverse
		*/
		Vector<size, T> operator-() const { Vector<size, T> out; for (std::size_t i = 0; i != size; i++) out._data[i] = -_data[i]; return out; }


		/*
			@brief	Vector Add
		*/
		Vector<size, T> operator + (const Vector<size, T> &other) const { return Vector<size, T>(*this) += other; }
		Vector<size, T>& operator+=(const Vector<size, T> &other) { for (std::size_t i = 0; i != size; i++) _data[i] += other._data[i]; return *this; }

		/*
			@brief	Vector Sub
		*/
		Vector<size, T> operator - (const Vector<size, T> &other) const { return Vector<size, T>(*this) -= other; }
		Vector<size, T>& operator-=(const Vector<size, T> &other) { for (std::size_t i = 0; i != size; i++) _data[i] -= other._data[i]; return *this; }

		/*
			@brief	Multiply
		*/
		Vector<size, T> operator*(T number) const { return Vector<size, T>(*this) *= number; }
		Vector<size, T>& operator*=(T co) { for (T &n : _data) n *= co; return *this; }

		/*
			@brief	Division by scalar
		*/
		Vector<size, T> operator /(T divisor) const { return Vector<size, T>(*this) /= divisor;  }
		Vector<size, T>& operator/=(T divisor) { assert(divisor != T(0)); for (T &n : _data) n /= divisor;  return *this; }


		/*
			@brief	Dot product with another Vector<size, T>
		*/
		T operator*(const Vector<size, T> &another) const;

		/*
			@brief	Overload index operation
		*/
		T& operator[](std::size_t index) { return _data[index]; }
		/* const overload*/
		const T& operator[](std::size_t index) const { assert(index < size); return _data[index]; }

	protected:
		template<std::size_t ...seq> Vector(Implementation::Sequence<seq...>, const T& uniform)
			:_data{ Implementation::Repeat(uniform, seq)... } {}

	private:
		T _data[size];
	};

	template<std::size_t size, typename T >
	typename std::enable_if<std::is_floating_point<T>::value, Vector<size, T>>::type Vector<size, T>::Normalize() const {
		Vector<size, T> out;
		T mag = Magnitude();
		for (std::size_t i = 0; i != size; i++)
			out._data[i] = _data[i] / mag;
		return out;
	}

	template<std::size_t size, typename T > inline T Vector<size, T>::Sum() const {
		T sum(0);
		for (const T& n : _data)
			sum += n;
		return sum;
	}

	template<std::size_t size, typename T > inline bool Vector<size, T>::operator==(const Vector<size, T> &another) const {
		for (std::size_t i = 0; i != size; i++){
			if (!equals(_data[i], another._data[i]))
				return false;
		}
		return true;
	}

	template<std::size_t size, typename T > inline T Vector<size, T>::operator*(const Vector<size, T> &another) const{
		T out(_data[0] * another._data[0]);
		for (std::size_t i = 1; i != size; i++) {
			out += _data[i] * another._data[i];
		}
		return out;
	}

	template<std::size_t size, typename T> inline T Vector<size, T>::Dot() const {
		return (*this) * (*this);
	}

	template<std::size_t size, typename T> inline bool Vector<size, T>::operator > (const Vector<size, T>& other) const {
		for (std::size_t i = 0; i != size; i++) {
			if (_data[i] <= other._data[i])
				return false;
		}
		return true;
	}

	/*
		@caution  We can't use equals(in Tools.h) here. Because the result type of std::sqrt(Dot()) can be quite different with T.
		So here is another algorithm:
			Consider magnitude of vector val M in range[1 - epsilon, 1 + epsilon] as 1,
			Dot() result is [1 - 2 * epsilon + epsilon^2, 1 + 2 * epsilon + epsilon ^2], we can omit epsilon^2 here.
			So we take std::abs(Dot() - T(1)) < 2 * epsilon as normalized vector.
	*/
	template<std::size_t size, typename T> inline bool Vector<size, T>::IsNormalized() const{
		return std::abs(Dot() - T(1)) < 2 * std::numeric_limits<T>::epsilon();
	}


	/*
		Free-standing operators.
		Reference: see the discuss about operators inside or outside class: https://stackoverflow.com/questions/4652932/why-define-operator-or-outside-a-class-and-how-to-do-it-properly
	*/
	/*
		@brief Multiply Vector with number, return a new Vector
	*/
	template<std::size_t size, typename T> inline Vector<size, T> operator*(T number, const Vector<size, T> &v) {
		return v * number;
	}

	/*
		@brief Free-standing add operator
	*/
	template<std::size_t size, typename T> Vector<size, T> operator+(const Vector<size, T>& a, const Vector<size, T>& b) {
		return Vector<size, T>(a) += b;
	}

	/*
		@brief Free-standing sub operator
	*/
	template<std::size_t size, typename T> Vector<size, T> operator-(const Vector<size, T>& a, const Vector<size, T>& b) {
		return Vector<size, T>(a) -= b;
	}

	/*
		@brief Free-sstanding div operator
	*/
	template<std::size_t size, typename T> Vector<size, T> operator/(const T& a, const Vector<size, T>& b) {
		return {a / b[0], a / b[1]};
	}

#ifdef TINY_TEST
	template<std::size_t size, typename T> std::ostream& operator<<(std::ostream& os, const Vector<size, T>& vector) {
		os << "[";
		for (int i = 0; i < size - 1; i++)
			os << vector[i] << ", ";
		
		os << vector[size - 1] << "]" << std::endl;
		return os;
	}
#endif
}}


#endif
