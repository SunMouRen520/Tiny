/*
	Information stores in row-major format, which is opposite to OpenGL for practicing

		| 1 1 1 | 
	M = | 2 2 2 | 
		| 3 3 3 |

	For row-major format, get the first vector is just &M[0].
	for column-major format, get the first vector is (M[0][0], M[1][0], M[2][0]).
*/
#ifndef Tiny_MATH_RECTANGULAR_MATRIX_H
#define Tiny_MATH_RECTANGULAR_MATRIX_H

#include <cstddef>

namespace Tiny { namespace Math {

	template<std::size_t rows, std::size_t cols, typename T> class RectangularMatrix{
		static_assert(rows != 0 && cols != 0, "RectangularMatrix cannot have 0 elements!");

		template<std::size_t, std::size_t, typename> friend class RectangularMatrix;

	public:
		typedef T Type;

		/*
			@brief RectangularMatrix From data
			@attention  User this carefully. 
		*/
		static RectangularMatrix<rows, cols, T>& From(T *data) {
			return *(reinterpret_cast<RectangularMatrix<rows, cols, T>*(data));
		}

		static const RectangularMatrix<rows, cols, T>& From(const T* data) {
			return *(reinterpret_cast<const RectangularMatrix<rows, cols, T> *)(data);
		}


		/*constructor*/
		explicit RectangularMatrix() noexcept {}
		/*copy constructor*/

		/*destructor*/

		/*
			Do Transpose
		*/
		void Transpose();

		/*
			Check matrix Invertible
		*/
		bool Invertible();

	private:
		Vector<cols, T> _data[rows];

	};
}}

#endif
