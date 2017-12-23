// Copyright (c) 2017 1aim GmbH
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is furnished to do
// so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef _ELA_MATRIX_H
#define _ELA_MATRIX_H

namespace ela {
	namespace expression {
		template <typename Type, size_t Rows, size_t Columns>
		struct traits<matrix<Type, Rows, Columns>>
		{
			typedef Type type;
			static constexpr size_t rows = Rows;
			static constexpr size_t columns = Columns;
			static constexpr bool concrete = true;
		};
	}

	/* A matrix.
	 *
	 * The internal buffer is a contiguous column-major array.
	 */
	template <typename Type, size_t Rows, size_t Columns>
	class matrix: public expression::base<matrix<Type, Rows, Columns>>
	{
	public:
		using expression::base<matrix<Type, Rows, Columns>>::operator =;

	public:
		/* Create an empty matrix.
		 */
		matrix () noexcept
		{ }

		matrix (Type value) noexcept
		{
			std::fill_n(_buffer, Rows * Columns, value);
		}

		template <typename Input, typename T = Type, size_t R = Rows, size_t C = Columns>
		matrix (Input const& expr, typename std::enable_if<
			R == expression::traits<Input>::rows &&
			C == expression::traits<Input>::columns &&
			std::is_same<T, typename expression::traits<Input>::type>::value>::type* = 0) noexcept
		{
			expression::base<matrix<Type, Rows, Columns>>::operator=(expr);
		}

		matrix (std::initializer_list<std::initializer_list<Type>> rows) noexcept
		{
			expression::base<matrix<Type, Rows, Columns>>::operator=(rows);
		}

		template <size_t R = Rows, size_t C = Columns>
		matrix (std::initializer_list<Type> elements, typename std::enable_if<R == 1 || C == 1>::type* = 0) noexcept
		{
			expression::base<matrix<Type, Rows, Columns>>::operator=(elements);
		}

		/* Create an identity matrix with the given value.
		 */
		template <size_t R = Rows, size_t C = Columns>
		static inline
		typename std::enable_if<R == C, matrix<Type, Rows, Columns>>::type
		identity () noexcept
		{
			matrix<Type, Rows, Columns> result;

			for (size_t i = 0; i < Rows; i++) {
				result(i, i) = 1;
			}

			return result;
		}

		/* Create a scaling matrix with the given values.
		 */
		template <size_t R = Rows, size_t C = Columns>
		static inline
		typename std::enable_if<R == C && (R == 3 || R == 4), matrix<Type, Rows, Columns>>::type
		scaling (Type x, Type y, Type z) noexcept
		{
			auto result = identity();

			result(0, 0) = x;
			result(1, 1) = y;
			result(2, 2) = z;

			return result;
		}

		/* Create an identity matrix with the given value.
		 */
		template <size_t R = Rows, size_t C = Columns>
		static inline
		typename std::enable_if<R == C && (R == 3 || R == 4), matrix<Type, Rows, Columns>>::type
		scaling (Type x) noexcept
		{
			auto result = identity();

			result(0, 0) = x;
			result(1, 1) = x;
			result(2, 2) = x;

			return result;
		}

		/* Access a scalar at the given row and column.
		 */
		inline
		Type const&
		operator () (size_t row, size_t column) const noexcept
		{
			ELA_ASSUME(row < Rows && column < Columns);

			return _buffer[row * Columns + column];
		}

		/* Access a scalar at the given row and column.
		 */
		inline
		Type&
		operator () (size_t row, size_t column) noexcept
		{
			ELA_ASSUME(row < Rows && column < Columns);

			return _buffer[row * Columns + column];
		}

		/* Return the wrapped raw pointer (row major).
		 */
		inline
		Type* operator & (void) noexcept
		{
			return _buffer;
		}

		/* Return the wrapped constant raw pointer (row major).
		 */
		inline
		Type const* operator & (void) const noexcept
		{
			return _buffer;
		}

	private:
		Type _buffer[Rows * Columns] = { 0 };
	};
}

#endif
