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
	template <typename Type, size_t Rows, size_t Columns>
	class matrix: public expression, public expression_traits<Type, Rows, Columns>
	{
	public:
		typedef expression_traits<Type, Rows, Columns> traits;

	public:
		/* Create an empty matrix.
		 */
		matrix () noexcept
		{ }

		/* Create an identity matrix with the given value.
		 */
		template <size_t R = Rows, size_t C = Columns>
		matrix (Type value, typename std::enable_if<R == C>::type* = 0) noexcept
		{
			for (size_t i = 0; i < Rows; i++) {
				_buffer[i * Rows + i] = value;
			}
		}

		/* Create a matrix from the given expression.
		 */
		template <typename Expr, typename T = Type, size_t R = Rows, size_t C = Columns>
		matrix (Expr const& expr, typename std::enable_if<R == Expr::rows && C == Expr::columns && std::is_same<T, typename Expr::type>::value>::type* = 0) noexcept
		{
			*this = expr;
		}

		/* Create a matrix from another matrix, copying the data.
		 */
		matrix (matrix<Type, Rows, Columns> const& from) noexcept
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
		matrix<Type, Rows, Columns>&
		operator = (matrix<Type, Rows, Columns> const& from) noexcept
		{
			std::copy(&from, &from + Rows * Columns, _buffer);

			return *this;
		}

		/* Copy the data present in the pointer.
		 */
		inline
		matrix<Type, Rows, Columns>&
		operator = (const Type* data) noexcept
		{
			std::copy(data, data + Rows * Columns, _buffer);

			return *this;
		}

		/* Copy the data from the initializer list.
		 */
		inline
		matrix<Type, Rows, Columns>&
		operator = (std::initializer_list<std::initializer_list<Type>> rows) noexcept
		{
			std::fill_n(_buffer, Rows * Columns, 0);

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
		template <typename Expr, typename T = Type, size_t R = Rows, size_t C = Columns>
		inline
		typename std::enable_if<R == Expr::rows &&
		                        C == Expr::columns &&
		                        std::is_same<T, typename Expr::type>::value,
		matrix<Type, Rows, Columns>&>::type
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

		/* Access a scalar at the given index, only available for vectors.
		 */
		template <typename T = Type, size_t R = Rows, size_t C = Columns>
		inline
		typename std::enable_if<R == 1 || C == 1, T const&>::type
		operator [] (size_t index) const noexcept
		{
			return (Rows == 1) ? (*this)(0, index) : (*this)(index, 0);
		}

		/* Access a scalar at the given index, only available for vectors.
		 */
		template <typename T = Type, size_t R = Rows, size_t C = Columns>
		inline
		typename std::enable_if<R == 1 || C == 1, T&>::type
		operator [] (size_t index) noexcept
		{
			return (Rows == 1) ? (*this)(0, index) : (*this)(index, 0);
		}

		/* Create an addition expression.
		 */
		template <typename Right>
		inline
		expr::add<matrix<Type, Rows, Columns>, Right>
		operator + (Right const& other) const
		{
			return expr::add<matrix<Type, Rows, Columns>, Right>(*this, other);
		}

		/* Add the resulting expression in place.
		 */
		template <typename Right>
		inline
		matrix<Type, Rows, Columns>&
		operator += (Right const& other)
		{
			*this = *this + other;
			return *this;
		}

		/* Create a subtraction expression.
		 */
		template <typename Right>
		inline
		expr::sub<matrix<Type, Rows, Columns>, Right>
		operator - (Right const& other) const
		{
			return expr::sub<matrix<Type, Rows, Columns>, Right>(*this, other);
		}

		/* Subtract the resulting expression in place.
		 */
		template <typename Right>
		inline
		matrix<Type, Rows, Columns>&
		operator -= (Right const& other)
		{
			*this = *this - other;
			return *this;
		}

		/* Create a multiplication expression.
		 */
		template <typename Right>
		inline
		expr::mul<matrix<Type, Rows, Columns>, Right>
		operator * (Right const& other) const
		{
			return expr::mul<matrix<Type, Rows, Columns>, Right>(*this, other);
		}

		/* Multiply the resulting expression in place.
		 */
		template <typename Right>
		inline
		matrix<Type, Rows, Columns>&
		operator *= (Right const& other)
		{
			*this = *this * other;
			return *this;
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
		Type _buffer[Rows * Columns] = { 0 };
	};
}

#endif
