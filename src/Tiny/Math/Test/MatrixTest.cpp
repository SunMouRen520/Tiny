#include "gtest/gtest.h"
#include "Matrix.h"

using namespace Tiny::Math;

using Vec2f = Vector<2, float>;
using Vec3f = Vector<3, float>;
using Vec4f = Vector<4, float>;

using Matrix2f = Matrix<2, float>;
using Matrix3f = Matrix<3, float>;
using Matrix4f = Matrix<4, float>;

template<std::size_t size> static void CheckEqual(const Matrix<size, float>& m, const float *data, int dataSize, int loopSize = 0) {
	if (!loopSize)
		loopSize = dataSize < size ? dataSize : size;
	for (std::size_t i = 0; i != loopSize; i++)
		for (std::size_t j = 0; j != loopSize; j++)
			EXPECT_EQ(data[i * dataSize + j], m[i][j]);
}

static int index[3] = { 0, 1, 2 };
TEST(MatrixTest, DefaultConstructor) {
	Matrix3f m;
	for (auto i : index) {
		for (auto j : index) {
			if (i == j)
				EXPECT_EQ(m[i][j], 1.0f);
			else
				EXPECT_EQ(m[i][j], 0.0f);
		}
	}
}

TEST(MatrixTest, ZeroConstructor) {
	Matrix3f m(ZeroInit);
	for (auto i : index) {
		for (auto j : index) {
			EXPECT_EQ(m[i][j], 0.f);
		}
	}
}

TEST(MatrixTest, UniformConstructor) {
	Matrix3f m(5.f);
	for (auto i : index) {
		for (auto j : index) {
			EXPECT_EQ(m[i][j], 5.f);
		}
	}
}

TEST(MatrixTest, DiagonalConstructor) {
	Vec3f v(100.f, 200.f, 300.f);
	Matrix3f m(v);
	for (auto i : index) {
		for (auto j : index) {
			if (i == j)
				EXPECT_EQ(m[i][j], v[i]);
			else
				EXPECT_EQ(m[i][j], 0.f);
		}
	}
}

TEST(MatrixTest, ConstructorConvertion) {
	Matrix3f m(Vec3f{ 0.0f, 0.1f, 0.2f }, Vec3f{ 1.0f, 1.1f, 1.2f }, Vec3f{ 2.0f, 2.1f, 2.2f });
	for (auto i : index) {
		for (auto j : index) {
			EXPECT_EQ(m[i][j], i * 1.f + j * 0.1f);
		}
	}

}

TEST(MatrixTest, CopyConstructor) {
	Matrix3f a(Vec3f{ 0.0f, 0.1f, 0.2f }, Vec3f{ 1.0f, 1.1f, 1.2f }, Vec3f{ 2.0f, 2.1f, 2.2f });
	Matrix3f b(a);
	EXPECT_EQ(a, b);

	Matrix3f c = a;
	EXPECT_EQ(c, b);
}

TEST(MatrixTest, ConstructFromOtherDimension) {
	Matrix3f m3(Vec3f(0.0f, 0.1f, 0.2f), Vec3f(1.0f, 1.1f, 1.2f), Vec3f(2.0f, 2.1f, 2.2f));

	const float data[2][2] = { {0.0f, 0.1f}, {1.0f, 1.1f} };
	Matrix2f m2(m3);
	CheckEqual(m2, &data[0][0], 2);
	
	const float data2[3][3] = { {0.0f, 0.1f, 0.2f}, {1.0f, 1.1f, 1.2f},{2.0f, 2.1f, 2.2f} };
	Matrix4f m4(m3);
	CheckEqual(m4, &data2[0][0], 3);

	for (int i = 0; i < 4; i++) {
		EXPECT_EQ(m4[3][i], (i == 3 ? 1.f : 0.f));
		EXPECT_EQ(m4[i][3], (i == 3 ? 1.f : 0.f));
	}
}

TEST(MatrixTest, orthnogal) {
	Matrix3f iden;
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
	Matrix3f iden;
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

TEST(MatrixTest, Inverse) {
	Matrix4f m(Vec4f(3.0f, 5.0f, 8.0f, 4.0f),
		Vec4f(4.0f, 4.0f, 7.0f, 3.0f),
		Vec4f(7.0f, -1.0f, 8.0f, 0.0f),
		Vec4f(9.0f, 4.0f, 5.0f, 9.0f));

	Matrix4f inverse(Vec4f(-60 / 103.0f, 71 / 103.0f, -4 / 103.0f, 3 / 103.0f),
		Vec4f(-66 / 103.0f, 109 / 103.0f, -25 / 103.0f, -7 / 103.0f),
		Vec4f(177 / 412.0f, -97 / 206.0f, 53 / 412.0f, -7 / 206.0f),
		Vec4f(259 / 412.0f, -185 / 206.0f, 31 / 412.0f, 27 / 206.0f));

	Matrix4f _inverse = m.Inverse();

	EXPECT_EQ(_inverse, inverse);
	//EXPECT_EQ(m * _inverse , Matrix4f());  this suffers from the floating point issue, seems like need to define some compare function for Google Test.
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
