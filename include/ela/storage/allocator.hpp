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

#ifndef ELA_STORAGE_ALLOCATOR_H
#define ELA_STORAGE_ALLOCATOR_H

namespace ela { namespace storage {
	template <typename Order, template <typename> class Allocator, typename Type, size_t Rows, size_t Columns>
	class impl<specifier<allocator<Allocator>, Order>, Type, Rows, Columns>
	{
	public:
		typedef Allocator<Type> allocator_type;

	public:
		impl (Allocator<Type> const& alloc = Allocator<Type>()) noexcept
			: _alloc(alloc)
		{
			_valid  = true;
			_buffer = _alloc.allocate(Rows * Columns);
		}

		impl (Type value, Allocator<Type> const& alloc = Allocator<Type>()) noexcept
			: impl(alloc)
		{
			std::fill_n(_buffer, Rows * Columns, value);
		}

		impl (impl<specifier<allocator<Allocator>, Order>, Type, Rows, Columns> const& from) noexcept
			: impl(from._alloc)
		{
			std::copy_n(from._buffer, Rows * Columns, _buffer);
		}

		impl (impl<specifier<allocator<Allocator>, Order>, Type, Rows, Columns>&& from) noexcept
			: _alloc(from._alloc), _buffer(from._buffer)
		{
			from._valid = false;
		}

		~impl () noexcept
		{
			if (_valid) {
				_alloc.deallocate(_buffer, Rows * Columns);
			}
		}

		/* Access a scalar at the given row and column.
		 */
		inline
		Type const&
		operator () (size_t row, size_t column) const noexcept
		{
			ELA_ASSUME(row < Rows && column < Columns);

			return _buffer[Order::template index<Rows, Columns>(row, column)];
		}

		/* Access a scalar at the given row and column.
		 */
		inline
		Type&
		operator () (size_t row, size_t column) noexcept
		{
			ELA_ASSUME(row < Rows && column < Columns);

			return _buffer[Order::template index<Rows, Columns>(row, column)];
		}

	private:
		Allocator<Type>                   _alloc;
		typename Allocator<Type>::pointer _buffer;
		bool                              _valid;
	};
} }

#endif
