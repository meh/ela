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

#ifndef ELA_EXPRESSION_TRANSPOSE_H
#define ELA_EXPRESSION_TRANSPOSE_H

namespace ela { namespace expression {
	template <typename Input, bool Concrete>
	struct traits<transpose<Input, Concrete>>
	{
		typedef typename traits<Input>::type type;
		static constexpr size_t rows = traits<Input>::columns;
		static constexpr size_t columns = traits<Input>::rows;
		static constexpr bool concrete = Concrete;
	};

	/* Transposition expression, swaps rows with columns.
	 */
	template <typename Input>
	class transpose<Input, false>: public unary<transpose<Input>, Input const&>
	{
	public:
		/* Create a new transposition expression.
		 */
		transpose (Input const& input) noexcept
			: unary<transpose<Input>, Input const&>(input)
		{ }

		/* Access the transposed scalar at the given index.
		 */
		inline
		typename traits<Input>::type
		operator () (size_t row, size_t column) const noexcept
		{
			ELA_ASSUME(row <= traits<Input>::columns && column <= traits<Input>::rows);

			return this->_input(column, row);
		}
	};

	/* Transposition expression, swaps rows with columns.
	 */
	template <typename Input>
	class transpose<Input, true>: public unary<transpose<Input>, Input&>
	{
	public:
		/* Create a new transposition expression.
		 */
		transpose (Input& input) noexcept
			: unary<transpose<Input>, Input&>(input)
		{ }

		/* Access the transposed scalar at the given index.
		 */
		inline
		typename traits<Input>::type const&
		operator () (size_t row, size_t column) const noexcept
		{
			ELA_ASSUME(row <= traits<Input>::columns && column <= traits<Input>::rows);

			return this->_input(column, row);
		}

		/* Access the transposed scalar at the given index.
		 */
		inline
		typename traits<Input>::type&
		operator () (size_t row, size_t column) noexcept
		{
			ELA_ASSUME(row <= traits<Input>::columns && column <= traits<Input>::rows);

			return this->_input(column, row);
		}
	};
} }

#endif
