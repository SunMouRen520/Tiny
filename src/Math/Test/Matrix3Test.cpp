#include "gtest\gtest.h"
#include "Matrix3.h"
#include <iostream>

using namespace Tiny::Math;

using Matrix3f = Matrix3<float>;
using Vec2f = Vector2<float>;
using Vec3f = Vector3<float>;

namespace Tiny { namespace Math { 
	std::ostream &operator<<(std::ostream& os, const Matrix3f& m) {
		os << "| " << m[0][0] << ",\t" << m[0][1] << ",\t" << m[0][2] << " |" << std::endl
			<< "| " << m[1][0] << ",\t" << m[1][1] << ",\t" << m[1][2] << " |" << std::endl
			<< "| " << m[2][0] << ",\t" << m[2][1] << ",\t" << m[2][2] << " |" << std::endl;
		return os;
	}
}
}

template<std::size_t size> static void CheckEqual(const Matrix<size, float>& m, const float(&data)[size][size]) {
	for (std::size_t i = 0; i != size; i++)
		for (std::size_t j = 0; j != size; j++)
			EXPECT_EQ(m[i][j], data[i][j]);
}

TEST(Matrix3Test, Constructors) {
	Matrix3f m;
	EXPECT_EQ(m, Matrix3f::Uniform(0.0f));

	const float data[3][3] = { {0.0f, 0.1f, 0.2f}, {1.0f, 1.1f, 1.2f}, {2.0f, 2.1f, 2.2f} };
	Matrix3f m2({ {0.0f, 0.1f, 0.2f}, {1.0f, 1.1f, 1.2f}, {2.0f, 2.1f, 2.2f} });
	CheckEqual(m2, data);

	Matrix3f m3(m2);
	EXPECT_EQ(m2, m3);
}

TEST(Matrix3Test, Scale) {
	Vec3f v(1.0f, 1.0f, 1.0f);
	Matrix3f scale = Matrix3f::Scale(Vec2f(5.2f, 4.8f));
	EXPECT_EQ(v * scale, Vec3f(5.2f, 4.8f, 1.0f));

	Vec3f v2(5.3f, 23.0f, 99.0f);
	EXPECT_EQ(v2 * scale, Vec3f(5.2f * 5.3f, 23.0f * 4.8f, 99.0f));
}

TEST(Matrix3Test, shear) {
	Vec3f v(1.0f, 2.0f, 1.0f);
	Matrix3f shear = Matrix3f::Shear(Vec2f(5.0f, 4.0f));
	EXPECT_EQ(v * shear, Vec3f(11.0f, 6.0f, 1.0f));
	
	Vec3f v2(0.5f, 10.0f, 1.0f);
	Matrix3f shear2 = Matrix3f::Shear(Vec2f(4.4f, 5.5f));
	EXPECT_EQ(v2 * shear2, Vec3f(44.5f, 12.75f, 1.0f));
}

TEST(Matrix3Test, Transpose) {
	Vec3f v1(1.0f, 1.0f, 1.0f);
	Matrix3f t1 = Matrix3f::Transpose(Vec2f(1.0f, 1.0f));
	EXPECT_EQ(v1 * t1, Vec3f(2.0f, 2.0f, 1.0f));

	Vec3f v2(321.0f, 568.45f, 269.584f);
	Matrix3f t2 = Matrix3f::Transpose(Vec2f(568.0f, 9898.0f));
	Vec3f r = v2 * t2;
	EXPECT_EQ(r, Vec3f(321.0f + 568.0f * 269.584f, 568.45f + 9898.0f * 269.584f, 269.584f));
}


TEST(Matrix3Test, Rotate) {
	Vec3f v1(1.0f, 0.0f, 0.0f);
	Vec3f v2(10.0f, 10.0f, 0.0f);

	Matrix3f r1 = Matrix3f::Rotate(Rad<float>(M_PI / 2));
	Matrix3f r2 = Matrix3f::Rotate(Rad<float>(M_PI));
	Matrix3f r3 = Matrix3f::Rotate(Rad<float>(-M_PI / 2));

	EXPECT_EQ(v1 * r1, Vec3f(0.0f, 1.0f, 0.0f));
	EXPECT_EQ(v2 * r2, Vec3f(-10.0f, -10.0f, 0.0f));

	EXPECT_EQ(v2 * r1, Vec3f(10.0f, -10.0f, 0.0f));
	EXPECT_EQ(v1 * r3, Vec3f(0.0f, -1.0f, 0.0f));
}

TEST(Matrix3Test, Reflection) {
	Vec2f reflect_axis_1(1.0f, 0.0f);
	Matrix3f reflect1 = Matrix3f::Reflection(reflect_axis_1);

	Vec2f reflect_axis_2(-1.0f, 0.0f);
	Matrix3f reflect2 = Matrix3f::Reflection(reflect_axis_2);

	const float a = std::sqrt(2.0f) / 2.0f;
	Vec2f reflect_axis_3(a, a);
	Matrix3f reflect3 = Matrix3f::Reflection(reflect_axis_3);


	Vec2f y_up(0.0f, 1.0f);
	Vec2f x_right(1.0f, 0.0f);
	EXPECT_EQ(y_up * reflect1, Vec2f(0.0f, -1.0f));
	EXPECT_EQ(y_up * reflect2, Vec2f(0.0f, -1.0f));
	EXPECT_EQ(x_right * reflect3, Vec2f(0.0f, 1.0f));
}

TEST(Matrix3Test, Projection) {
	Vec2f v1(32.1f, 66989.f);

	Matrix3f project_x = Matrix3f::Projection(Vec2f(1.0f, 0.0f));
	Matrix3f project_y = Matrix3f::Projection(Vec2f(0.0f, 1.0f));
	Vec2f pv3 = Vec2f(1.0f, 1.0f).Normalize();
	Matrix3f project3 = Matrix3f::Projection(pv3);

	EXPECT_EQ(v1 * project_x, Vec2f(32.1f, 0.0f));
	EXPECT_EQ(v1 * project_y, Vec2f(0.0f, 66989.f));

	Vec2f v1_p3 = v1 * project3;
	Vec2f v1_p3_check = (v1 * pv3) * pv3;

	EXPECT_EQ(v1_p3, v1_p3_check);
}

TEST(Matrix3Test, ScaleAlongVector) {
	Vec2f v1(1.0f, 1.0f);
	Vec2f v2(98.32f, 195.2f);

	Vec2f vector_scale_1(1.0f, 0.0f);
	Matrix3f scale1 = Matrix3f::ScaleAlongVector(vector_scale_1.Normalize(), 10.0f);

	Vec2f vector_scale_2(1.0f, 1.0f);
	Matrix3f scale2 = Matrix3f::ScaleAlongVector(vector_scale_2.Normalize(), 10.0f);

	Vec2f vector_scale_3 = Vec2f(568.f, 898.0f).Normalize();
	const float k = 13.3f;
	Matrix3f scale3 = Matrix3f::ScaleAlongVector(vector_scale_3, k);


	EXPECT_EQ(v1 * scale1, Vec2f(10.0f, 1.0f));
	EXPECT_EQ(v1 * scale2, Vec2f(10.0f, 10.0f));

	Vec2f v2_scale3 = v2 * scale3;
	
	Vec2f raw_vector_along = (v2 * vector_scale_3) * vector_scale_3;
	Vec2f raw_vector_perpen = v2 - raw_vector_along;
	EXPECT_EQ(v2_scale3, raw_vector_along * k + raw_vector_perpen);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}