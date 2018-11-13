#ifndef Tiny_MATH_VECTOR_H
#define Tiny_MATH_VECTOR_H


#include <cstddef>
#include <cstdlib>
#include <cassert>

#include "Tools.h"

/*
	Row vector, eg.[a b c]
*/

namespace Tiny { namespace Math { 
	/*
		@brief Dot product for two vectors
	*/
	template<std::size_t size, typename T> inline T Dot(const Vector<size, T> &a, const Vector<size, T> &b) {
		return (a * b).sum()
	}

	/*
		Multiply Vector with number, return a new Vector
	*/
	template<std::size_t size, typename T> inline Vector<size, T> operator*(T number, const Vector<size, T> &v) {
		return v * number;
	}

	/*
		Free-standing add operator. 
		Reference: see the discuss about operators inside or outside class: https://stackoverflow.com/questions/4652932/why-define-operator-or-outside-a-class-and-how-to-do-it-properly
	*/
	template<std::size_t size, typename T> Vector<size, T> operator+(const Vector<size, T> &a, const Vector<size, T> &b) {
		return Vector<size, T>(a) += b;
	}

	/*
		Free-standing sub operator
	*/
	template<std::size_t size, typename T> Vector<size, T> operator-(const Vector<size, T> &a, const Vector<size, T> &b) {
		return Vector<size, T>(a) -= b;
	}


	template<std::size_t size, typename T> class Vector {
		static_assert(size != 0, "Vector cannot have 0 size elements!");

		template<std::size_t, typename> friend class Vector;

	public:
		typedef T Type;

		/*constructor*/
		/*Variadic template constructor,I do not think this is a proper use. Static from() method much better
		template<typename T, typename ...Args>
		explicit Vector(T first, Args... args) : _data{ first, ...args } {}
		*/

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
		
		explicit Vector(void) noexcept{}
		
		/*destructor*/
		~Vector(){}

		bool Zero() const {
			return equal(Magnitude(), T(1));
		}

		/*
			Normalized
			@caution Only avaliable for float-point Vector.
		*/
		typename std::enable_if<std::is_floating_point<T>, void>::type Normalize() {
			assert(!Zero());
			T mag = Magnitude();
			for(T &n : _data)
				n /= mag;
		}

		/*const overload*/
		typename std::enable_if<std::is_floating_point<T>, Vector<size, T>>::type Normalize() const {
			Vector<size, T> out;
			T mag = Magnitude();
			for (std::size_t i = 0; i != size; i++)
				out._data[i] = _data[i] / mag;
			return out;
		}

		/*
			Whether the vector is normalized
		*/
		bool IsNormalized() const;

		/*
			Vector Magnitude
		*/
		template<typename U = T> typename std::enable_if<std::is_floating_point<U>::value, U>::type Magnitude() const() {
			return std::sqrt(Dot());
		}

		/*
			Sum of values in the vector
		*/
		T Sum() const() {
			T sum(0);
			for (const T& n : _data)
				sum += n;
			return sum;
		}

		/*
			Dot product of vector itself
		*/
		T Dot() const();


		/* Get raw data*/
		T* Get() { return _data; }
		/*const overload*/
		constexpr const T* const Get() { return _data; }

		/*
			Vector Add
		*/
		void operator+=(const Vector<size, T> &other) {
			for(T &n : _data)
				n += other._data[i];
		}

		/*
			Vector Sub
		*/
		void operator-=(const Vector<size, T> &other) {
			for(T &n : _data)
				n -= other._data[i];
		}

		/*
			Division by scalar
		*/
		void operator/=(T divisor) {
			assert(divisor != T(0), "Invalid divisor for vector division");
			for(T &n : _data)
				_data[i] /= divisor;
		}


		/*
			Dot product with another Vector<size, T>
		*/
		T operator*(const Vector<size, T> &another) const {
			T out(_data[0] * another._data[0]);
			for (std::size_t i = 1; i != size; i++) {
				out += _data[i] * another._data[i];
			}
			return out;
		}

		/*
			Multiply number component-wise and assign
		*/
		Vector<size, T> operator*=(T number) {
			for()
		}

		/*
			Multiply number component-wise
		*/
		void operator*(T number) {
			for (std::size_t i = 0; i < size; i++)
				_data[i] *= number
		}

		/* const overload*/
		Vector<size, T> operator*(T number) const {
			return Vector<size, T>(*this) * number;
		}

		/*
			Overload index operation
		*/
		T operator[](std::size_t index) { return _data[index]; }
		/* const overload*/
		const T& operator[](std::size_t index) const {
			assert(index < size);
			return _data[index];
		}

	private:
		T _data[size];
	};

	template<std::size_t size, typename T> inline T Vector<size, T>::Sum() const {
		T out(_data[0]);
		for (std::size_t i = 1; i != size; i++)
			out += _data[i];
		return out;
	}

	template<std::size_t size, typename T> inline T Vector<size, T>::Dot() const {
		return Dot(*this, *this);
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
}}


#endif

