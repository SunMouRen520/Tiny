#include "gtest/gtest.h"
#include "Vector4.h"

using namespace Tiny::Math;
using Vec4f = Vector4<float>;
using Vec3f = Vector3<float>;
using Vec2f = Vector2<float>;

TEST(VectorTest, DefaultConstructor) {
	Vec4f a;
	EXPECT_EQ(a[0], 0.f);
	EXPECT_EQ(a[1], 0.f);
	EXPECT_EQ(a[2], 0.f);
	EXPECT_EQ(a[3], 0.f);
}

TEST(VectorTest, UniformConstructor) {
	Vec4f a(3.3f);

	EXPECT_EQ(a[0], 3.3f);
	EXPECT_EQ(a[1], 3.3f);
	EXPECT_EQ(a[2], 3.3f);
	EXPECT_EQ(a[3], 3.3f);
}

TEST(VectorTest, ConstructConvertion) {
	Vec4f a = { 1.f, 2.f, 3.f, 4.f};
	EXPECT_EQ(a[0], 1.f);
	EXPECT_EQ(a[1], 2.f);
	EXPECT_EQ(a[2], 3.f);
	EXPECT_EQ(a[3], 4.f);

	Vec4f b(1.f, 2.f, 3.f, 4.f);
	EXPECT_EQ(a, b);

	Vec2f v2(2.2f, 2.2f);

	Vec4f c(v2, 3.f, 4.f);
	EXPECT_EQ(c, Vec4f(2.2f, 2.2f, 3.f, 4.f));

	Vec3f v3(3.f, 3.f, 3.f);
	Vec4f d(v3, 1.f);
	EXPECT_EQ(d, Vec4f(3.f, 3.f, 3.f, 1.f));
}

TEST(VectorTest, CopyConstructor) {
	Vec4f a = { 321.f, 8932.f, 223.f, 323.0f};
	Vec4f b(a);

	EXPECT_EQ(a, b);

	Vec4f c = a;
	EXPECT_EQ(a, c);
	EXPECT_EQ(b, c);
}


TEST(Vector4Test, Interface) {
	Vec4f a(5.5f, -100.0f, 20.5f, 11.1f);
	EXPECT_EQ(a.X(), a.R());
	EXPECT_EQ(a.Y(), a.G());
	EXPECT_EQ(a.Z(), a.B());
	EXPECT_EQ(a.W(), a.A());

	a.X() = 20.3f;
	a.Y() = 32.5f;
	a.Z() = 323.2f;
	a.W() = 32.2f;

	EXPECT_EQ(a, Vec4f(20.3f, 32.5f, 323.2f, 32.2f));

	Vector3<float>& xyz = a.XYZ();
	xyz.X() = 1.0f;
	xyz.Y() = 2.0f;
	xyz.Z() = 3.0f;
	EXPECT_EQ(a.X(), 1.0f);
	EXPECT_EQ(a.Y(), 2.0f);
	EXPECT_EQ(a.Z(), 3.0f);

	const Vec4f con_a(5.5f, 6.6f, 1.0f, 8.0f);
	Vector3<float> con_xyz = con_a.XYZ();
	EXPECT_EQ(con_xyz.X(), 5.5f);
	EXPECT_EQ(con_xyz.Y(), 6.6f);
	EXPECT_EQ(con_xyz.Z(), 1.0f);
}



int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
