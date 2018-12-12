#include "gtest/gtest.h"
#include "Matrix4.h"
#include "Tools.h"
#include "TestTools.h"

using namespace Tiny::Math;
using namespace Tiny::Math::Test;

using Mat4f = Matrix4<float>;
using Mat3f = Matrix3<float>;

using Vec4f = Vector4<float>;
using Vec3f = Vector3<float>;
using Vec2f = Vector2<float>;

using Radf = Rad<float>;
using Degf = Deg<float>;



static int index[] = { 0, 1, 2, 3};
TEST(Matrix4Test, DefaultConstructor) {
	Mat4f m;
	for (auto i : index)
		for (auto j : index)
			EXPECT_EQ(m[i][j], (i == j ? 1.f : 0.f));
}

TEST(Matrix4Test, ZeroConstructor) {
	Mat4f m(ZeroInit);

	for (auto i : index)
		for (auto j : index)
			EXPECT_EQ(m[i][j], 0.f);
}

TEST(Matrix4Test, UniformConstructor) {
	Mat4f a(ZeroInit);
	Mat4f b(0.f);

	EXPECT_EQ(a, b);

	Mat4f c(100.f);
	for (auto i : index)
		for (auto j : index)
			EXPECT_EQ(c[i][j], 100.f);
}

TEST(Matrix4Test, CopyConstructor) {
	Mat4f m2(Vec4f(0.0f, 0.1f, 0.2f, 0.3f), Vec4f(1.0f, 1.1f, 1.2f, 1.3f), Vec4f(2.0f, 2.1f, 2.2f, 2.3f), Vec4f(3.0f, 3.1f, 3.2f, 3.3f));
	Mat4f m3(m2);
	EXPECT_EQ(m2, m3);

	Mat4f m4 = m2;
	EXPECT_EQ(m4, m2);
}

TEST(Matrix4Test, ConstructorFromOtherDimension) {
	const float data[][4] = { { 1.f, 2.f, 3.f, 4.f },
	{ 1.f, 2.f, 3.f, 4.f },
	{ 1.f, 2.f, 3.f, 4.f },
	{ 1.f, 2.f, 3.f, 4.f } };
	Mat4f m4{ { 1.f, 2.f, 3.f, 4.f },
	{ 1.f, 2.f, 3.f, 4.f },
	{ 1.f, 2.f, 3.f, 4.f },
	{ 1.f, 2.f, 3.f, 4.f } };


	Mat3f m3(m4);
	CheckEqual(m3, &data[0][0], 4, 3);

	Mat4f m42(m3);
	CheckEqual(m42, &data[0][0], 4, 3);
	for (int i = 0; i < 4; i++) {
		EXPECT_EQ(m42[3][i], (i == 3 ? 1.f : 0.f));
		EXPECT_EQ(m42[i][3], (i == 3 ? 1.f : 0.f));
	}
}


TEST(Matrix4Test, Scale) {
	Vec4f target1(1.0f, 2.0f, 3.0f, 1.0f);
	Vec4f target2(0.0f, -1.0f, 3.0f, 1.0f);

	Mat4f scale1 = Mat4f::Scale({2.0f, 1.0f, 1.0f});
	Mat4f scale2 = Mat4f::Scale({1.0f, 2.0f, 2.0f});
	Mat4f scale3 = Mat4f::Scale({1.0f, 1.0f, 1.0f});

	Vec4f target1_scale1 = target1 * scale1;
	EXPECT_EQ(target1_scale1, Vec4f(2.0f, 2.0f, 3.0f, 1.0f));

	Vec4f target1_scale2 = target1 * scale2;
	EXPECT_EQ(target1_scale2, Vec4f(1.0f, 4.0f, 6.0f, 1.0f));

	Vec4f target2_scale1 = target2 * scale1;
	EXPECT_EQ(target2_scale1, Vec4f(0.0f, -1.0f, 3.0f, 1.0f));

	Vec4f target2_scale2 = target2 * scale2;
	EXPECT_EQ(target2_scale2, Vec4f(0.0f, -2.0f, 6.0f, 1.0f));

	EXPECT_EQ(target2 * scale3, target2);
}

TEST(Matrix4Test, Shear) {
	Vec4f target1(1.0f, 2.0f, 3.0f, 1.0f);
	Vec4f target2(0.0f, -1.0f, 3.0f, 1.0f);

	Mat4f shear1 = Mat4f::Shear({1.0f, 0.f, 0.f});
	Mat4f shear2 = Mat4f::Shear({0.0f, 0.f, 0.f});

	EXPECT_EQ(target1 * shear1, Vec4f(1.0f, 3.0f, 4.0f, 1.0f));
	EXPECT_EQ(target2 * shear1, Vec4f(0.0f, -1.0f, 3.0f, 1.0f));

	EXPECT_EQ(target1 * shear2, target1);
}

TEST(Matrix4Test, Transpose) {
	Vec4f target1(1.0f, 2.0f, 3.0f, 1.0f);
	Vec4f target2(0.0f, -1.0f, 3.0f, 1.0f);

	Mat4f tran1 = Mat4f::Transpose({1.0f, 1.0f, 1.0f});
	Mat4f tran2 = Mat4f::Transpose({0.0f, 0.0f, 0.0f});

	EXPECT_EQ(target1 * tran1, Vec4f(2.0f, 3.0f, 4.0f, 1.0f));
	EXPECT_EQ(target2 * tran1, Vec4f(1.0f, 0.0f, 4.0f, 1.0f));

	EXPECT_EQ(target2 * tran2, target2);
}

TEST(Matrix4Test, Rotation) {
	Vec4f v1(1.0f, 0.0f, 0.0f, 1.0f);

	EXPECT_EQ(v1 * Mat4f::RotationX(Degf(90.f)), Vec4f(1.f, 0.f, 0.f, 1.f));
	EXPECT_EQ(v1 * Mat4f::RotationY(Degf(90.f)), Vec4f(0.0f, 0.0f, -1.0f, 1.0f));
	EXPECT_EQ(v1 * Mat4f::RotationZ(Degf(90.f)), Vec4f(0.0f, 1.0f, 0.0f, 1.0f));

	const float sqrt2 = std::sqrt(2.0f) / 2;
	Vec4f rr = v1 * Mat4f::RotationZ(Degf(45.0f));
	EXPECT_EQ(rr, Vec4f(sqrt2, sqrt2, 0.f, 1.f));

    Mat4f matrix({ 0.35612202f, -0.80181062f, 0.47987163f, 0.0f},
                   { 0.47987163f,  0.59757626f,  0.6423596f, 0.0f},
                   {-0.80181062f,  0.00151846f, 0.59757626f, 0.0f},
                   {        0.0f,         0.0f,        0.0f, 1.0f});
    EXPECT_EQ(Mat4f::Rotation(Vec3f(-1.0f, 2.0f, 2.0f).Normalize(), Degf(-74.0f)), matrix);
}

TEST(Matrix4Test, Perspective) {
	Vec4f v1(1.f, 1.f, -20.f, 1.f);

    Mat4f expected({-4.0f,      0.0f,         0.0f,  0.0f},
                     {0.0f, -7.111111f,         0.0f,  0.0f},
                     {0.0f,      0.0f,  -1.9411764f, -1.0f},
                     {0.0f,      0.0f, -94.1176452f,  0.0f});
    Mat4f actual = Mat4f::Perspective({16.0f, 9.0f}, -32.0f, -100.0f);
	EXPECT_EQ(actual, expected);

	Mat4f m2 = Mat4f::Perspective(Vec2f(10.f, 10.f), -5.f, -100.f);
	Mat4f m3 = Mat4f::Perspective(Radf(M_PI / 2.f), 1.f, -5.f, -100.f);
	EXPECT_EQ(m2, m3);

	Vec4f v2(0.f, 0.f, -5.f, 1.f);
	Vec4f v2m2 = v2 * m2;
	EXPECT_EQ(v2m2, Vec4f(0.f, 0.f, -5.f, 5.f));

	Vec4f v3(0.f, 0.f, -100.f, 1.f);
	Vec4f v3m2 = v3 * m2;
	EXPECT_EQ(v3m2, Vec4f(0.f, 0.f, 100.f, 100.f));
}

TEST(Matrix4Test, Orthographic) {
	Vec4f v1(1.f, 1.f, -20.f, 1.f);

	Mat4f m1 = Mat4f::Orthographic(Vec2f(10.f, 10.f), 0.f, -100.f);
	EXPECT_EQ(v1 * m1, Vec4f(0.2f, 0.2f, 0.6f, 1.f));

    Mat4f expected({0.4f, 0.0f,   0.0f, 0.0f},
                     {0.0f, 0.5f,   0.0f, 0.0f},
                     {0.0f, 0.0f, 0.25f, 0.0f},
                     {0.0f, 0.0f, 1.25f, 1.0f});
    Mat4f actual = Mat4f::Orthographic({5.0f, 4.0f}, -1.0f, -9.0f);
    EXPECT_EQ(actual, expected);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
