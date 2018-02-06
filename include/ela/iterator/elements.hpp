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

#ifndef ELA_ITERATOR_ELEMENTS_H
#define ELA_ITERATOR_ELEMENTS_H

namespace ela { namespace iterator {
	template <typename Expr, typename Order>
	class elements<Expr, Order, marker::concrete<false>>
	{
	public:
		typedef std::ptrdiff_t difference_type;
		typedef typename expression::traits<Expr>::type value_type;
		typedef value_type const* pointer;
		typedef value_type const& reference;
		typedef std::random_access_iterator_tag iterator_category;

	protected:
		elements (Expr const& expr, size_t index) noexcept
			: _expr(expr), _index(index)
		{ }

	public:
		static inline
		elements<Expr, Order, marker::concrete<false>>
		begin (Expr const& expr) noexcept
		{
			return elements(expr, 0);
		}

		static inline
		elements<Expr, Order, marker::concrete<false>>
		end (Expr const& expr) noexcept
		{
			return elements(expr, expression::traits<Expr>::rows * expression::traits<Expr>::columns);
		}

	public:
		inline
		value_type
		operator * () const
		{
			size_t row, column;
			std::tie(row, column) = Order::template index<
				expression::traits<Expr>::rows, expression::traits<Expr>::columns>(_index);

			return _expr(row, column);
		}

		inline
		value_type
		operator -> () const
		{
			size_t row, column;
			std::tie(row, column) = Order::template index<
				expression::traits<Expr>::rows, expression::traits<Expr>::columns>(_index);

			return _expr(row, column);
		}

		inline
		elements<Expr, Order, marker::concrete<false>>&
		operator ++ ()
		{
			_index++;
			return *this;
		}

		inline
		elements<Expr, Order, marker::concrete<false>>
		operator ++ (int)
		{
			elements<Expr, Order, marker::concrete<false>> tmp(*this);
			_index++;
			return tmp;
		}

		template <typename Concrete>
		inline
		bool
		operator == (elements<Expr, Order, Concrete> const& other) const
		{
			return _index == other._index;
		}

		template <typename Concrete>
		inline
		bool
		operator != (elements<Expr, Order, Concrete> const& other) const
		{
			return _index != other._index;
		}

	protected:
		Expr const& _expr;
		size_t      _index;
	};

	template <typename Expr, typename Order>
	class elements<Expr, Order, marker::concrete<true>>
	{
	public:
		typedef std::ptrdiff_t difference_type;
		typedef typename expression::traits<Expr>::type value_type;
		typedef value_type* pointer;
		typedef value_type& reference;
		typedef std::random_access_iterator_tag iterator_category;

	protected:
		elements (Expr& expr, size_t index) noexcept
			: _expr(expr), _index(index)
		{ }

	public:
		static inline
		elements<Expr, Order, marker::concrete<true>>
		begin (Expr& expr) noexcept
		{
			return elements(expr, 0);
		}

		static inline
		elements<Expr, Order, marker::concrete<true>>
		end (Expr& expr) noexcept
		{
			return elements(expr, expression::traits<Expr>::rows * expression::traits<Expr>::columns);
		}

	// Iterator
	public:
		inline
		reference
		operator * () const
		{
			size_t row, column;
			std::tie(row, column) = Order::template index<
				expression::traits<Expr>::rows, expression::traits<Expr>::columns>(_index);

			return _expr(row, column);
		}

		inline
		pointer
		operator -> () const
		{
			size_t row, column;
			std::tie(row, column) = Order::template index<
				expression::traits<Expr>::rows, expression::traits<Expr>::columns>(_index);

			return &_expr(row, column);
		}

		inline
		elements<Expr, Order, marker::concrete<true>>&
		operator ++ ()
		{
			_index++;
			return *this;
		}

		inline
		elements<Expr, Order, marker::concrete<true>>
		operator ++ (int)
		{
			elements<Expr, Order, marker::concrete<true>> tmp(*this);
			_index++;
			return tmp;
		}

		template <typename Concrete>
		inline
		bool
		operator == (elements<Expr, Order, Concrete> const& other) const
		{
			return _index == other._index;
		}

		template <typename Concrete>
		inline
		bool
		operator != (elements<Expr, Order, Concrete> const& other) const
		{
			return _index != other._index;
		}

	private:
		Expr&  _expr;
		size_t _index;
	};
} }

#endif
