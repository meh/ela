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

namespace ela { namespace order {
	/* Row major order.
	 */
	struct row_major
	{
		template <size_t Rows, size_t Columns>
		static inline
		size_t
		index (size_t row, size_t column) noexcept
		{
			return row * Columns + column;
		}

		template <size_t Rows, size_t Columns>
		static inline
		std::pair<size_t, size_t>
		index (size_t index) noexcept
		{
			return std::make_pair(index / Columns, index % Columns);
		}
	};

	/* Column major order.
	 */
	struct column_major
	{
		template <size_t Rows, size_t Columns>
		static inline
		size_t
		index (size_t row, size_t column) noexcept
		{
			return column * Rows + row;
		}

		template <size_t Rows, size_t Columns>
		static inline
		std::pair<size_t, size_t>
		index (size_t index) noexcept
		{
			return std::make_pair(index % Rows, index / Rows);
		}
	};
} }
