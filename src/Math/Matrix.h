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

			The cofactor Cij = (-1)^(i + j)detA(ij)

			I.		We can choose any row or column instead of first row to calculate detA in Formular 1
			II.		For triangular matrix, detA is the product of the entris along the main diagonal.
			III.	Row operations:
						1.	If a multiply of one row in A is added to another row to produce B, then detB = detA.
						2.	If two rows in A is interchanged to produce B, then detB = -detA.
						3.	If one row is multiplied by k to produce B, then detB = k(detA).
			IV.		Matrix A is invertible only detA = 0.
			V.		det(A t) = detA
			VI.		det(AB) = detA * detB
			VII.	Cramer's Rule:
						For any invertible n x n matrix A and any b in R(n), let A(i)(b) be the matrix obtained 
						from A by replacing column i by the vector b.
						Then the unique solution x of Ax = b has entries given by:
								x(i) = detA(i)(b) / detA
			
			VIII.	Inverse Formula:
					
					A ^ -1 = (C t) / detA. where C is the cofactor matrix of A.

			IX.		If A is in R2, |detA| is the area of parallelogram.
					If A is in R3, |detA| is the volume of parallelepiped.

			X.		R2 -> R2 be the linear transform determinated by 2x2 matrix A. If S is a parallelogram in R2, then 
						{area of T(S)} = detA x {area of S}

		3.	Eigenvectors and Eigenvalues;
			I.		An Eigenvector of n x n matrix A is a nonzero vector x such that Ax = Lx for some scalar L.  (L is short for greek's lambda).
					A scalar L is called an eigenvalue of A if there is a nontrivial solution x of Ax = Lx; such an x is called an eigenvector corresponding to L.
			II.		For a diagonal matrix, the eigenvalues are entris on the main diagonal.
			III.	If v1, ... vn are eigenvectors that correspond to distinct eigenvalues L1, ... Ln, then the set{v1, ... vn} are linear indenpendent.
			IV.		Square Matrix A ia invertible if and only if:
					1.	The number 0 is not eigenvalues.
					2.	detA is not 0.

			V.		too be continue...
			
*/

namespace Tiny { namespace Math {
	/*
		@brief Square Matrix base class.
	*/
	template<std::size_t size, typename T> class Matrix : public RectangularMatrix<size, size, T> {

	public:
		enum : std::size_t {
			Size = size
		};

		/*don't need any constructors here*/

		/*
			@brief construct from other size matrix.
			if other_size >= size, then the result matrix filled with data from the first size rows and colmuns in other.
			else, the result matrix is expanded to identity(ones on diagonal, zeros elsewhere).

			TODO:
				this function is intended to be undefined. 
				in magnum, this is implement by this:
					Matrix<size, T>{typename Implementation::GenerateSequence<size>::Type(), other}
				how to understand?
		*/
		template<std::size_t other_size, typename std::enable_if<false, T>::type * = nullptr> explicit Matrix(const Matrix<other_size, T>& other) {
			
		}

		/*
			@brief Get the determinant
		*/
		T Determinant() const;

		/*
			@brief Is Orthogonal matrix?
			Matrix A is orthogonal if (A t) = (A ^ -1).
		*/
		bool Orthogonal() const;
	};

	template<std::size_t size, typename T> T Matrix<size, T>::Determinant() const {
		
	}

	template<typename T> using Matrix33 = Matrix<3, T>;
	template<typename T> using Matrix44 = Matrix<4, T>;
} }

#endif