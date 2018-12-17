#ifndef TINY_MATH_TEST_TEST_TOOLS_H
#define TINY_MATH_TEST_TEST_TOOLS_H

#include <cstddef>
#include "gtest/gtest.h"

namespace Tiny { namespace Math { 
	template<std::size_t, typename> class Matrix;

	namespace Test {
	template<std::size_t size> static void CheckEqual(const Matrix<size, float>& m, const float *data, int dataSize, int loopSize = 0) {
		if (!loopSize)
			loopSize = dataSize < size ? dataSize : size;
		for (std::size_t i = 0; i != loopSize; i++)
			for (std::size_t j = 0; j != loopSize; j++)
				EXPECT_EQ(data[i * dataSize + j], m[i][j]);
	}
}
}
}

#endif // !TINY_MATH_TEST_TEST_TOOLS_H
