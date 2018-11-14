#include "gtest\gtest.h"
#include "Vector2.h"
#include "Tools.h"

using namespace Tiny::Math;

typedef Vector2<float> Vec2;


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
	EXPECT_EQ(a.x(), 3.0f);
	EXPECT_EQ(a.y(), -4.5f);
	//a.x = 5; //should be wrong
	
	Vec2 b(1.0f, 2.0f);
	b.x() = 3.3f;
	b.y() = -1.5f;
	EXPECT_EQ(b, Vec2(3.3f, -1.5f));

	EXPECT_EQ(Vec2::xAxis(3.3f), Vec2(3.3f, 0.0f));
	EXPECT_EQ(Vec2::yAxis(-1.5f), Vec2(0.0f, -1.5f));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
