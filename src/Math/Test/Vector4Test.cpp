#include "gtest\gtest.h"
#include "Vector4.h"

using namespace Tiny::Math;
using Vec4f = Vector4<float>;

TEST(Vector4Test, Constructor) {
	Vec4f v;
	Vec4f zero(0.0f, 0.0f, 0.0f, 0.0f);
	EXPECT_EQ(v, zero);

	Vec4f one(1.0f, 1.0f, 1.0f, 1.0f);
	Vec4f copy(one);
	EXPECT_EQ(copy, one);
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