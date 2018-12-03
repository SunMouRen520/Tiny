#ifndef TINY_MATH_ANGLE_H
#define TINY_MATH_ANGLE_H

#include "Math/Tools.h"

namespace Tiny { namespace Math {
	template<typename T> class Rad;

	/*
		@bried MeasurementUnit provide the common operations for unit of measurement.
		TODO:
			1.
	*/
	template<template<typename> class Derived, typename T> class MeasurementUnit {
		template<template<typename> class, typename> friend class MeasurementUnit;
	public:
		/*
			@brief constructors
		*/
		explicit MeasurementUnit() :_data(0) {}
		explicit MeasurementUnit(T v) :_data(v) {}
		MeasurementUnit(const MeasurementUnit<Derived, T>& other) = default;

		/*
			@brief convert from another type U
		*/
		template<typename U> explicit MeasurementUnit(const MeasurementUnit<Derived, U>& other) :_data(other._data) {}

		bool operator == (const MeasurementUnit<Derived, T>& other) const { return equals(_data, other._data); }
		bool operator > (const MeasurementUnit<Derived, T>& other) const { return _data > other._data; }
		bool operator >= (const MeasurementUnit<Derived, T>& other) const { return (operator ==(other) || operator>(other)); }
		bool operator < (const MeasurementUnit<Derived, T>& other) const { return !operator>=(other); }
		bool operator <= (const MeasurementUnit<Derived, T>& other) const { return (operator ==(other) || operator<(other)); }
		bool operator != (const MeasurementUnit<Derived, T>& other) const { return (!operator == (other)); }

		MeasurementUnit<Derived, T>& operator+=(const MeasurementUnit<Derived, T>& other) { _data += other._data;	return *this; }
		MeasurementUnit<Derived, T>& operator-=(const MeasurementUnit<Derived, T>& other) { _data -= other._data;	return *this; }
		MeasurementUnit<Derived, T>& operator*=(const MeasurementUnit<Derived, T>& other) { _data *= other._data;	return *this; }
		MeasurementUnit<Derived, T>& operator/=(const MeasurementUnit<Derived, T>& other) { _data /= other._data;	return *this; }

		MeasurementUnit<Derived, T> operator+ (const MeasurementUnit<Derived, T>& other) const { return MeasurementUnit<Derived, T>(_data) += other; }
		MeasurementUnit<Derived, T> operator- (const MeasurementUnit<Derived, T>& other) const { return MeasurementUnit<Derived, T>(_data) -= other; }
		MeasurementUnit<Derived, T> operator* (const MeasurementUnit<Derived, T>& other) const { return MeasurementUnit<Derived, T>(_data) *= other; }
		MeasurementUnit<Derived, T> operator/ (const MeasurementUnit<Derived, T>& other) const { return MeasurementUnit<Derived, T>(_data) /= other; }

		MeasurementUnit<Derived, T>	operator-() { return MeasurementUnit<Derived, T>(-_data); }

		explicit operator T() const { return _data; }

	private:
		T _data;
	};

	template<typename T> class Deg :public MeasurementUnit<Math::Deg, T> {
	public:
		/**/
		explicit Deg() :MeasurementUnit<Math::Deg, T>() {}

		Deg(const T& v) :MeasurementUnit<Math::Deg, T>(v) {}

		Deg(const Deg& other) = default;

		/*
			@brief Convert from redian to degree
		*/
		Deg(const MeasurementUnit<Rad, T>& rad) :MeasurementUnit<Math::Deg, T>(T(rad) * T(180) / M_PI) {}

	};

	template<typename T> class Rad :public MeasurementUnit<Math::Rad, T> {
	public:
		explicit Rad() :MeasurementUnit<Math::Rad, T>() {}

		Rad(const T& v) :MeasurementUnit<Math::Rad, T>(v) {}

		Rad(const Rad& other) = default;

		/*
			@brief Convert from defree to radian
		*/
		Rad(const MeasurementUnit<Deg, T>& deg) :MeasurementUnit<Math::Rad, T>(T(deg) / T(180) * M_PI) {}
	};

}
}

#endif
