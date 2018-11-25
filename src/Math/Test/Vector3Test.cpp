#include "gtest/gtest.h"
#include "Vector3.h"

using namespace Tiny::Math;

using Vec3 = Vector3<float>;

TEST(Vector3Test, constructors) {
	Vec3 a;
	Vec3 b( 0.0f, 0.0f, 0.0f );
	EXPECT_EQ(a, b);

	Vec3 c(1.0f, -1.0f, 2.0f);
	Vec3 d( 1.0f, -1.0f, 2.0f );
	EXPECT_EQ(c, d);

	Vec3 e(5.5f, -11.0f, 100.0f);
	Vec3 f(e);
	EXPECT_EQ(e, f);

	c = f;
	EXPECT_EQ(c, e);
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
