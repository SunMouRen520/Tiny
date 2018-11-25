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

        if (a == -b)
            return false;

		T absA = std::abs(a);
		T absB = std::abs(b);
		T diff = std::abs(absA - absB);

		if (a == T{} || b == T{} || diff < std::numeric_limits<T>::epsilon()) {
			return diff < std::numeric_limits<T>::epsilon();
		}

		return (diff / (absA + absB)) < std::numeric_limits<T>::epsilon();
	}
}}

#endif
