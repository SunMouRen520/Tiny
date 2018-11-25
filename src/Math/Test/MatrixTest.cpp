#include "gtest/gtest.h"
#include "Matrix.h"

using namespace Tiny::Math;

using Vec2f = Vector<2, float>;
using Vec3f = Vector<3, float>;

using Matrix2f = Matrix<2, float>;
using Matrix3f = Matrix<3, float>;

template<std::size_t size> static void CheckEqual(const Matrix<size, float>& m, const float (&data)[size][size]) {
	for (std::size_t i = 0; i != size; i++)
		for (std::size_t j = 0; j != size; j++)
			EXPECT_EQ(m[i][j], data[i][j]);
}

TEST(MatrixTest, Uniform) {
	Matrix3f u = Matrix3f::Uniform(1.0f);
	const float one[3][3] = { {1.0f, 1.0f, 1.0f},{ 1.0f, 1.0f, 1.0f },{ 1.0f, 1.0f, 1.0f } };
	CheckEqual(u, one);
}

TEST(MatrixTest, Identity) {
	Matrix2f iden = Matrix2f::Identity();
	const float data[2][2] = { {1.0f, 0.0f}, {0.0f, 1.0f} };
	CheckEqual(iden, data);
}

TEST(MatrixTest, Constructor) {
	Matrix3f m;
	Matrix3f zero = Matrix3f::Uniform(0.0f);
	EXPECT_EQ(m, zero);

	Matrix3f initialize(Vec3f(0.0f, 0.1f, 0.2f), Vec3f(1.0f, 1.1f, 1.2f), Vec3f(2.0f, 2.1f, 2.2f));
	const float data[3][3] = { {0.0f, 0.1f, 0.2f}, {1.0f, 1.1f, 1.2f},{2.0f, 2.1f, 2.2f} };
	CheckEqual(initialize, data);

	Matrix3f copy(initialize);
	CheckEqual(copy, data);
}

TEST(MatrixTest, orthnogal) {
	Matrix3f iden = Matrix3f::Identity();
	EXPECT_TRUE(iden.Orthogonal());

	const float v1 = std::sqrt(2.0f) / 2.0f;
	Matrix3f crafed(Vec3f(v1, v1, 0.0f),
					Vec3f(-v1, v1, 0.0f),
					Vec3f(0.0f, 0.0f, 1.0f));
	EXPECT_TRUE(crafed.Orthogonal());
}

TEST(MatrixTest, Determinant) {
	const float f1(5463.3f), f2(989.5f), f3(323.f), f4(14252.0f), f5(5656.89f), f6(99.0f);
	Matrix2f m2(Vec2f(f1, f2), Vec2f(f3, f4));
	EXPECT_TRUE(equals(m2.Determinant(), f1 * f4 - f2 * f3));

	Matrix3f m3(Vec3f(1.0f, 1.0f, 1.0f), Vec3f(f1, f2, f3), Vec3f(f4, f5, f6));
	const float vd = m3.ij(0, 0).Determinant() - m3.ij(0, 1).Determinant() + m3.ij(0, 2).Determinant();
	EXPECT_TRUE(equals(vd , m3.Determinant()));
}


TEST(MatrixTest, Invertible) {
	Matrix3f iden = Matrix3f::Identity();
	EXPECT_TRUE(iden.Invertible());


	Matrix2f m2(Vec2f(1.0f, 0.0f), Vec2f(2.0f, 0.0f));
	EXPECT_FALSE(m2.Invertible());

	Matrix3f m3(Vec3f(1.0f, 0.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f), Vec3f(1.0f, 1.0f, 0.0f));
	EXPECT_FALSE(m3.Invertible());

	Matrix3f m4(Vec3f(321.65f, 2323.12f, 2326.2f), Vec3f(36.4f, 3236.4f, 9896.2131f), Vec3f(3265.9f, 231.5f, 5698.53f));
	EXPECT_TRUE(m4.Invertible());
}

TEST(MatrixTest, ij) {
	const Vec3f row1(0.0f, 0.1f, 0.2f);
	const Vec3f row2(1.0f, 1.1f, 1.2f);
	const Vec3f row3(2.0f, 2.1f, 2.2f);

	Matrix3f m1(row1, row2, row3);
	EXPECT_EQ(m1.ij(0, 0), Matrix2f(Vec2f(1.1f, 1.2f), Vec2f(2.1f, 2.2f)));
	EXPECT_EQ(m1.ij(1, 1), Matrix2f(Vec2f(0.0f, 0.2f), Vec2f(2.0f, 2.2f)));
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
