#ifndef TINY_MATH_TOOLS_H
#define TINY_MATH_TOOLS_H

#include <type_traits>
#include <limits>
#include <cmath>

namespace Tiny { namespace Math {
    /* @brief	PI */
#ifndef M_PI
	constexpr float M_PI = 3.14159265358979323846f;
#endif
	template<typename T>
	//typename std::enable_if<std::is_floating_point<T>::value, bool>::type
	bool equals(T a, T b) {
		if (a == b)
			return true;

		T absA = std::abs(a);
		T absB = std::abs(b);
		T diff = std::abs(a - b);

		if (a == T{} || b == T{} || diff < std::numeric_limits<T>::epsilon()) {
			return diff < std::numeric_limits<T>::epsilon();
		}

		return (diff / (absA + absB)) < std::numeric_limits<T>::epsilon();
	}

	/*
	  @brief	Generic linear interpolation
	*/
	template<typename T, typename U> T Lerp(const T& a, const T&b, const U& t) {
		return (1 - t) * a + t * b;
	}
}}

#endif
