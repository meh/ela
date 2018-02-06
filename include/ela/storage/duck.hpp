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

#ifndef ELA_STORAGE_DUCK_H
#define ELA_STORAGE_DUCK_H

namespace ela { namespace storage {
	template <typename Order, typename Duck, typename Type, size_t Size>
	class impl<specifier<duck<Duck>, Order>, Type, Size>
	{
	public:
		impl (Duck duck) noexcept
			: _duck(duck)
		{ }

		/* Access a scalar at the given row and column.
		 */
		inline
		Type const&
		operator [] (size_t index) const noexcept
		{
			ELA_ASSUME(index < Size);

			return _duck[index];
		}

		/* Access a scalar at the given row and column.
		 */
		inline
		Type&
		operator [] (size_t index) noexcept
		{
			ELA_ASSUME(index < Size);

			return _duck[index];
		}

	private:
		Duck _duck;
	};
} }

#endif
