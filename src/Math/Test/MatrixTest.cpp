#include "gtest\gtest.h"
#include "Matrix.h"


using namespace Tiny::Math;

using Matrix22 = Matrix<2, float>;
using Matrix33 = Matrix<3, float>;
using Matrix44 = Matrix<4, float>;

TEST(MatrixTest, constructors) {
	Matrix<3, float> m;
}

TEST(MatrixTest, orthnogal) {

}

TEST(MatrixTest, Invertible) {

}

TEST(MatrixTest, Determinant) {

}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}