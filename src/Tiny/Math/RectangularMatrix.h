/*
	Information stores in row-major format, which is opposite to OpenGL convention.

		| 1 1 1 |
	M = | 2 2 2 |
		| 3 3 3 |

	For row-major format, get the first vector is just &M[0].
	for column-major format, get the first vector is (M[0][0], M[1][0], M[2][0]).

	Rectangular Matrix properties:
		1.	Matrix multiplication:
			a.	matrix mul matrix:
				A(m x n) * B(n x p) = C(m x p) can be viewed in two forms:

				I.	A = { row1, row2 ... rowm }, B = { col1, col2 ... colp }
					One specific val C (i x j) = A(rowi) * B(colj)  //vector inner product

					1.	Based on upper view, One col C(j) = A * B(colj).

				II.	A = { col1, col2 ... coln }, B = {row1, row2 ... rown }
					The hole result matrix C(m x p) = A(col1) x B(row1) + A(col2) x B(row2) + .... + A(coln) x B(rown) //vector outer product

			b.	matrix mul vector:
				same as matrix mul matrix, the matrix can be viewed in two form. As in Tiny, we treat all vectors in row-major.
					V_in(n) * M(n * p)  = V_out(p)

				I.	M = { row1, row2 ... rown}.
					V_out(p) = V_in(1) * row1 + V_in(2) * row2 + ... + V_in(n) * rown.
					In this view, we treat the result V_out as a linear combination of rows in M with vector V_in

				II.	M = {col1, col2 ... colp}
					V_out(p) = { V_in(n) * col1, V_in(n) * col2, ... V_in(n) * colp}
					In this view, we treat each element i in V_out as a inner product result of V_in with coli.

			c.	matrix mul scalar; not too much to say.

		2.	Row reduction:
			a.	Standard row operations:
				I.		Multiply a row by nonzero scalar
				II.		Adding a multiple of one row to another
				III.	Swapping one row from another

			b.	Row-equivalent: If we can get from matrix A to matrix B by row operations, then A and B are Row-equivalent

			c.	Row-Echelon Form. If a matrix:
				I:	any rows made complete zeors are at bottom of matrix
				II:	the first nonzero entries of the various rows form a staircase pattern: the first nonzero entry
					of the k + 1st row is to the right of the first nonzero entry of the k th row.
					eg. | 1 2 3 4 |
						| 0 1 2 0 |
						| 0 0 0 5 |
						| 0 0 0 0 |

			d.	Pivot and Pivot Colum:
				I.	If a matrix is in row-echelon form, then the first non-zero entry of each row is pivot.
				II. the columns in which the pivot appears called pivot column.

			e.	Reduced Row-Echelon Form(shortcut: rref):
				I. require 3 conditions:
					1. in row-echelon form
					2. all pivots equal to 1
					3. all values in pivot columns except pivot is 0.

				II. algorithm to rref: Gaussian elimination

		3.	Rank: The rank of a matrix is the number of pivots in its reduced row-echelon form. notation is R.
			a.	For non-square matrix A(m x n). The rank R cannot be great than min(m, n).
				I.	If m < n, there are at least (n - m) columns without pivots
				II.	If m > n, there are at lear (m - b) zero rows

			b.	For quare matrix A(m x m).
				I.		If R equal m, then the rref of A is I. we say the matrix is "invertible".
				II.		If R less than m, then we say the matrix is "singular".
				III.	The "determinant" tells the difference.

			c. The rank R tells the dimenssion of the column space.

		4.	Transpose: Matrix A(m x n) transpose is AT(n x m), which A(ij) = AT(ji).

		5.	Null Space, Column Space,


	TODO:
	1. Factorization algorithms.
		a. LU factorization: A = LU.
*/
#ifndef Tiny_MATH_RECTANGULAR_MATRIX_H
#define Tiny_MATH_RECTANGULAR_MATRIX_H

#include <cstddef>
#include <type_traits>
#include "Tiny/Math/Vector.h"

#ifdef TINY_TEST
#include <iostream>
#endif

namespace Tiny { namespace Math {


	/*
		@brief Rectangular Matrix.
		Provide the common operators such as index, add, sub, mul, div, compare.
	*/
	template<std::size_t rows, std::size_t cols, typename T> class RectangularMatrix{
		static_assert(rows != 0 && cols != 0, "RectangularMatrix cannot have 0 elements!");

		template<std::size_t, std::size_t, typename> friend class RectangularMatrix;

	public:
		typedef T Type;

		enum : std::size_t {
			Rows = rows,
			Cols = cols,

			DiagonalSize = rows > cols ? rows : cols
		};

		/*
			@brief RectangularMatrix From data
			@attention  Use this carefully, as we could create multiply RectangularMatrix reference but share the same data.
		*/
		static RectangularMatrix<rows, cols, T>& From(T *data) {
			return *(reinterpret_cast<RectangularMatrix<rows, cols, T>*> (data));
		}

		static const RectangularMatrix<rows, cols, T>& From(const T* data) {
			return *(reinterpret_cast<const RectangularMatrix<rows, cols, T>*> (data));
		}

		/*
			@brief	Default constructor, all values zero clear.
		*/
		RectangularMatrix(ZeroInitT = ZeroInit)
			:RectangularMatrix(Implementation::GenerateSeq<rows>::Type(), 0){}

#ifdef TINY_TEST
		/*
			@brief	Convert from c array. Test avaliable only.
			@caution	Only avaliable when build for testing, maybe should be removed in future.
		*/
		RectangularMatrix(const T *source) {
			for (std::size_t i = 0; i < rows; i++)
				for (std::size_t j = 0; j < cols; j++)
					_data[i][j] = source[(i * cols) + j];
		}

#endif // TINY_TEST

		/*
			@brief construct from Vector<cols, T>[rows]
		*/
		template<typename ...U, typename std::enable_if<sizeof...(U) + 1 == rows, T>::type* = nullptr> RectangularMatrix( const Vector<cols, T>& first, const U&... next):_data{first, next...}{ }

		/*copy constructor*/
		RectangularMatrix(const RectangularMatrix& other) = default;
		RectangularMatrix& operator=(const RectangularMatrix &other) = default;
		/*destructor*/
		~RectangularMatrix() = default;

		/*
			@brief Get Vector<rows, T> from colmun n
		*/
		Vector<rows, T> Column(std::size_t col) const;

		/*
			@brief Transpose
		*/
		RectangularMatrix<cols, rows, T> Transpose() const;

		/*
			@brief Get the raw data
		*/
		T* Get() { return _data[0].Get(); }
		/*const overload*/
		const T* Get() const { return _data[0].Get(); }

		/*
			@brief index operatiosn
		*/
		Vector<cols, T>& operator[](std::size_t row_index) { return _data[row_index]; }
		/*const overload*/
		const Vector<cols, T>& operator[](std::size_t row_index) const{ return _data[row_index]; }

		/*
			@brief add operator
		*/
		RectangularMatrix<rows, cols, T> operator+(const RectangularMatrix<rows, cols, T>& other) const { return RectangularMatrix<rows, cols, T>(*this) += other; }
		RectangularMatrix<rows, cols, T>& operator+=(const RectangularMatrix<rows, cols, T>& other);

		/*
			@brief sub operator
		*/
		RectangularMatrix<rows, cols, T> operator-(const RectangularMatrix<rows, cols, T>& other) const { return RectangularMatrix<rows, cols, T>(*this) -= other; }
		RectangularMatrix<rows, cols, T>& operator-=(const RectangularMatrix<rows, cols, T>& other);

		/*
			@brief div operator
		*/
		typename std::enable_if< std::is_floating_point<T>::value, RectangularMatrix<rows, cols, T>>::type operator / (T divisor) { return RectangularMatrix<rows, cols, T>(*this) /= divisor; }
		typename std::enable_if< std::is_floating_point<T>::value, RectangularMatrix<rows, cols, T>&>::type operator /= (T divisor);


		/*
			@brief Multiply with number
		*/
		RectangularMatrix<rows, cols, T> operator * (T coe) const { return RectangularMatrix<rows, cols, T>(*this) *= coe; }

		/*
			@brief Multiply with number and assign
		*/
		RectangularMatrix<rows, cols, T>& operator *= (T coe);

		/*
			@brief	Multiply with another rectangular matrix.
			@caution	Matrix multiplications are very expensive.
		*/
		//template<typename U> typename std::enable_if<U::Rows == cols, RectangularMatrix<rows, U::Cols, T>>::type operator*=(const U& other);

		/*Multiply with vector is provided as free-standing functions*/
		/*
			@brief Multiply with Matrix
		*/
		template<typename U> typename std::enable_if<U::Rows == cols, RectangularMatrix<rows, U::Cols, T>>::type operator*(const U& other) const;

		/*
			@brief Matrix compare
		*/
		bool operator == (const RectangularMatrix<rows, cols, T>& other) const;
		bool operator != (const RectangularMatrix<rows, cols, T>& other) const;

	protected:
		/*
			@brief	Construct with diagonal value.
		*/
		template<std::size_t ...RowSeq> RectangularMatrix(Implementation::Sequence<RowSeq...>, const Vector<DiagonalSize, T>& diagonal)
			:_data{ GenDiagonalCol(diagonal, RowSeq)...} {}

		Vector<cols, T> GenDiagonalCol(const Vector<DiagonalSize, T>& diagonal, int row) {
			return DiagonalCol(Implementation::GenerateSeq<cols>::Type(), diagonal, row);
		}

		template<std::size_t ...ColumnSeq> Vector<cols, T> DiagonalCol(Implementation::Sequence<ColumnSeq...>, const Vector<DiagonalSize, T>& diagonal, int row) {
			return { (ColumnSeq == row ? diagonal[row] : T{})... };
		}

		/*
			@brief	Set all _data with same value
		*/
		template<std::size_t ...RowSeq> RectangularMatrix(Implementation::Sequence<RowSeq...>, T val)
			:_data{ (Vector<cols, T>(Implementation::Repeat(val, RowSeq)))... } {
		}

	private:
		Vector<cols, T> _data[rows];
	};

	template<std::size_t rows, std::size_t cols, typename T> RectangularMatrix<cols, rows, T> RectangularMatrix<rows, cols, T>::Transpose() const{
		RectangularMatrix<cols, rows, T> out;
		for (std::size_t c = 0; c != cols; c++)
			for (std::size_t r = 0; r != rows; r++)
				out[c][r] = _data[r][c];
		return out;
	}

	template<std::size_t rows, std::size_t cols, typename T> Vector<rows, T> RectangularMatrix<rows, cols, T>::Column(std::size_t col) const{
		Vector<rows, T> out;
		for (std::size_t r = 0; r != rows ; r++) {
			out[r] = (*this)[r][col];
		}
		return out;
	}

	template<std::size_t rows, std::size_t cols, typename T> RectangularMatrix<rows, cols, T>& RectangularMatrix<rows, cols, T>::operator *= (T coe) {
		for (auto &row : _data)
			row *= coe;
		return *this;
	}

	template<std::size_t rows, std::size_t cols, typename T> RectangularMatrix<rows, cols, T>& RectangularMatrix<rows, cols, T>::operator += (const RectangularMatrix<rows, cols, T>& other) {
		for (std::size_t r = 0; r != rows; r++)
			_data[r] += other._data[r];
		return *this;
	}

	template<std::size_t rows, std::size_t cols, typename T> RectangularMatrix<rows, cols, T>& RectangularMatrix<rows, cols, T>::operator -= (const RectangularMatrix<rows, cols, T>& other) {
		for (std::size_t r = 0; r != rows; r++)
			_data[r] -= other._data[r];
		return *this;
	}

	template<std::size_t rows, std::size_t cols, typename T>
	typename std::enable_if< std::is_floating_point<T>::value, RectangularMatrix<rows, cols, T>&>::type RectangularMatrix<rows, cols, T>::operator /= (T divisor) {
		for (std::size_t r = 0; r != rows; r++)
			_data[r] /= divisor;
		return *this;
	}

	template<std::size_t rows, std::size_t cols, typename T>
	template<typename U> typename std::enable_if<U::Rows == cols, RectangularMatrix<rows, U::Cols, T>>::type RectangularMatrix<rows, cols, T>::operator *(const U& other) const{
		RectangularMatrix<rows, U::Cols, T> out;
		for (std::size_t i = 0; i < rows; i++) {
			for (std::size_t j = 0; j < U::Cols; j++) {
				out[i][j] = _data[i] * other.Column(j);
			}
		}
		return out;
	}

	template<std::size_t rows, std::size_t cols, typename T> bool RectangularMatrix<rows, cols, T>::operator ==(const RectangularMatrix<rows, cols, T>& other) const{
		for (std::size_t i = 0; i < rows; i++) {
			if (!(_data[i] == other._data[i]))
				return false;
		}
		return true;
	}

	template<std::size_t rows, std::size_t cols, typename T> bool RectangularMatrix<rows, cols, T>::operator !=(const RectangularMatrix<rows, cols, T>& other) const{
		return !(*this == other);
	}

	//template<std::size_t rows, std::size_t cols, typename T>
	//template<typename U> typename std::enable_if<U::Rows == cols, RectangularMatrix<rows, U::Cols, T>>::type RectangularMatrix<rows, cols, T>::operator *=(const U& other) {
	//	return (*this) * other;
	//}

	/*
		@brief Vector multiply Matrix
		Matrix M multiply Vector V: V * M
	*/
	template<std::size_t rows, std::size_t cols, typename T >  Vector<cols, T> operator*(const Vector<rows, T>& v, const RectangularMatrix<rows, cols, T>& m) {
		Vector<cols, T> out;
		for (std::size_t i = 0; i != cols; i++) {
			Vector<rows, T> col = m.Column(i);
			out[i] = col * v;
		}
		return out;
	}


	/*
		TODO: what's the meaning of this operator?
		@brief outer operator.
		@tparam		col		col is the colmun-vector with form (M x 1)
		@tparam		row		row is the row-vector with form (1 X N)
		@return		RectangularMatirx with form (M x N)
	*/

	template<std::size_t M, std:: size_t N, typename T > RectangularMatrix<M, N, T> Outer(const Vector<M, T>& col, const Vector<N, T>& row) {
		RectangularMatrix<M, N, T> out;
		for (std::size_t i = 0; i != M; i++) {
			for (std::size_t j = 0; j != N; j++) {
				out[i][j] = col[i] * row[j];
			}
		}
		return out;
	}



#ifdef TINY_TEST
	template<std::size_t row, std::size_t col, typename T> std::ostream &operator<<(std::ostream& os, const RectangularMatrix<row, col, T>& m) {
		for (int i = 0; i < row; i++) {
			os << "| ";
			for (int j = 0; j < col - 1; j++) {
				os << m[i][j] << ",\t";
			}
			os << m[i][col - 1];
			os << " |" << std::endl;
		}
		return os;
	}
#endif
}}

#endif
