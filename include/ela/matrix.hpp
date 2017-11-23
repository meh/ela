// Copyright (c) 2017 1aim GmbH
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

#ifndef _ELA_MATRIX_H
#define _ELA_MATRIX_H

#include <algorithm>
#include <cmath>
#include <initializer_list>

namespace ela {
	/* A matrix.
	 */
	template <size_t Columns, size_t Rows, typename Type>
	class matrix: public expression, public expression_traits<Columns, Rows, Type>
	{
	public:
		typedef expression_traits<Columns, Rows, Type> traits;

	public:
		/* Create an empty matrix.
		 */
		matrix () noexcept
		{ }

		/* Create an identity matrix with the given value.
		 */
		template <size_t C = Columns, size_t R = Rows>
		matrix (Type value, typename std::enable_if<C == R>::type* = 0) noexcept
		{
			for (size_t i = 0; i < Rows; i++) {
				_buffer[i * Rows + i] = value;
			}
		}

		/* Create a matrix from the given expression.
		 */
		template <typename Expr, size_t C = Columns, size_t R = Rows, typename T = Type>
		matrix (Expr const& expr, typename std::enable_if<C == Expr::columns && R == Expr::rows && std::is_same<T, typename Expr::type>::value>::type* = 0) noexcept
		{
			*this = expr;
		}

		/* Create a matrix from another matrix, copying the data.
		 */
		matrix (matrix<Columns, Rows, Type> const& from) noexcept
		{
			*this = from;
		}

		/* Create a matrix from an initializer list.
		 */
		matrix (std::initializer_list<std::initializer_list<Type>> list) noexcept
		{
			*this = list;
		}

		/* Create a matrix from a pointer, copying the data.
		 */
		matrix (const Type* buffer) noexcept
		{
			*this = buffer;
		}

		/* Copy the contents of the matrix.
		 */
		inline
		matrix<Columns, Rows, Type>&
		operator = (matrix<Columns, Rows, Type> const& from) noexcept
		{
			std::copy(&from, &from + Columns * Rows, _buffer);

			return *this;
		}

		/* Copy the data present in the pointer.
		 */
		inline
		matrix<Columns, Rows, Type>&
		operator = (const Type* data) noexcept
		{
			std::copy(data, data + Columns * Rows, _buffer);

			return *this;
		}

		/* Copy the data from the initializer list.
		 */
		inline
		matrix<Columns, Rows, Type>&
		operator = (std::initializer_list<std::initializer_list<Type>> rows) noexcept
		{
			std::fill_n(_buffer, Columns * Rows, 0);

			size_t row_index = 0;
			for (auto row : rows) {
				size_t column_index = 0;
				for (auto value : row) {
					_buffer[column_index * Rows + row_index] = value;

					column_index++;
				}

				row_index++;
			}

			return *this;
		}

		/* Copy the data from the expression.
		 */
		template <typename Expr, size_t C = Columns, size_t R = Rows, typename T = Type>
		inline
		typename std::enable_if<C == Expr::columns &&
		                        R == Expr::rows &&
		                        std::is_same<T, typename Expr::type>::value,
		matrix<Columns, Rows, Type>&>::type
		operator = (Expr const& expr) noexcept
		{
			for (size_t row = 0; row < Rows; row++) {
				for (size_t column = 0; column < Columns; column++) {
					_buffer[column * Rows + row] = expr(row, column);
				}
			}

			return *this;
		}

		/* Access a scalar at the given row and column.
		 */
		inline
		Type const&
		operator () (size_t row, size_t column) const noexcept
		{
			return _buffer[column * Rows + row];
		}

		/* Access a scalar at the given row and column.
		 */
		inline
		Type&
		operator () (size_t row, size_t column) noexcept
		{
			return _buffer[column * Rows + row];
		}

		/* Access a scalar at the given column, only available for vectors.
		 */
		template <size_t R = Rows>
		inline
		typename std::enable_if<R == 1, Type>::type const&
		operator () (size_t column) const noexcept
		{
			return _buffer[column];
		}

		/* Access a scalar at the given column, only available for vectors.
		 */
		template <size_t R = Rows>
		inline
		typename std::enable_if<R == 1, Type>::type&
		operator () (size_t column) noexcept
		{
			return _buffer[column];
		}

		/* Create a multiplication expression.
		 */
		template <typename Right>
		inline
		expr::mul<matrix<Columns, Rows, Type>, Right>
		operator * (Right const& other) const
		{
			return expr::mul<matrix<Columns, Rows, Type>, Right>(*this, other);
		}

		/* Create an addition expression.
		 */
		template <typename Right>
		inline
		expr::add<matrix<Columns, Rows, Type>, Right>
		operator + (Right const& other) const
		{
			return expr::add<matrix<Columns, Rows, Type>, Right>(*this, other);
		}

		/* Create a subtraction expression.
		 */
		template <typename Right>
		inline
		expr::sub<matrix<Columns, Rows, Type>, Right>
		operator - (Right const& other) const
		{
			return expr::sub<matrix<Columns, Rows, Type>, Right>(*this, other);
		}

		/* Return the wrapped raw pointer (row major).
		 */
		inline
		Type* operator & (void) noexcept
		{
			return _buffer;
		}

		/* Return the wrapped constant raw pointer (row major).
		 */
		inline
		Type const* operator & (void) const noexcept
		{
			return _buffer;
		}

	private:
		Type _buffer[Columns * Rows] = { 0 };
	};

	/* A vector.
	 */
	template <size_t Columns, typename Type = float>
	using vector = matrix<Columns, 1, Type>;
}

#endif
