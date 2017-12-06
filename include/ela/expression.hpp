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

#ifndef _ELA_EXPRESSION_H
#define _ELA_EXPRESSION_H

namespace ela { namespace expression {
	/* Traits for expressions.
	 */
	template <typename Expr>
	struct traits
	{
		/* The scalar type.
		 */
		typedef void type;

		/* The number of rows.
		 */
		static constexpr size_t rows = 0;

		/* The number of columns.
		 */
		static constexpr size_t columns = 0;
	};

	/* Base expression type, defines common operators to all expressions and
	 * expression-like types.
	 */
	template <typename Expr>
	class base
	{
	public:
		/* Create an addition expression.
		 */
		template <typename Right>
		inline
		add<Expr, Right>
		operator + (Right const& other) const noexcept
		{
			return add<Expr, Right>(static_cast<Expr const&>(*this), other);
		}

		/* Create a subtraction expression.
		 */
		template <typename Right>
		inline
		subtract<Expr, Right>
		operator - (Right const& other) const noexcept
		{
			return subtract<Expr, Right>(static_cast<Expr const&>(*this), other);
		}

		/* Create a multiplication expression.
		 */
		template <typename Right>
		inline
		typename std::enable_if<!std::is_same<typename traits<Right>::type, void>::value,
		multiply<Expr, Right>>::type
		operator * (Right const& other) const noexcept
		{
			return multiply<Expr, Right>(static_cast<Expr const&>(*this), other);
		}

		/* Create a multiplication expression.
		 */
		inline
		scale<Expr>
		operator * (typename traits<Expr>::type value) const noexcept
		{
			return scale<Expr>(static_cast<Expr const&>(*this), value);
		}

		/* Create a transpose expression.
		 */
		inline
		transpose<Expr>
		operator ~ () const noexcept
		{
			return transpose<Expr>(static_cast<Expr const&>(*this));
		}

		/* Create an inversion expression.
		 */
		inline
		invert<Expr>
		operator ! () const noexcept
		{
			return invert<Expr>(static_cast<Expr const&>(*this));
		}

		/* Check two expressions yield the same result.
		 */
		template <typename Right>
		inline
		bool
		operator == (Right const& other) const noexcept
		{
			if (traits<Expr>::rows != traits<Right>::rows || traits<Expr>::columns != traits<Right>::columns) {
				return false;
			}

			for (size_t row = 0; row < traits<Expr>::rows; row++) {
				for (size_t column = 0; column < traits<Expr>::columns; column++) {
					if (static_cast<Expr const&>(*this)(row, column) != other(row, column)) {
						return false;
					}
				}
			}

			return true;
		}

		/* Check two expressions do not yield the same result.
		 */
		template <typename Right>
		inline
		bool
		operator != (Right const& other) const noexcept
		{
			return !(*this == other);
		}

		/* Access a scalar at the given coordinates with compile-time bound
		 * checking.
		 */
		template <size_t Row, size_t Column>
		inline
		typename traits<Expr>::type
		at () const noexcept
		{
			static_assert(Row < traits<Expr>::rows && Column < traits<Expr>::columns,
				"index out of bounds");

			return at(Row, Column);
		}

		/* Access a scalar at the given coordinates.
		 */
		inline
		typename traits<Expr>::type
		at (size_t row, size_t column) const noexcept
		{
			return static_cast<Expr const&>(*this)(row, column);
		}

		/* Access a scalar at the given index, only available for expressions
		 * returning vectors.
		 */
		template <typename T = typename traits<Expr>::type, size_t R = traits<Expr>::rows, size_t C = traits<Expr>::columns>
		inline
		typename std::enable_if<R == 1 || C == 1, T>::type
		operator [] (size_t index) const noexcept
		{
			ELA_ASSUME(index < (R == 1 ? C : R));

			return (R == 1)
				? static_cast<Expr const&>(*this)(0, index)
				: static_cast<Expr const&>(*this)(index, 0);
		}

		/* Access the column vector at the given index with compile-time bound
		 * checking.
		 */
		template <size_t Index>
		inline
		vector<Expr, for_column<Expr>>
		column () noexcept
		{
			static_assert(Index < traits<Expr>::columns,
				"index out of bounds");

			return vector<Expr, for_column<Expr>>(static_cast<Expr&>(*this), Index);
		}

		/* Access the column vector at the given index.
		 */
		inline
		vector<Expr, for_column<Expr>>
		column (size_t index) noexcept
		{
			return vector<Expr, for_column<Expr>>(static_cast<Expr&>(*this), index);
		}

		/* Access the row vector at the given index with compile-time bound
		 * checking.
		 */
		template <size_t Index>
		inline
		vector<Expr, for_row<Expr>>
		row () noexcept
		{
			static_assert(Index < traits<Expr>::rows,
				"index out of bounds");

			return vector<Expr, for_row<Expr>>(static_cast<Expr&>(*this), Index);
		}

		/* Access the row vector at the given index.
		 */
		inline
		vector<Expr, for_row<Expr>>
		row (size_t index) noexcept
		{
			return vector<Expr, for_row<Expr>>(static_cast<Expr&>(*this), index);
		}
	};

	/* Unary expressions.
	 */
	template <typename Expr, typename Input>
	class unary: public base<Expr>
	{
	public:
		/* The type of the input expression.
		 */
		typedef Input input;

	protected:
		/* Create a new unary expression.
		 */
		unary (Input const& input) noexcept
			: _input(input)
		{ }

	protected:
		Input const& _input;
	};

	/* Binary expressions.
	 */
	template <typename Expr, typename Left, typename Right>
	class binary: public base<Expr>
	{
		static_assert(std::is_same<typename traits<Left>::type, typename traits<Right>::type>::value,
			"type mismatch");

	public:
		/* The type of the left hand side expression.
		 */
		typedef Left left;

		/* The type of the right hand side expression.
		 */
		typedef Right right;

	protected:
		/* Create a new binary expression.
		 */
		binary (Left const& left, Right const& right) noexcept
			: _left(left), _right(right)
		{ }

	protected:
		Left const&  _left;
		Right const& _right;
	};
} }

/* Binary expressions.
 */
#include "expression/add.hpp"
#include "expression/subtract.hpp"
#include "expression/multiply.hpp"
#include "expression/scale.hpp"

/* Unary expressions.
 */
#include "expression/transpose.hpp"
#include "expression/invert.hpp"

#endif
