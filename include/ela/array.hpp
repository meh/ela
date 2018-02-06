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

#ifndef ELA_ARRAY_H
#define ELA_ARRAY_H

namespace std {
	template <typename Exprt , size_t Rows, size_t Columns, typename Order, bool Concrete>
	struct tuple_size<ela::array<Expr, Order, Concrete>> : std::integral_constant<size_t,
		ela::expression::traits<Expr>::rows * ela::expression::traits<Expr>::columns>
	{ };

	template <size_t Index, typename Expr, typename Order, bool Concrete>
	struct tuple_element<Index, ela::array<Expr, Order, Concrete>>
	{
		using type = typename ela::expression::traits<Expr>::type;
	};
}

namespace ela {
	template <typename Expr, typename Order>
	class array_base
	{
	public:
		typedef ela::iterator::elements<Expr, Order>        iterator;
		typedef ela::iterator::elements<Expr, Order, false> const_iterator;

	public:
		array_base (Expr& expr)
			: _expr(expr)
		{ }

	public:
		const_iterator
		begin () const noexcept
		{
			return const_iterator::begin(_expr);
		}

		iterator
		begin () noexcept
		{
			return iterator::begin(_expr);
		}

		const_iterator
		end () const noexcept
		{
			return const_iterator::end(_expr);
		}

		iterator
		end () noexcept
		{
			return iterator::end(_expr);
		}

	public:
		inline
		size_t
		size () const noexcept
		{
			return expression::traits<Expr>::rows * expression::traits<Expr>::columns;
		}

	protected:
		Expr& _expr;
	};

	template <typename Expr, typename Order>
	class array<Expr, Order, false>
		: array_base<Expr, Order>
	{
	public:
		array (Expr const& expr)
			: array_base<Expr, Order>(const_cast<Expr&>(expr))
		{ }

	public:
		template <size_t Index>
		typename expression::traits<Expr>::type
		get () const noexcept
		{
			return this[Index];
		}

	public:
		inline
		typename expression::traits<Expr>::type
		operator [] (size_t index) noexcept
		{
			size_t row, column;
			std::tie(row, column) = Order::template index<
				expression::traits<Expr>::rows, expression::traits<Expr>::columns>(index);

			return this->_expr(row, column);
		}
	};

	template <typename Expr, typename Order>
	class array<Expr, Order, true>
		: array_base<Expr, Order>
	{
	public:
		array (Expr& expr)
			: array_base<Expr, Order>(expr)
		{ }

	public:
		template <size_t Index>
		typename expression::traits<Expr>::type const&
		get () const noexcept
		{
			return this[Index];
		}

		template <size_t Index>
		typename expression::traits<Expr>::type&
		get () noexcept
		{
			return this[Index];
		}

	public:
		inline
		void
		fill (typename expression::traits<Expr>::type value) noexcept
		{
			for (size_t i = 0; i < this->size(); i++) {
				size_t row, column;
				std::tie(row, column) = Order::template index<
					expression::traits<Expr>::rows, expression::traits<Expr>::columns>(i);

				this->_expr(row, column) = value;
			}
		}

		inline
		typename expression::traits<Expr>::type const&
		operator [] (size_t index) const noexcept
		{
			size_t row, column;
			std::tie(row, column) = Order::template index<
				expression::traits<Expr>::rows, expression::traits<Expr>::columns>(index);

			return this->_expr(row, column);
		}

		inline
		typename expression::traits<Expr>::type&
		operator [] (size_t index) noexcept
		{
			size_t row, column;
			std::tie(row, column) = Order::template index<
				expression::traits<Expr>::rows, expression::traits<Expr>::columns>(index);

			return this->_expr(row, column);
		}
	};
}

#endif
