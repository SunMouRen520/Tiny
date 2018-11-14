#include "gtest\gtest.h"
#include "Vector3.h"

using namespace Tiny::Math;

typedef Vector3<float> Vec3;

TEST(Vector3Test, constructors) {
	Vec3 a;
	Vec3 b({ 0.0f, 0.0f, 0.0f });
	EXPECT_EQ(a, b);

	Vec3 c(1.0f, -1.0f, 2.0f);
	Vec3 d({ 1.0f, -1.0f, 2.0f });
	EXPECT_EQ(c, d);

	Vec3 e(5.5f, -11.0f, 100.0f);
	Vec3 f(e);
	EXPECT_EQ(e, f);

	c = f;
	EXPECT_EQ(c, e);
}

TEST(Vector3Test, operators) {
	
}

TEST(Vector3Test, interfaces) {
	Vec3 a(5.5f, -100.0f, 20.5f);
	EXPECT_EQ(a.x(), a.r());
	EXPECT_EQ(a.y(), a.g());
	EXPECT_EQ(a.z(), a.b());

	a.x() = 20.3f;
	a.y() = 32.5f;
	a.z() = 323.2f;

	EXPECT_EQ(a, Vec3(20.3f, 32.5f, 323.2f));
	
	EXPECT_EQ(Vec3::xAxis(20.0f), Vec3(20.0f, 0.0f, 0.0f));
	EXPECT_EQ(Vec3::yAxis(20.0f), Vec3(0.0f, 20.0f, 0.0f));
	EXPECT_EQ(Vec3::zAxis(20.0f), Vec3(0.0f, 0.0f, 20.0f));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
