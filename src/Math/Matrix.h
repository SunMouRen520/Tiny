#ifndef TINY_MATH_MATRIX_H
#define TINY_MATH_MATRIX_H

#include "RectangularMatrix.h"
/*
	Square Matrix Properties:
		1.	Triangular matrix: 
			i.	Lower triangular: A square matrix which all values above the main diagonal are 0.
			ii.	Upper triangular: opposite to the lower triangular matrix .

		2. Determinant: 
			detA = a(11)detA(11) - a(12)detA(12) ... +(-1)^(1 + n)a(1n)detA(1n).  --Formular 1
			a(1n) is the nth value in first row and A(1n) is the A sub-matrix without row 1 and column n.

			I.		We can choose any row or column instead of first row to calculate detA in Formular 1
			II.		For triangular matrix, detA is the product of the entris along the main diagonal.
			III.	Row operations:
						1.	If a multiply of one row in A is added to another row to produce B, then detB = detA.
						2.	If two rows in A is interchanged to produce B, then detB = -detA.
						3.	If one row is multiplied by k to produce B, then detB = k(detA).
			IV.		Matrix A is invertible only detA = 0.
			V.		det(AT) = detA
			VI.		det(AB) = det(A) * det(B)
			VII.	
			
*/

namespace Tiny { namespace Math {
	/*
		@brief Square Matrix base class.
	*/
	template<std::size_t size, typename T> class Matrix : public RectangularMatrix<size, size, T> {
		template<std::size_t, typename> friend class Matrix;

	public:
		/*	
			@brief Is Symmetric?
		*/
		bool Symmetric() const;

		/*
			@brief Get the determinant
		*/
		T Determinant() const;
	};
} }

#endif