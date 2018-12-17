#include "gtest\gtest.h"
#include "Tiny/Math/Quaternion.h"
#include "Tiny/Math/Matrix4.h"
#include "Tiny/Math/MathForward.h"
#include "Tiny/Math/Tools.h"

using namespace Tiny::Math;


TEST(QuaternionTest, DefaultConstruct) {
	Quaternionf q;
	EXPECT_EQ(q.Scalar(), 1.f);
	EXPECT_EQ(q.Vector(), Vector3f(ZeroInit));
}

TEST(QuaternionTest, ZeroConstruct) {
	Quaternionf q(ZeroInit);
	EXPECT_EQ(q.Scalar(), 0.f);
	EXPECT_EQ(q.Vector(), Vector3f(ZeroInit));
}

TEST(QuaternionTest, ConstructRotate) {
	float theta = M_PI / 3.f;
	Vector3f axis(3.4f, 989.f, 0.59f);
	Quaternionf r = Quaternionf::Rotate(M_PI / 3, axis);
	EXPECT_EQ(std::cos(theta / 2), r.Scalar());
	EXPECT_EQ(axis.Normalize() * std::sin(theta / 2), r.Vector());
}

TEST(QuaternionTest, ConstructMatrix) {
	const Degf degree(-74.f);
	const Vector3f axis = Vector3f(-1.f, 2.f, 2.f).Normalize();
	Matrix4f rotateMat = Matrix4f::Rotation(axis, degree);

	Quaternionf rotateQuat = Quaternionf::FromMatrix(rotateMat.ij(3, 3));
	EXPECT_EQ(rotateQuat, Quaternionf::Rotate(degree, axis));
}

TEST(QuaternionTest, ConstructConvertion) {
	const float scalar = 0.53f;
	const Vector3f vector(321.f, 857.f, 321321.f);
	Quaternionf q(scalar, vector);
	EXPECT_EQ(q.Scalar(), scalar);
	EXPECT_EQ(q.Vector(), vector);
}

TEST(QuaternionTest, ToMatrix) {
	const Degf degree(-74.f);
	const Vector3f axis = Vector3f(-1.f, 2.f, 2.f).Normalize();
	Quaternionf rotate = Quaternionf::Rotate(degree, axis);
	EXPECT_EQ(rotate.ToMatrix(), Matrix4f::Rotation(axis, degree).ij(3, 3));
}

TEST(QuaternionTest, Angle) {
	const Radf rad(M_PI / 20);
	const Vector3f axis = Vector3f(-1.f, 2.f, 2.f).Normalize();
	Quaternionf rotate = Quaternionf::Rotate(rad, axis);
	EXPECT_NEAR(rotate.Angle(), M_PI / 20.f, 0.001);
}

TEST(QuaternionTest, Norm) {
	const float scalar = 51.23f;
	const Vector3f vector(0.2f, 100.f, 53.f);
	Quaternionf q(scalar, vector);
	EXPECT_TRUE(equals(q.Norm(), std::sqrt(std::pow(scalar, 2) + vector.Dot())));

	EXPECT_EQ(Quaternionf().Norm(), 1.f);

	EXPECT_TRUE(Quaternionf().IsNormalized());
	EXPECT_TRUE(equals(q.Normalize().Norm(), 1.f));
}

TEST(QuaternionTest, Conjugate) {
	const float scalar = 51.23f;
	const Vector3f vector(0.2f, 100.f, 53.f);
	Quaternionf q1(scalar, vector);
	EXPECT_EQ(q1.Conjugate(), Quaternionf(scalar, -vector));
}

TEST(QuaternionTest, Inverse) {
	const float scalar = 51.23f;
	const Vector3f vector(0.2f, 100.f, 53.f);
	Quaternionf q1(scalar, vector);

	EXPECT_EQ(q1.Inverse(), Quaternionf(scalar, -vector) / std::sqrt(scalar * scalar + vector.Dot()));

	const Degf degree(-74.f);
	const Vector3f axis = Vector3f(-1.f, 2.f, 2.f).Normalize();
	Quaternionf r1 = Quaternionf::Rotate(degree, axis);
	Quaternionf r1_inverse = Quaternionf::Rotate(-degree, axis);
	EXPECT_EQ(r1.Inverse(), r1_inverse);
}


TEST(QuaternionTest, Operators) {
	const float scalar = 51.23f;
	const Vector3f vector(0.2f, 100.f, 53.f);
	Quaternionf q1(scalar, vector);

	const float w2 = 0.3f;
	const Vector3f v2(1.2f, 10.f, 3.f);
	Quaternionf q2(w2, v2);

	EXPECT_EQ(-q1, Quaternionf(-scalar, -vector));

	const float demonitor = 100.f;
	EXPECT_EQ(q1 / demonitor, Quaternionf(scalar/ demonitor, vector / demonitor));

	EXPECT_EQ(q1 - q1, Quaternionf(ZeroInit));
	EXPECT_EQ(q1 - q2, Quaternionf(scalar - w2, vector - v2));

	EXPECT_EQ(q1 + (-q1), Quaternionf(ZeroInit));
	EXPECT_EQ(q1 + q2, Quaternionf(scalar + w2, vector + v2));

	EXPECT_EQ(q1 * 3.f, Quaternionf(scalar * 3.f, vector * 3.f));
}

TEST(QuaternionTest, CorssProduct) {
	const float w1= 51.23f;
	const Vector3f v1(0.2f, 100.f, 53.f);
	Quaternionf q1(w1, v1);
	
	const float w2 = 0.3f;
	const Vector3f v2(1.2f, 10.f, 3.f);
	Quaternionf q2(w2, v2);


	Quaternionf expect(w1 * w2 - v1 * v2, w1 * v2 + w2 * v1 + Cross(v2, v1));
	EXPECT_EQ(q1 * q2, expect);
}

TEST(QuaternionTest, Transform) {
	const Radf rad(M_PI * 2.f / 3.f);
	const Vector3f axis1(0.5f, 0.5f, 0.5f);
	Quaternionf q1 = Quaternionf::Rotate(rad, axis1);

	Vector3f xNormal(1.f, 0.f, 0.f);
	//q1.Tranform(xNormal) supposed to get normal vector along positive y direction.
	EXPECT_EQ(q1.Tranform(xNormal), Vector3f(0.f, 1.f, 0.f));


	const Degf degree2(-74.f);
	const Vector3f axis2 = Vector3f(-1.f, 2.f, 2.f).Normalize();
	Matrix4f m1 = Matrix4f::Rotation(axis2, degree2);
	Quaternionf q2 = Quaternionf::Rotate(degree2, axis2);
	
	Vector3f v2(0.3f, 100.f, -20.f);
	EXPECT_EQ(v2 * m1, q2.Tranform(v2));

	const Radf rad3(M_PI / 4);
	const Vector3f axis3 = Vector3f(3.f, 4.f, 5.f).Normalize();
	Matrix4f m2 = Matrix4f::Rotation(axis3, rad3);
	Quaternionf q3 = Quaternionf::Rotate(rad3, axis3);
	EXPECT_EQ(v2 * m1 * m2, (q2 * q3).Tranform(v2));
}

TEST(QuaternionTest, Lerp) {
	const float rad1 = 0.53f;
	const Vector3f v1(321.f, 857.f, 321321.f);
	Quaternionf q1(rad1, v1);

	const float rad2 = 0.3f;
	const Vector3f v2(31.f, 57.f, 1.f);
	Quaternionf q2(rad2, v2);

	const float t = 0.1f;
	Quaternionf lerp_result = Lerp(q1, q2, t);
	EXPECT_EQ(lerp_result, Quaternionf(Lerp(rad1, rad2, t), Lerp(v1, v2, t)).Normalize());
}

TEST(QuaternionTest, Slerp) {
	const Vector3f x(1.f, 0.f, 0.f);
	Quaternionf q1 = Quaternionf::Rotate(M_PI / 2.f, x);
	Quaternionf q2 = Quaternionf::Rotate(0.f, x);

	EXPECT_EQ(Slerp(q1, q2, 0.5f), Quaternionf::Rotate(M_PI / 4.f, x));
	EXPECT_EQ(Slerp(q1, q2, 0.3f), Quaternionf::Rotate(M_PI * 7.f / 20.f, x));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
