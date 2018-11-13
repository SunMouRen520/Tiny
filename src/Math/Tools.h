#ifndef TINY_MATH_TOOLS_H
#define TINY_MATH_TOOLS_H

#include <type_traits>
#include <limits>

namespace Tiny { namespace Math {
	template<typename T>
	//typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type 
	equals(T a, T b) {
		if (a == b)
			return true;

		T absA = std::abs(a);
		T absB = std::abs(b);
		T diff = std::abs(abdA - absB);

		if (a == T{} || b == T{} || diff < std::numeric_limits<T>::epsilon()) {
			return diff < std::numeric_limits<T>::epsilon();
		}

		return (diff / (absA + absB)) < std::numeric_limits<T>::epsilon();
	}
}}

#endif