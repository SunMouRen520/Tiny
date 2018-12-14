#ifndef TINY_MATH_TAGS_H
#define TINY_MATH_TAGS_H

namespace Tiny { namespace Math {
	/*
		@brief	Create zero clear vector/matrix
	*/
	struct ZeroInitT {};
	static ZeroInitT ZeroInit;

	/*
		@brief	Create identity matrix/quaternion
	*/
	struct IdentityInitT {};
	static IdentityInitT IdentityInit;
} }

#endif // !TINY_MATH_TAGS_H
