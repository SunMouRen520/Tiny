#include "gtest/gtest.h"
#include "Vector2.h"
#include "Tools.h"

using namespace Tiny::Math;

using Vec2 = Vector2<float>;

TEST(Vector2Test, DefaultConstruct) {
	Vec2 a;
	EXPECT_EQ(a[0], 0.f);
	EXPECT_EQ(a[1], 0.f);
}

TEST(Vector2Test, UniformConstruct) {
	Vec2 a(0.f);
	Vec2 b;
	EXPECT_EQ(a, b);

	Vec2 c(3.3f);
	EXPECT_EQ(c[0], 3.3f);
	EXPECT_EQ(c[1], 3.3f);
}

TEST(Vector2Test, ConstructConvertion) {
	Vec2 a = {1.0f, 2.0f};
	EXPECT_EQ(a[0], 1.0f);
	EXPECT_EQ(a[1], 2.0f);

	Vec2 b(1.0f, 2.0f);
	EXPECT_EQ(a, b);

	EXPECT_EQ(b, Vec2({ 1.0f, 2.0f }));
}

TEST(Vector2Test, CopyConstruct) {
	Vec2 a(5321.f, 390.f);
	Vec2 b(a);
	EXPECT_EQ(a, b);

	Vec2 c = b;
	EXPECT_EQ(a, c);
}

TEST(Vector2Test, interfaces) {
	const Vec2 a(3.0f, -4.5f);
	EXPECT_EQ(a.X(), 3.0f);
	EXPECT_EQ(a.Y(), -4.5f);
	//a.x = 5; //should be wrong

	Vec2 b(1.0f, 2.0f);
	b.X() = 3.3f;
	b.Y() = -1.5f;
	EXPECT_EQ(b, Vec2(3.3f, -1.5f));

	EXPECT_EQ(Vec2::XAxis(3.3f), Vec2(3.3f, 0.0f));
	EXPECT_EQ(Vec2::YAxis(-1.5f), Vec2(0.0f, -1.5f));
}

using Radf = Rad<float>;
TEST(Vector2Test, angle) {
	Vec2 v1(1.0f, 0.0f);
	Vec2 v2(0.0f, 1.0f);
	EXPECT_TRUE(equals(float(M_PI / 2.0f), (float)inner_angle(v1, v2)));

	Vec2 v3(-0.5f, (float)std::sqrt(3) / 2.0f);
	EXPECT_TRUE(equals((float)((M_PI * 2.0f) / 3.0f), (float)inner_angle(v1, v3)));

	Vec2 v4(0.0f, -1.0f);
	EXPECT_TRUE(equals(float(-M_PI / 2.0f), (float)angle(v1, v4)));

	Vec2 v5(float(std::sqrt(2.0f) / 2.0f), -std::sqrt(2.0f) / 2.0f);

	EXPECT_TRUE(equals(float(-M_PI * 3.0f/ 4.0f), (float)angle(v2, v5)));
}

TEST(Vector2Test, perpendicular) {
	Vec2 v1(1.0f, 0.0f);
	Vec2 v11 = v1.Perpendicular();
	EXPECT_EQ(v11, Vec2(0.0f, 1.0f));
	EXPECT_TRUE(equals(0.0f, v1.Perpendicular() * v1));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
