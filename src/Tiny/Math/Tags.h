#pragma once

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
