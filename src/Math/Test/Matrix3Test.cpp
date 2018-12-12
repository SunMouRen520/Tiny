#include "gtest/gtest.h"
#include "Matrix3.h"
#include "TestTools.h"

using namespace Tiny::Math;
using namespace Tiny::Math::Test;

using Matrix3f = Matrix3<float>;
using Matrix4f = Matrix<4, float>;
using Vec2f = Vector2<float>;
using Vec3f = Vector3<float>;
using Vec4f = Vector<4, float>;

static int index[] = { 0, 1, 2 };
TEST(Matrix3Test, DefaultConstructor) {
	Matrix3f m;
	for (auto i : index)
		for (auto j : index)
			EXPECT_EQ(m[i][j], (i == j ? 1.f : 0.f));
}

TEST(Matrix3Test, ZeroConstructor) {
	Matrix3f m(ZeroInit);
	
	for (auto i : index)
		for (auto j : index)
			EXPECT_EQ(m[i][j], 0.f);
}

TEST(Matrix3Test, UniformConstructor) {
	Matrix3f a(ZeroInit);
	Matrix3f b(0.f);
	
	EXPECT_EQ(a, b);

	Matrix3f c(100.f);
	for (auto i : index)
		for (auto j : index)
			EXPECT_EQ(c[i][j], 100.f);
}

TEST(Matrix3Test, CopyConstructor) {
	Matrix3f m2({ {0.0f, 0.1f, 0.2f}, {1.0f, 1.1f, 1.2f}, {2.0f, 2.1f, 2.2f} });
	Matrix3f m3(m2);
	EXPECT_EQ(m2, m3);

	Matrix3f m4 = m2;
	EXPECT_EQ(m4, m2);
}

TEST(Matrix3Test, ConstructorFromOtherDimension) {
	const float data[][4] = { { 1.f, 2.f, 3.f, 4.f },
	{ 1.f, 2.f, 3.f, 4.f },
	{ 1.f, 2.f, 3.f, 4.f },
	{ 1.f, 2.f, 3.f, 4.f } };
	Matrix4f m4{ Vec4f{1.f, 2.f, 3.f, 4.f},
		Vec4f{1.f, 2.f, 3.f, 4.f},
		Vec4f{1.f, 2.f, 3.f, 4.f},
		Vec4f{1.f, 2.f, 3.f, 4.f} };


	Matrix3f m3(m4);
	CheckEqual(m3, &data[0][0], 4);

	Matrix4f m42(m3);
	CheckEqual(m42, &data[0][0], 4, 3);
	for (int i = 0; i < 4; i++) {
		EXPECT_EQ(m42[3][i], (i == 3 ? 1.f : 0.f));
		EXPECT_EQ(m42[i][3], (i == 3 ? 1.f : 0.f));
	}
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

	EXPECT_EQ(v2 * r1, Vec3f(-10.0f, 10.0f, 0.0f));
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
	EXPECT_EQ(Vec3f(y_up, 1.f) * reflect1, Vec3f(0.0f, -1.0f, 1.f));
	EXPECT_EQ(Vec3f(y_up, 1.f) * reflect2, Vec3f(0.0f, -1.0f, 1.f));
	EXPECT_EQ(Vec3f(x_right , 1.f)* reflect3, Vec3f(0.0f, 1.0f, 1.f));
}

TEST(Matrix3Test, Projection) {
	Vec2f v1(32.1f, 66989.f);

	Matrix3f project_x = Matrix3f::Projection(Vec2f(1.0f, 0.0f));
	Matrix3f project_y = Matrix3f::Projection(Vec2f(0.0f, 1.0f));
	Vec2f pv3 = Vec2f(1.0f, 1.0f).Normalize();
	Matrix3f project3 = Matrix3f::Projection(pv3);

	EXPECT_EQ(Vec3f(v1, 1.f) * project_x, Vec3f(32.1f, 0.0f, 1.f));
	EXPECT_EQ(Vec3f(v1, 1.f) * project_y, Vec3f(0.0f, 66989.f, 1.f));

	Vec2f v1_p3 = ((Vec3f)(Vec3f(v1, 1.f) * project3)).XY();
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


	EXPECT_EQ(Vec3f(v1, 1.f) * scale1, Vec3f(10.0f, 1.0f, 1.f));
	EXPECT_EQ(Vec3f(v1, 1.f) * scale2, Vec3f(10.0f, 10.0f, 1.f));

	Vec2f v2_scale3 = ((Vec3f)(Vec3f(v2, 1.f) * scale3)).XY();

	Vec2f raw_vector_along = (v2 * vector_scale_3) * vector_scale_3;
	Vec2f raw_vector_perpen = v2 - raw_vector_along;
	EXPECT_EQ(v2_scale3, raw_vector_along * k + raw_vector_perpen);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
