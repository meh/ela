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

#ifndef ELA_ITERATOR_ROWS_H
#define ELA_ITERATOR_ROWS_H

namespace ela { namespace iterator {
	template <typename Expr>
	class rows<Expr, marker::concrete<false>>
	{
	public:
		typedef std::ptrdiff_t difference_type;
		typedef vector<Expr, for_row<Expr>, marker::concrete<false>> value_type;
		typedef vector<Expr, for_row<Expr>, marker::concrete<false>> pointer;
		typedef vector<Expr, for_row<Expr>, marker::concrete<false>> reference;
		typedef std::random_access_iterator_tag iterator_category;

	protected:
		rows (Expr const& expr, size_t index) noexcept
			: _expr(expr), _index(index)
		{ }

	public:
		static inline
		rows<Expr, marker::concrete<false>>
		begin (Expr const& expr) noexcept
		{
			return rows(expr, 0);
		}

		static inline
		rows<Expr, marker::concrete<false>>
		end (Expr const& expr) noexcept
		{
			return rows(expr, expression::traits<Expr>::rows);
		}

	public:
		inline
		value_type
		operator * () noexcept
		{
			return _expr.row(_index);
		}

		inline
		bool
		operator != (rows<Expr, marker::concrete<false>> const& other)
		{
			return _index != other._index;
		}

	protected:
		Expr const& _expr;
		size_t      _index;
	};

	template <typename Expr>
	class rows<Expr, marker::concrete<true>>
	{
	public:
		typedef std::ptrdiff_t difference_type;
		typedef vector<Expr, for_row<Expr>, marker::concrete<true>> value_type;
		typedef vector<Expr, for_row<Expr>, marker::concrete<true>> pointer;
		typedef vector<Expr, for_row<Expr>, marker::concrete<true>> reference;
		typedef std::random_access_iterator_tag iterator_category;

	protected:
		rows (Expr& expr, size_t index) noexcept
			: _expr(expr), _index(index)
		{ }

	public:
		static inline
		rows<Expr, marker::concrete<true>>
		begin (Expr& expr) noexcept
		{
			return rows(expr, 0);
		}

		static inline
		rows<Expr, marker::concrete<true>>
		end (Expr& expr) noexcept
		{
			return rows(expr, expression::traits<Expr>::rows);
		}

	// Iterator
	public:
		inline
		value_type
		operator * () noexcept
		{
			return _expr.row(_index);
		}

		inline
		rows<Expr, marker::concrete<true>>&
		operator ++ () noexcept
		{
			_index++;
			return *this;
		}

		inline
		bool
		operator != (rows<Expr, marker::concrete<true>> const& other) noexcept
		{
			return _index != other._index;
		}

	private:
		Expr&  _expr;
		size_t _index;
	};
} }

#endif
