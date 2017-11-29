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

#ifndef _ELA_EXPRESSION_ADD_H
#define _ELA_EXPRESSION_ADD_H

namespace ela { namespace expression {
	template <typename Left, typename Right>
	struct traits<add<Left, Right>>
	{
		typedef typename traits<Left>::type type;
		static constexpr size_t rows = traits<Left>::rows;
		static constexpr size_t columns = traits<Left>::columns;
	};

	/* Addition expression.
	 */
	template <typename Left, typename Right>
	class add : public binary<add<Left, Right>, Left, Right>
	{
		static_assert(
			traits<Left>::rows == traits<Right>::rows &&
			traits<Left>::columns == traits<Right>::columns,
			"rows and columns don't match");

	public:
		/* Create a new addition expression.
		 */
		add (Left const& left, Right const& right) noexcept
			: binary<add<Left, Right>, Left, Right>(left, right)
		{ }

		/* Access the added scalar at the given index.
		 */
		inline
		typename traits<Left>::type
		operator () (size_t row, size_t column) const noexcept
		{
			ELA_ASSUME(row < traits<Left>::rows && column < traits<Left>::columns);

			return this->_left(row, column) + this->_right(row, column);
		}
	};
} }

#endif
