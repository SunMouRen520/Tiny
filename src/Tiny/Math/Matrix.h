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

#ifndef TINY_MATH_MATRIX_H
#define TINY_MATH_MATRIX_H

#include "Tiny/Math/RectangularMatrix.h"
#include "Tiny/Math/Tools.h"
#include "Tiny/Math/Tags.h"

namespace Tiny { namespace Math {

	template<std::size_t, typename> class Matrix;
	namespace Implementation {
		template<std::size_t size, typename T> struct Determinant{
			T operator()(const Matrix<size, T>& m){
				T out(0);
				for (std::size_t col = 0; col != size; col++) {
					out += ((col & 1) ? -1 : 1) * m[0][col] * m.ij(0, col).Determinant();
				}

				return out;
			}
		};

		template<typename T> struct Determinant<2, T> {
			T operator()(const Matrix<2, T>& m){
				return m[0][0] * m[1][1] - m[0][1] * m[1][0];
			}
		};

		template<typename T> struct Determinant<1, T>{
			T operator()(const Matrix<1, T>& m) {
				return m[0][0];
			}
		};


		template<std::size_t size, std::size_t otherSize, typename T, std::size_t ...cols> Vector<size, T> CopyOrIdentity(const RectangularMatrix<otherSize, otherSize, T>& other, std::size_t row, Implementation::Sequence<cols...>) {
			return{ ((row < otherSize && cols < otherSize )? other[row][cols] : (row == cols ? T{1} : T{0}))... };
		}

		template<std::size_t otherSize, std::size_t size, typename T> Vector<size, T> CopyOrIdentityColumn(const RectangularMatrix<otherSize, otherSize, T>& other, std::size_t row) {
			return CopyOrIdentity<size, otherSize ,T>(other, row, GenerateSeq<size>::Type());
		}
	}

	/*
		@brief Square Matrix base class.
	*/
	template<std::size_t size, typename T> class Matrix : public RectangularMatrix<size, size, T> {
	public:
		enum : std::size_t {
			Size = size
		};

		/*
			@breif	Default constructor, identity.
		*/
		/*explicit*/ Matrix(IdentityInitT = IdentityInit) noexcept
			:RectangularMatrix<size, size, T>{Implementation::GenerateSeq<size>::Type(), Vector<size, T>(1)} {}

		/*
			@brief	Construct zero clear matrix
		*/
		explicit Matrix(ZeroInitT) noexcept
			:RectangularMatrix<size, size, T>(ZeroInit){}

		/*
			@brief	Set all value in matrix to be uniform
		*/
		explicit Matrix(const T& uniform)
			:RectangularMatrix<size, size, T>{Implementation::GenerateSeq<size>::Type(), uniform} {}


		/*
			@brief	Construct from diagonal vector
		*/
		explicit Matrix(const Vector<size, T>& diagonal)
			:RectangularMatrix<size, size, T>(Implementation::GenerateSeq<size>::Type(), diagonal){}

		/*
			@brief	Generate matrix from Rectangularmatrix.
		*/
		Matrix(const RectangularMatrix<size, size, T>& other)
			:RectangularMatrix<size, size, T>(other) {}

		/*
			@brief	Constructor from other dimensation
		*/
		template<std::size_t otherSize> explicit Matrix(const RectangularMatrix<otherSize, otherSize, T>& other)
			:Matrix(Implementation::GenerateSeq<size>::Type(), other) {}

		template<typename ...U, typename std::enable_if<sizeof...(U)+1 == size, T>::type* = nullptr> Matrix(const Vector<size, T>& first, const U&... next) : RectangularMatrix<size, size, T>(first, next...){}

		/*default copy constructor*/
		Matrix(const Matrix<size, T>& other) = default;

		/*
			@brief Get the determinant
		*/
		T Determinant() const;

		/*
			@brief Is Orthogonal matrix?
			Matrix A is orthogonal if (A t) = (A ^ -1).
		*/
		bool Orthogonal() const;

		/*
			@brief Invertible
		*/
		bool Invertible() const;

		/*
			@brief Get sub-matrix without row i and col j.
		*/
		Matrix<size - 1, T> ij(std::size_t i, std::size_t j) const;

		/*
			@brief	Get vector along diagonal 
		*/
		Vector<size, T> Diagonal() const;

		Matrix<size, T> Inverse() const;

		template<typename U> typename std::enable_if<U::Size == size, Matrix<size, T>&>::type operator*=(const U& other);

	protected:
		template<std::size_t ...RowSeq> Vector<size, T> DiagonalIner(Implementation::Sequence<RowSeq...>) const
		{
			return  Vector<size, T>(((*this)[RowSeq][RowSeq])...);
		}

	private:
		template<std::size_t otherSize, std::size_t ...RowSeq> Matrix(Implementation::Sequence<RowSeq...>, const RectangularMatrix<otherSize, otherSize, T>& other)
			:RectangularMatrix<size, size, T>{( Implementation::CopyOrIdentityColumn<otherSize, size, T>(other, RowSeq))...} {}
	};

	template<std::size_t size, typename T> bool Matrix<size, T>::Invertible() const {
		return Determinant() != 0;
	}

	template<std::size_t size, typename T> bool Matrix<size, T>::Orthogonal() const {
		//Is normalized?
		for (std::size_t row = 0; row != size; row++)
			if (!(*this)[row].IsNormalized())
				return false;
		//Is orghogonal?
		for (std::size_t i = 0; i != size; i++)
			for (std::size_t j = i + 1; j != size; j++)
				if (!equals((*this)[i] * (*this)[j], T(0)))
					return false;

		return true;
	}

	template<std::size_t size, typename T> T Matrix<size, T>::Determinant() const {
		return Implementation::Determinant<size, T>()(*this);
		//if (size == 1)
		//	return (*this)[0][0];
		//if (size == 2)
		//	return (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];

		//T out(0);
		//for (std::size_t col = 0; col != size; col++) {
		//	out += ((col & 1) ? -1 : 1) * (*this)[0][col] * (*this).ij(0, col).Determinant();
		//}
		//return out;
	}

	template<std::size_t size, typename T> Matrix<size - 1, T> Matrix<size, T>::ij(std::size_t i, std::size_t j) const {
		Matrix<size - 1, T> out;
		for (std::size_t row = 0; row != (size - 1) ; row++)
			for (std::size_t col = 0; col != (size - 1) ; col++)
				out[row][col] = (*this)[row  + (row >= i)][col + (col >= j)];

		return out;
	}

	template<std::size_t size, typename T>  Vector<size, T> Matrix<size, T>::Diagonal() const {
		//return Vector<size, T>((*this)[0][0], (*this)[1][1], (*this)[2][2]);
		return DiagonalIner(Implementation::GenerateSeq<size>::Type());
	}

	//The cofactor Cij = (-1) ^ (i + j)detA(ij)
	template<std::size_t size, typename T>  Matrix<size, T> Matrix<size, T>::Inverse() const {
		T k = T(1) / Determinant();
		Matrix<size, T> result;
		for (int i = 0; i != size; i++) {
			for (int j = 0; j != size; j++) {
				result[i][j] = (((i + j) & 1) ? -1 : 1) * ij(j, i).Determinant() * k;
			}
		}
		return result;
	}

	template<std::size_t size, typename T>
	template<typename U> typename std::enable_if<U::Size == size, Matrix<size, T>&>::type Matrix<size, T>::operator*=(const U& other) {
		*this = (*this) * other;
		return *this;
	}
} }

#endif
