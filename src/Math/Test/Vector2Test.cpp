#include "gtest\gtest.h"
#include "Vector2.h"
#include "Tools.h"

using namespace Tiny::Math;

using Vec2 = Vector2<float>;


TEST(Vector2Test, constructors) {
	Vec2 a;
	Vec2 b(0.0f, 0.0f);
	//Vec2 l(0.0f, 0.0f);
	//static_assert(b == c);
	//const int p = 1;
	//typename std::enable_if<std::is_const<decltype(b)>::value, int>::type int_type = 5;

	EXPECT_EQ(a, b);

	Vec2 c({ 3.0f, -5.0f });
	Vec2 d(3.0f, -5.0f);
	EXPECT_EQ(c, d);

	Vec2 e(d);
	EXPECT_EQ(e, d);

	Vec2 f = d;
	EXPECT_EQ(f, e);
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
	EXPECT_TRUE(equals(M_PI / 2.0f, (float)inner_angle(v1, v2)));

	Vec2 v3(-0.5f, (float)std::sqrt(3) / 2.0f);
	EXPECT_TRUE(equals((float)((M_PI * 2.0f) / 3.0f), (float)inner_angle(v1, v3)));

	Vec2 v4(0.0f, -1.0f);
	EXPECT_TRUE(equals(-M_PI / 2.0f, (float)angle(v1, v4)));

	Vec2 v5(std::sqrt(2.0f) / 2.0f, -std::sqrt(2.0f) / 2.0f);

	EXPECT_TRUE(equals(-M_PI * 3.0f/ 4.0f, (float)angle(v2, v5)));
}

TEST(Vector2Test, perpendicular) {
	Vec2 v1(1.0f, 0.0f);
	EXPECT_EQ(v1.Perpendicular(), Vec2(0.0f, -1.0f));
	EXPECT_TRUE(equals(0.0f, v1.Perpendicular() * v1));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
