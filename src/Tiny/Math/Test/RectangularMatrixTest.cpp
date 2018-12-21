#include "gtest/gtest.h"
#include "RectangularMatrix.h"


using namespace Tiny::Math;

using Matrix22 = RectangularMatrix<2, 2, float>;
using Matrix32 = RectangularMatrix<3, 2, float>;
using Matrix24 = RectangularMatrix<2, 4, float>;
using Matrix42 = RectangularMatrix<4, 2, float>;
using Matrix34 = RectangularMatrix<3, 4, float>;

using Vec2 = Vector<2, float>;
using Vec3 = Vector<3, float>;
using Vec4 = Vector<4, float>;

class TestMatrixMultiply {
public:
	typedef int p;

	p i;
};

const float data_1[6] = { 321.0f, 566.0f, 432.0f, 5643.56f, 323.85f, 36.8f };
const float data_2[6] = { 97.34f, 93.2f, 12.5f, 35.4f, 65.0f, 123.7f };
const float data_3[6] = { 1.0f, 1.0f, 2.0f, 2.0f, 3.0f, 3.0f };

const float data_4[8] = { 2.0f, 3.0f, 4.0f, 5.0f, 321.0f, 22.0f, 54.0f, 98.0f };

TEST(RectangularMatrixTest, DefaultConstructor) {
	Matrix32 m;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 2; j++)
			EXPECT_EQ(m[i][j], 0.f);
}

TEST(RectangularMatrixTest, ConstructorConversion) {
	Matrix32 m{ Vec2{0.f, 0.1f}, Vec2{1.f, 1.1f}, Vec2{2.f, 2.1f} };
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 2; j++)
			EXPECT_EQ(m[i][j], (i * 1.f + j * 0.1f));

	Matrix32 complete(Vec2(2.3f, 321.0f), Vec2(33.0f, 12.3f), Vec2(3233.3f, 65.0f));
	EXPECT_EQ(complete[0][0], 2.3f);
	EXPECT_EQ(complete[0][1], 321.0f);
	EXPECT_EQ(complete[1][0], 33.0f);
	EXPECT_EQ(complete[1][1], 12.3f);
	EXPECT_EQ(complete[2][0], 3233.3f);
	EXPECT_EQ(complete[2][1], 65.0f);
}


TEST(RectangularMatrixTest, CopyConstructor) {
	Matrix32 a(Vec2(2.3f, 321.0f), Vec2(33.0f, 12.3f), Vec2(3233.3f, 65.0f));
	Matrix32 b(a);
	EXPECT_EQ(a, b);

	Matrix32 c = a;
	EXPECT_EQ(a, b);
}

TEST(RectangularMatrixTest, GetData) {
	Matrix32 m1(data_1);
	EXPECT_EQ(m1[0][0], data_1[0]);
	EXPECT_EQ(m1[0][1], data_1[1]);
	EXPECT_EQ(m1[1][0], data_1[2]);
	EXPECT_EQ(m1[1][1], data_1[3]);
	EXPECT_EQ(m1[2][0], data_1[4]);
	EXPECT_EQ(m1[2][1], data_1[5]);

	Vec3 col1 = m1.Column(0);
	Vec3 col2 = m1.Column(1);
	EXPECT_EQ(col1[0], data_1[0]);
	EXPECT_EQ(col1[1], data_1[2]);
	EXPECT_EQ(col1[2], data_1[4]);

	EXPECT_EQ(col2[0], data_1[1]);
	EXPECT_EQ(col2[1], data_1[3]);
	EXPECT_EQ(col2[2], data_1[5]);
}

TEST(RectangularMatrixTest, MatrixAdd) {
	Matrix32 add_1(data_1);
	Matrix32 add_2(data_2);

	Matrix32 result1= add_1 + add_1;
	float *result1_data = result1.Get();
	EXPECT_TRUE(std::equal(result1_data, result1_data + 6, data_1, [](const float& v1, const float& v2) ->bool { return v1 == 2 * v2; }));
	
	Matrix32 add_1_plus_add_2 = add_1 + add_2;
	float data_check[6] = {};
	for (std::size_t i = 0; i < 6; i++)
		data_check[i] = data_1[i] + data_2[i];
	float *result2_data = add_1_plus_add_2.Get();
	EXPECT_TRUE(std::equal(result2_data, result2_data + 6, data_check));
}

TEST(RectangularMatrixTest, MatrixSub) {
	Matrix32 sub_1(data_1);

	Matrix32 result1 = sub_1 - sub_1;
	EXPECT_EQ(result1, Matrix32());

	Matrix32 sub_2(data_3);
	EXPECT_EQ(sub_1 - sub_2, Matrix32(Vec2(320.0f, 565.0f), Vec2(430.0f, 5641.56f), Vec2(320.85f, 33.8f)));
}

TEST(RectangularMatrixTest, MatrixMul) {
	//mul zero matrix
	Matrix32 m(data_3);

	Matrix24 zero;
	Matrix34 time_zero = m * zero;
	EXPECT_EQ(time_zero, Matrix34());

	//mul non-zero matrix
	Matrix24 n(data_4);
	Matrix34 mn = m * n;
	
	Vec3 m_col1 = m.Column(0);
	Vec3 m_col2 = m.Column(1);
	Matrix34 factorize_of_mn = Outer(m_col1, n[0]) + Outer(m_col2, n[1]);
	EXPECT_EQ(mn, factorize_of_mn);

	//mul number
	Matrix24 result_2 = n * 100;
	float *result_data = result_2.Get();
	EXPECT_TRUE(std::equal(result_data, result_data + 8, data_4, [](const float& v1, const float& v2) -> bool {return v1 == (v2 * 100); }));

	Matrix24 t1(Vec4(1.f, 2.f, 3.f, 4.f), Vec4(2.f, 3.f, 4.f, 5.f));
	Matrix42 t2(Vec2(1.f, 2.f), Vec2(3.f, 4.f), Vec2(2.f, 3.f), Vec2(4.f, 5.f));

	Matrix22 result = t1 * t2;
	EXPECT_EQ(result, Matrix22(Vec2(29.f, 39.f), Vec2(39.f, 53.f)));
}


TEST(RectangularMatrixTest, Div) {
	Matrix32 m(data_3);
	
	Matrix32 result_1 = m / 1;
	EXPECT_EQ(m, result_1);

	Matrix32 result_2 = m / 10.0f;
	float *result_data = result_2.Get();
	EXPECT_TRUE(std::equal(result_data, result_data + 6, data_3, [](const float& v1, const float& v2) -> bool {return v1 == static_cast<float>(v2 / 10.0f); }));
}


//vector mul matrix
TEST(RectangularMatrixTest, vectors) {
	typedef Vector<3, float> Vec3;
	typedef Vector<5, float> Vec5;
	Vec3 v(1.0f, 1.0f, 1.0f);
	RectangularMatrix<3, 5, float> m(Vec5(1.0f, 0.0f, 0.0f, 0.0f, 0.0f),
		Vec5(1.0f, 0.0f, 0.0f, 0.0f, 0.0f),
		Vec5(1.0f, 0.0f, 0.0f, 0.0f, 0.0f));
	
	Vec5 result = v * m;
	EXPECT_EQ(result, Vec5(1.0f, 0.0f, 0.0f, 0.0f, 0.0f) + Vec5(1.0f, 0.0f, 0.0f, 0.0f, 0.0f) + Vec5(1.0f, 0.0f, 0.0f, 0.0f, 0.0f));
}

TEST(RectangularMatrixTest, vector_outer) {
	Vec2 v2(3.0f, 5.0f);
	Vec3 v3(4.0f, 9.0f, 1.0f);
	Matrix32 outer_result = Outer(v3, v2); 
	EXPECT_EQ(outer_result[0][0], 12.0f);
	EXPECT_EQ(outer_result[0][1], 20.0f);
	EXPECT_EQ(outer_result[1][0], 27.0f);
	EXPECT_EQ(outer_result[1][1], 45.0f);
	EXPECT_EQ(outer_result[2][0], 3.0f);
	EXPECT_EQ(outer_result[2][1], 5.0f);
}


TEST(RectangularMatrixTest, transpose) {
	Matrix24 m_raw(data_4);
	Matrix42 m_tran = m_raw.Transpose();
	for (std::size_t i = 0; i < 2; i++)
		for (std::size_t j = 0; j < 4; j++)
			m_raw[i][j] = m_tran[j][i];
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}