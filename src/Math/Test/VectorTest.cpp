#include "gtest/gtest.h"
#include "Vector.h"
#include "Tools.h"

using namespace Tiny::Math;

typedef Vector<2, float> Vec2;
typedef Vector<3, float> Vec3;
typedef Vector<4, float> Vec4;

TEST(VectorTest, constructor) {
	Vec4 e;
	Vec4 empty(0.0f, 0.0f, 0.0f, 0.0f);
	EXPECT_EQ(e, empty);

	Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
	Vec4 b = { 1.0f, 2.0f, 3.0f, 4.0f };
	EXPECT_EQ(a, b);

	float c[4] = { 1.0f, 2.0f, 3.0f, 4.0f };
	const Vec4& d = Vec4::From(c);
	EXPECT_EQ(a, d);
}

TEST(VectorTest, Operators) {
	Vec4 a(1.0f, 1.0f, 2.0f, 1.0f);
	Vec4 b(20.1f, 2.1f, 0.21f, 1.0f);

	EXPECT_EQ(a + b, Vec4(21.1f, 3.1f, 2.21f, 2.0f));
	EXPECT_EQ(b - a, Vec4(19.1f, 1.1f, -1.79f, 0.0f));
	EXPECT_EQ(a * b, 20.1f + 2.1f + 0.42f + 1.0f);
	EXPECT_EQ(b * 3.0f, Vec4(60.3f, 6.3f, 0.63f, 3.0f));
	EXPECT_EQ(b / 10.0f, Vec4(2.01f, 0.21f, 0.021f, 0.1f));
	
	a += b;
	EXPECT_EQ(a, Vec4(21.1f, 3.1f, 2.21f, 2.0f));

	Vec4 c(5.2f, 0.3f, -1.1f, -10.0f);
	Vec4 a_backup = a;
	a -= c;
	EXPECT_EQ(a , Vec4(15.9f, 2.8f, 3.31f, 12.0f));
	a += c;
	EXPECT_TRUE(a == a_backup);

	EXPECT_EQ(c[0], 5.2f);
	EXPECT_EQ(c[1], 0.3f);
	EXPECT_EQ(c[2], -1.1f);
	EXPECT_EQ(c[3], -10.0f);

	c[0] = 10.0f;
	c[3] = 100.0f;
	EXPECT_EQ(c[0], 10.0f);

	Vec4 smaller(1.0f, -1.0f, -2.0f, 3.0f);
	Vec4 bigger(10.1f, -0.2f, 0.0f, 4.0f);

	EXPECT_TRUE(bigger > smaller);
}

TEST(VectorTest, Interfaces) {
	Vec4 zero;
	EXPECT_TRUE(zero.Zero());

	Vec4 norm(1.0f, 0.0f, 0.0f, 0.0f);
	EXPECT_TRUE(norm.IsNormalized());
	norm = { 0.0f, 1.0f, 0.0f, 0.0f };
	EXPECT_TRUE(norm.IsNormalized());
	norm = { 0.0f, 0.0f, 1.0f, 0.0f };
	EXPECT_TRUE(norm.IsNormalized());
	norm = { 0.0f, 0.0f, 0.0f, 1.0f };
	EXPECT_TRUE(norm.IsNormalized());

	Vec4 before_normalize(30.5f, -4.3f, 5.5f, -3.1f);
	norm = before_normalize.Normalize();
	EXPECT_TRUE(equals(norm.Magnitude(), 1.0f));
	EXPECT_TRUE(norm.IsNormalized());

	EXPECT_TRUE(equals(before_normalize.Dot(), (float)(30.5 * 30.5 + -4.3f * -4.3f + 5.5f * 5.5f + -3.1f * -3.1f)));
	EXPECT_EQ(before_normalize.Sum(), 30.5f - 4.3f + 5.5f - 3.1f);

	//Vec4 v(1.0f, 2.0f, 3.0f, 4.0f, 5.0f); check variadic template constructor
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}