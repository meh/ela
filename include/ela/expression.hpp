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

#ifndef ELA_EXPRESSION_H
#define ELA_EXPRESSION_H

namespace ela { namespace expression {
	namespace derive {
		template <typename Self>
		struct operators
		{
			/* Create an addition expression.
			 */
			template <typename Other>
			inline
			add<Self, Other>
			operator + (Other const& other) const noexcept
			{
				return add<Self, Other>(static_cast<Self const&>(*this), other);
			}

			/* Create a subtraction expression.
			 */
			template <typename Other>
			inline
			subtract<Self, Other>
			operator - (Other const& other) const noexcept
			{
				return subtract<Self, Other>(static_cast<Self const&>(*this), other);
			}

			/* Create a multiplication expression.
			 */
			template <typename Other>
			inline
			typename std::enable_if<!std::is_same<typename traits<Other>::type, void>::value,
			multiply<Self, Other>>::type
			operator * (Other const& other) const noexcept
			{
				return multiply<Self, Other>(static_cast<Self const&>(*this), other);
			}

			/* Create a multiplication expression.
			 */
			inline
			scale<Self>
			operator * (typename traits<Self>::type value) const noexcept
			{
				return scale<Self>(static_cast<Self const&>(*this), value);
			}

			/* Create a transpose expression.
			 */
			inline
			transpose<Self>
			operator ~ () const noexcept
			{
				return transpose<Self>(static_cast<Self const&>(*this));
			}

			/* Create a transpose expression.
			 */
			inline
			transpose<Self>
			operator ~ () noexcept
			{
				return transpose<Self>(static_cast<Self&>(*this));
			}

			/* Create an inversion expression.
			 */
			inline
			invert<Self>
			operator ! () const noexcept
			{
				return invert<Self>(static_cast<Self const&>(*this));
			}

			/* Check two expressions yield the same result.
			 */
			template <typename Other>
			inline
			bool
			operator == (Other const& other) const noexcept
			{
				if (traits<Self>::rows != traits<Other>::rows || traits<Self>::columns != traits<Other>::columns) {
					return false;
				}

				for (size_t row = 0; row < traits<Self>::rows; row++) {
					for (size_t column = 0; column < traits<Self>::columns; column++) {
						if (static_cast<Self const&>(*this)(row, column) != other(row, column)) {
							return false;
						}
					}
				}

				return true;
			}

			/* Check two expressions do not yield the same result.
			 */
			template <typename Other>
			inline
			bool
			operator != (Other const& other) const noexcept
			{
				return !(*this == other);
			}
		};

		template <typename Self>
		struct vectors<Self, false>
		{
			/* Access the column vector at the given index with compile-time bound
			 * checking.
			 */
			template <size_t Index>
			inline
			vector<Self, for_column<Self>, false>
			column () const noexcept
			{
				static_assert(Index < traits<Self>::columns,
					"index out of bounds");

				return vector<Self, for_column<Self>, false>(
					static_cast<Self const&>(*this), Index);
			}

			/* Access the column vector at the given index.
			 */
			inline
			vector<Self, for_column<Self>, false>
			column (size_t index) const noexcept
			{
				return vector<Self, for_column<Self>, false>(
					static_cast<Self const&>(*this), index);
			}

			/* Access the row vector at the given index with compile-time bound
			 * checking.
			 */
			template <size_t Index>
			inline
			vector<Self, for_row<Self>>
			row () const noexcept
			{
				static_assert(Index < traits<Self>::rows,
					"index out of bounds");

				return vector<Self, for_row<Self>, false>(
					static_cast<Self const&>(*this), Index);
			}

			/* Access the row vector at the given index.
			 */
			inline
			vector<Self, for_row<Self>>
			row (size_t index) const noexcept
			{
				return vector<Self, for_row<Self>, false>(
					static_cast<Self const&>(*this), index);
			}
		};

		template <typename Self>
		struct vectors<Self, true>
		{
			/* Access the column vector at the given index with compile-time bound
			 * checking.
			 */
			template <size_t Index>
			inline
			vector<Self, for_column<Self>, false>
			column () const noexcept
			{
				static_assert(Index < traits<Self>::columns,
					"index out of bounds");

				return vector<Self, for_column<Self>, false>(
					static_cast<Self const&>(*this), Index);
			}

			/* Access the column vector at the given index.
			 */
			inline
			vector<Self, for_column<Self>, false>
			column (size_t index) const noexcept
			{
				return vector<Self, for_column<Self>, false>(
					static_cast<Self const&>(*this), index);
			}

			/* Access the column vector at the given index with compile-time bound
			 * checking.
			 */
			template <size_t Index>
			inline
			vector<Self, for_column<Self>, true>
			column () noexcept
			{
				static_assert(Index < traits<Self>::columns,
					"index out of bounds");

				return vector<Self, for_column<Self>, true>(
					static_cast<Self&>(*this), Index);
			}

			/* Access the column vector at the given index.
			 */
			inline
			vector<Self, for_column<Self>, true>
			column (size_t index) noexcept
			{
				return vector<Self, for_column<Self>, true>(
					static_cast<Self&>(*this), index);
			}

			/* Access the row vector at the given index with compile-time bound
			 * checking.
			 */
			template <size_t Index>
			inline
			vector<Self, for_row<Self>>
			row () const noexcept
			{
				static_assert(Index < traits<Self>::rows,
					"index out of bounds");

				return vector<Self, for_row<Self>, false>(
					static_cast<Self const&>(*this), Index);
			}

			/* Access the row vector at the given index.
			 */
			inline
			vector<Self, for_row<Self>>
			row (size_t index) const noexcept
			{
				return vector<Self, for_row<Self>, false>(
					static_cast<Self const&>(*this), index);
			}

			/* Access the row vector at the given index with compile-time bound
			 * checking.
			 */
			template <size_t Index>
			inline
			vector<Self, for_row<Self>, true>
			row () noexcept
			{
				static_assert(Index < traits<Self>::rows,
					"index out of bounds");

				return vector<Self, for_row<Self>, true>(
					static_cast<Self&>(*this), Index);
			}

			/* Access the row vector at the given index.
			 */
			inline
			vector<Self, for_row<Self>, true>
			row (size_t index) noexcept
			{
				return vector<Self, for_row<Self>, true>(
					static_cast<Self&>(*this), index);
			}
		};

		template <typename Self>
		struct accessors<Self, false>
		{
			/* Access a scalar at the given coordinates with compile-time bound
			 * checking.
			 */
			template <size_t Row, size_t Column>
			inline
			typename traits<Self>::type
			at () const noexcept
			{
				static_assert(Row < traits<Self>::rows && Column < traits<Self>::columns,
					"index out of bounds");

				return static_cast<Self const&>(*this)(Row, Column);
			}

			/* Access a scalar at the given index, only available for vector
			 * expressions.
			 */
			template <typename T = typename traits<Self>::type, size_t R = traits<Self>::rows, size_t C = traits<Self>::columns>
			inline
			typename std::enable_if<R == 1 || C == 1, T>::type
			operator [] (size_t index) const noexcept
			{
				ELA_ASSUME(index < (R == 1 ? C : R));

				return (R == 1)
					? static_cast<Self const&>(*this)(0, index)
					: static_cast<Self const&>(*this)(index, 0);
			}
		};

		template <typename Self>
		struct accessors<Self, true>
		{
			/* Access a scalar at the given coordinates with compile-time bound
			 * checking.
			 */
			template <size_t Row, size_t Column>
			inline
			typename traits<Self>::type const&
			at () const noexcept
			{
				static_assert(Row < traits<Self>::rows && Column < traits<Self>::columns,
					"index out of bounds");

				return static_cast<Self const&>(*this)(Row, Column);
			}

			/* Access a scalar at the given coordinates with compile-time bound
			 * checking.
			 */
			template <size_t Row, size_t Column>
			inline
			typename traits<Self>::type
			at () noexcept
			{
				static_assert(Row < traits<Self>::rows && Column < traits<Self>::columns,
					"index out of bounds");

				return static_cast<Self&>(*this)(Row, Column);
			}

			/* Access a scalar at the given index, only available for vector
			 * expressions.
			 */
			template <typename T = typename traits<Self>::type, size_t R = traits<Self>::rows, size_t C = traits<Self>::columns>
			inline
			typename std::enable_if<R == 1 || C == 1, T>::type const&
			operator [] (size_t index) const noexcept
			{
				ELA_ASSUME(index < (R == 1 ? C : R));

				return (R == 1)
					? static_cast<Self const&>(*this)(0, index)
					: static_cast<Self const&>(*this)(index, 0);
			}

			/* Access a scalar at the given index, only available for vector
			 * expressions.
			 */
			template <typename T = typename traits<Self>::type, size_t R = traits<Self>::rows, size_t C = traits<Self>::columns>
			inline
			typename std::enable_if<R == 1 || C == 1, T>::type&
			operator [] (size_t index) noexcept
			{
				ELA_ASSUME(index < (R == 1 ? C : R));

				return (R == 1)
					? static_cast<Self&>(*this)(0, index)
					: static_cast<Self&>(*this)(index, 0);
			}
		};

		template <typename Self, bool Concrete>
		struct assignment
		{ };

		template <typename Self>
		struct assignment<Self, true>
		{
			/* Copy the data from the initializer list.
			 */
			inline
			Self&
			operator = (std::initializer_list<std::initializer_list<typename traits<Self>::type>> rows) noexcept
			{
				ELA_ASSUME(rows.size() == traits<Self>::rows);

				size_t row = 0;
				for (auto columns : rows) {
					ELA_ASSUME(columns.size() == traits<Self>::columns);

					size_t column = 0;
					for (auto element : columns) {
						static_cast<Self&>(*this)(row, column) = element;

						column++;
					}

					row++;
				}

				return static_cast<Self&>(*this);
			}

			/* Copy the data from the initializer list, only for vectors.
			 */
			inline
			Self&
			operator = (std::initializer_list<typename traits<Self>::type> elements) noexcept
			{
				ELA_ASSUME(elements.size() == traits<Self>::rows * traits<Self>::columns);

				size_t index = 0;
				for (auto element : elements) {
					static_cast<Self&>(*this)(index % traits<Self>::rows, index / traits<Self>::rows) = element;
					index++;
				}

				return static_cast<Self&>(*this);
			}

			/* Copy the data from the expression.
			 */
			template <typename Input, typename T = typename traits<Self>::type, size_t R = traits<Self>::rows, size_t C = traits<Self>::columns>
			inline
			typename std::enable_if<R == traits<Input>::rows &&
		                          C == traits<Input>::columns &&
		                          std::is_same<T, typename traits<Input>::type>::value,
			Self&>::type
			operator = (Input const& input) noexcept
			{
				for (size_t row = 0; row < traits<Self>::rows; row++) {
					for (size_t column = 0; column < traits<Self>::columns; column++) {
						static_cast<Self&>(*this)(row, column) = input(row, column);
					}
				}

				return static_cast<Self&>(*this);
			}
		};
	}

	/* Base expression type, defines common operators to all expressions and
	 * expression-like types.
	 */
	template <typename Self>
	struct base<Self, false>: public derive::operators<Self>,
	                          public derive::vectors<Self>,
	                          public derive::accessors<Self>
	{ };

	template <typename Self>
	struct base<Self, true>: public derive::operators<Self>,
	                         public derive::vectors<Self>,
	                         public derive::accessors<Self>,
	                         public derive::assignment<Self>
	{
		using derive::assignment<Self, true>::operator =;
	};

	/* Unary expressions.
	 */
	template <typename Self, typename Input>
	class unary: public base<Self>
	{
	public:
		/* The type of the input expression.
		 */
		typedef typename std::remove_reference<typename std::remove_cv<Input>::type>::type input;

	protected:
		/* Create a new unary expression.
		 */
		unary (Input input) noexcept
			: _input(input)
		{ }

	protected:
		Input _input;
	};

	/* Binary expressions.
	 */
	template <typename Self, typename Left, typename Right>
	class binary: public base<Self>
	{
	public:
		/* The type of the left hand side expression.
		 */
		typedef typename std::remove_reference<typename std::remove_cv<Left>::type>::type left;

		/* The type of the right hand side expression.
		 */
		typedef typename std::remove_reference<typename std::remove_cv<Left>::type>::type right;

	protected:
		/* Create a new binary expression.
		 */
		binary (Left left, Right right) noexcept
			: _left(left), _right(right)
		{ }

	protected:
		Left  _left;
		Right _right;
	};
} }

namespace ela {
	template <typename T>
	struct void_t
	{
		typedef void type;
	};

	template <typename Expr, typename = void>
	struct is_expr : public std::false_type
	{ };

	template <typename Expr>
	struct is_expr<Expr, typename void_t<typename expression::traits<Expr>::type>::type>
		: public std::true_type
	{ };

	template <typename Expr>
	using expr_traits = expression::traits<Expr>;
}

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
