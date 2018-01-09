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

#ifndef ELA_STORAGE_POINTER_H
#define ELA_STORAGE_POINTER_H

namespace ela { namespace storage {
	template <typename Order, typename Type, size_t Rows, size_t Columns>
	class impl<specifier<pointer, Order>, Type, Rows, Columns>
	{
	public:
		impl (Type* ptr) noexcept
			: _ptr(ptr)
		{ }

		/* Access a scalar at the given row and column.
		 */
		inline
		Type const&
		operator () (size_t row, size_t column) const noexcept
		{
			ELA_ASSUME(row < Rows && column < Columns);

			return _ptr[Order::template index<Rows, Columns>(row, column)];
		}

		/* Access a scalar at the given row and column.
		 */
		inline
		Type&
		operator () (size_t row, size_t column) noexcept
		{
			ELA_ASSUME(row < Rows && column < Columns);

			return _ptr[Order::template index<Rows, Columns>(row, column)];
		}

		/* Return the wrapped raw pointer.
		 */
		inline
		operator Type* (void) noexcept
		{
			return _ptr;
		}

		/* Return the wrapped constant raw pointer.
		 */
		inline
		operator Type const* (void) const noexcept
		{
			return _ptr;
		}

	private:
		Type* _ptr;
	};

} }

#endif
