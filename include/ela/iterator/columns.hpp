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

#ifndef ELA_ITERATOR_COLUMNS_H
#define ELA_ITERATOR_COLUMNS_H

namespace ela { namespace iterator {
	template <typename Expr>
	class columns<Expr, false>
	{
	public:
		typedef std::ptrdiff_t difference_type;
		typedef vector<Expr, for_column<Expr>, false> value_type;
		typedef vector<Expr, for_column<Expr>, false> pointer;
		typedef vector<Expr, for_column<Expr>, false> reference;
		typedef std::random_access_iterator_tag iterator_category;

	protected:
		columns (Expr const& expr, size_t index) noexcept
			: _expr(expr), _index(index)
		{ }

	public:
		static inline
		columns<Expr, false>
		begin (Expr const& expr) noexcept
		{
			return columns(expr, 0);
		}

		static inline
		columns<Expr, false>
		end (Expr const& expr) noexcept
		{
			return columns(expr, expression::traits<Expr>::columns);
		}

	public:
		inline
		value_type
		operator * () noexcept
		{
			return _expr.column(_index);
		}

		inline
		bool
		operator != (columns<Expr, false> const& other)
		{
			return _index != other._index;
		}

	protected:
		Expr const& _expr;
		size_t      _index;
	};

	template <typename Expr>
	class columns<Expr, true>
	{
	public:
		typedef std::ptrdiff_t difference_type;
		typedef vector<Expr, for_column<Expr>, true> value_type;
		typedef vector<Expr, for_column<Expr>, true> pointer;
		typedef vector<Expr, for_column<Expr>, true> reference;
		typedef std::random_access_iterator_tag iterator_category;

	protected:
		columns (Expr& expr, size_t index) noexcept
			: _expr(expr), _index(index)
		{ }

	public:
		static inline
		columns<Expr, true>
		begin (Expr& expr) noexcept
		{
			return columns(expr, 0);
		}

		static inline
		columns<Expr, true>
		end (Expr& expr) noexcept
		{
			return columns(expr, expression::traits<Expr>::columns);
		}

	// Iterator
	public:
		inline
		value_type
		operator * () noexcept
		{
			return _expr.column(_index);
		}

		inline
		columns<Expr, true>&
		operator ++ () noexcept
		{
			_index++;
			return *this;
		}

		inline
		bool
		operator != (columns<Expr, true> const& other) noexcept
		{
			return _index != other._index;
		}

	private:
		Expr&  _expr;
		size_t _index;
	};
} }

#endif
