#include "gtest/gtest.h"
#include "Vector3.h"

using namespace Tiny::Math;

using Vec3 = Vector3<float>;
using Vec2 = Vector2<float>;

TEST(VectorTest, DefaultConstructor) {
	Vec3 a;
	EXPECT_EQ(a[0], 0.f);
	EXPECT_EQ(a[1], 0.f);
	EXPECT_EQ(a[2], 0.f);
}

TEST(VectorTest, UniformConstructor) {
	Vec3 a(3.3f);

	EXPECT_EQ(a[0], 3.3f);
	EXPECT_EQ(a[1], 3.3f);
	EXPECT_EQ(a[2], 3.3f);
}

TEST(VectorTest, ConstructConvertion) {
	Vec3 a = { 1.f, 2.f, 3.f };
	EXPECT_EQ(a[0], 1.f);
	EXPECT_EQ(a[1], 2.f);
	EXPECT_EQ(a[2], 3.f);

	Vec3 b(1.f, 2.f, 3.f);
	EXPECT_EQ(a, b);

	Vec2 v2(2.2f, 2.2f);
	Vec3 c(v2, 1.f);
	EXPECT_EQ(c, Vec3(2.2f, 2.2f, 1.f));
}

TEST(VectorTest, CopyConstructor) {
	Vec3 a = { 321.f, 8932.f, 223.f };
	Vec3 b(a);

	EXPECT_EQ(a, b);

	Vec3 c = a;
	EXPECT_EQ(a, c);
	EXPECT_EQ(b, c);
}

TEST(Vector3Test, CrossProduct) {
	const float x1(321.432f), y1(343.132f), z1(98033.321f);
	const float x2(89.2f), y2(323.1f), z2(994.0f);
	Vec3 a(x1, y1, z1);
	Vec3 b(x2, y2, z2);
	EXPECT_EQ(Cross(a, b), Vec3(y1*z2 - z1*y2, z1*x2 - x1*z2, x1*y2 - y1*x2));
}

TEST(Vector3Test, interfaces) {
	Vec3 a(5.5f, -100.0f, 20.5f);
	EXPECT_EQ(a.X(), a.R());
	EXPECT_EQ(a.Y(), a.G());
	EXPECT_EQ(a.Z(), a.B());

	a.X() = 20.3f;
	a.Y() = 32.5f;
	a.Z() = 323.2f;

	EXPECT_EQ(a, Vec3(20.3f, 32.5f, 323.2f));

	EXPECT_EQ(Vec3::XAxis(20.0f), Vec3(20.0f, 0.0f, 0.0f));
	EXPECT_EQ(Vec3::YAxis(20.0f), Vec3(0.0f, 20.0f, 0.0f));
	EXPECT_EQ(Vec3::ZAxis(20.0f), Vec3(0.0f, 0.0f, 20.0f));

	Vector2<float>& xy = a.XY();
	xy.X() = 1.0f;
	xy.Y() = 1.0f;
	EXPECT_EQ(a.X(), 1.0f);
	EXPECT_EQ(a.Y(), 1.0f);

	const Vec3 con_a(5.5f, 6.6f, 1.0f);
	Vector2<float> con_xy = con_a.XY();
	EXPECT_EQ(con_xy.X(), 5.5f);
	EXPECT_EQ(con_xy.Y(), 6.6f);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
