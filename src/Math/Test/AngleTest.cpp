#include "gtest/gtest.h"
#include "Angle.h"

using namespace Tiny::Math;

using Radf = Rad<float>;
using Degf = Deg<float>;

TEST(AngleTest, defaultConstructor) {
	Radf r;
	EXPECT_EQ((float)r, 0.0f);

	Degf d;
	EXPECT_EQ((float)d, 0.0f);
}

TEST(AngleTest, constructorFromValue) {
	Radf r1(1.0f);
	EXPECT_EQ((float)r1, 1.0f);

	Radf r2(-21.321f);
	EXPECT_EQ((float)r2, -21.321f);

	Degf d1(1.0f);
	EXPECT_EQ((float)d1, 1.0f);

	Degf d2(-21.321f);
	EXPECT_EQ((float)d2, -21.321f);
}

TEST(AngleTest, copyConstructor) {
	Radf r_to(3213.321f);
	Radf r_from = r_to;
	EXPECT_EQ((float)r_from, 3213.321f);

	Degf d_to(3213.321f);
	Degf d_from = d_to;
	EXPECT_EQ((float)r_from, 3213.321f);
}

TEST(AngleTest, moveConstructor) {

}

TEST(AngleTest, typeConvertion) {
	Radf r1(2 * M_PI);
	Degf d1(r1);
	EXPECT_TRUE(equals(float(d1), 360.0f));

	Degf d2(360.0f);
	Radf r2(d2);
	EXPECT_TRUE(equals(float(r2), float(2.0f * M_PI)));
}

TEST(AngleTest, rad_operators) {
	float d1 = 4329.321f;
	float d2 = 213.32f;
	float d3 = 4116.001f;

	Radf r1(d1);
	Radf r2(d2);
	Radf r3(d3);
	Radf r4(d1);

	EXPECT_FALSE(r1 == r2);
	EXPECT_TRUE(r1 == r4);
	EXPECT_TRUE(r1 != r2);

	EXPECT_TRUE(r1 > r2);
	EXPECT_TRUE(r1 >= r4);
	EXPECT_FALSE(r2 > r3);
	EXPECT_FALSE(r2 >= r3);

	EXPECT_TRUE(r2 < r1);
	EXPECT_TRUE(r2 <= r1);
	EXPECT_FALSE(r3 <= r2);
	EXPECT_FALSE(r3 < r2);

	EXPECT_TRUE(equals(float(r1 + r2), d1 + d2));
	EXPECT_TRUE(equals(float(r1 - r2), d3));
	EXPECT_TRUE(equals(float(r1 * r2), float(d1 * d2)));
	EXPECT_TRUE(equals(float(r1 / r2), float(d1 / d2)));
}

TEST(AngleTest, deg_operators) {
	float d1 = 4329.321f;
	float d2 = 213.32f;
	float d3 = 4116.001f;

	Degf r1(d1);
	Degf r2(d2);
	Degf r3(d3);
	Degf r4(d1);

	EXPECT_FALSE(r1 == r2);
	EXPECT_TRUE(r1 == r4);
	EXPECT_TRUE(r1 != r2);

	EXPECT_TRUE(r1 > r2);
	EXPECT_TRUE(r1 >= r4);
	EXPECT_FALSE(r2 > r3);
	EXPECT_FALSE(r2 >= r3);

	EXPECT_TRUE(r2 < r1);
	EXPECT_TRUE(r2 <= r1);
	EXPECT_FALSE(r3 <= r2);
	EXPECT_FALSE(r3 < r2);

	EXPECT_TRUE(equals(float(r1 + r2), d1 + d2));
	EXPECT_TRUE(equals(float(r1 - r2), d3));
	EXPECT_TRUE(equals(float(r1 * r2), d1 * d2));
	EXPECT_TRUE(equals(float(r1 / r2), d1 / d2));
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
