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

#ifndef _ELA_EXPR_MUL_H
#define _ELA_EXPR_MUL_H

namespace ela { namespace expression {
	template <typename Left, typename Right>
	struct traits<multiply<Left, Right>>
	{
		typedef typename traits<Left>::type type;
		static constexpr size_t rows = traits<Left>::rows;
		static constexpr size_t columns = traits<Right>::columns;
		static constexpr bool concrete = false;
	};

	/* Multiplication expression.
	 */
	template <typename Left, typename Right>
	class multiply : public binary<multiply<Left, Right>, Left, Right>
	{
		static_assert(traits<Left>::columns == traits<Right>::rows,
			"rows and columns don't match");

	public:
		/* Create a new multiplication expression.
		 */
		multiply (Left const& left, Right const& right) noexcept
			: binary<multiply<Left, Right>, Left, Right>(left, right)
		{ }

		/* Access the multiplied scalar at the given index.
		 */
		inline
		typename traits<Left>::type
		operator () (size_t row, size_t column) const noexcept
		{
			ELA_ASSUME(row < traits<Left>::rows && column < traits<Right>::columns);

			typename traits<Left>::type scalar = 0;

			for (size_t i = 0; i < traits<Left>::columns; i++) {
				scalar += this->_left(row, i) * this->_right(i, column);
			}

			return scalar;
		}
	};
} }

#endif
