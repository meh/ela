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

#ifndef ELA_ITERATOR_H
#define ELA_ITERATOR_H

namespace ela { namespace iterator {
	template <typename Expr, typename Iterator, typename ConstIterator>
	class wrapper
	{
		public:
			typedef Iterator iterator;
			typedef ConstIterator const_iterator;

		public:
			wrapper (Expr& expr)
				: _expr(expr)
			{ }

			const_iterator
			begin () const noexcept
			{
				return ConstIterator::begin(_expr);
			}

			iterator
			begin () noexcept
			{
				return Iterator::begin(_expr);
			}

			const_iterator
			end () const noexcept
			{
				return ConstIterator::end(_expr);
			}

			iterator
			end () noexcept
			{
				return Iterator::end(_expr);
			}

		private:
			Expr& _expr;
	};

	template <typename Expr, typename Iterator>
	class wrapper<Expr, Iterator, Iterator>
	{
		public:
			typedef Iterator iterator;
			typedef Iterator const_iterator;

		public:
			wrapper (Expr const& expr)
				: _expr(expr)
			{ }

			const_iterator
			begin () const noexcept
			{
				return Iterator::begin(_expr);
			}

			const_iterator
			begin () noexcept
			{
				return Iterator::begin(_expr);
			}

			const_iterator
			end () const noexcept
			{
				return Iterator::end(_expr);
			}

			const_iterator
			end () noexcept
			{
				return Iterator::end(_expr);
			}

		private:
			Expr const& _expr;
	};
} }

#include "iterator/elements.hpp"
#include "iterator/rows.hpp"
#include "iterator/columns.hpp"

#endif
