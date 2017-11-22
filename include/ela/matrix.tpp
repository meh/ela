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

#include <algorithm>
#include <cmath>
#include <initializer_list>

namespace ela {
	template <size_t Columns, size_t Rows, typename Type>
	matrix<Columns, Rows, Type>::matrix () noexcept
	{ }

	template <size_t Columns, size_t Rows, typename Type>
	template <size_t C, size_t R>
	matrix<Columns, Rows, Type>::matrix (Type value, typename std::enable_if<C == R>::type* _dummy) noexcept
	{
		for (size_t i = 0; i < Rows; i++) {
			_buffer[i * Rows + i] = value;
		}
	}

	template <size_t Columns, size_t Rows, typename Type>
	template <typename Expr, size_t C, size_t R, typename T>
	matrix<Columns, Rows, Type>::matrix (Expr const& expr, typename std::enable_if<C == Expr::columns && R == Expr::rows && std::is_same<T, typename Expr::type>::value>::type* _dummy) noexcept
	{
		*this = expr;
	}

	template <size_t Columns, size_t Rows, typename Type>
	matrix<Columns, Rows, Type>::matrix (matrix<Columns, Rows, Type> const& from) noexcept
	{
		std::copy(&from, &from + Columns * Rows, _buffer);
	}

	template <size_t Columns, size_t Rows, typename Type>
	matrix<Columns, Rows, Type>::matrix (std::initializer_list<std::initializer_list<Type>> list) noexcept
	{
		*this = list;
	}

	template <size_t Columns, size_t Rows, typename Type>
	matrix<Columns, Rows, Type>::matrix (const Type* buffer) noexcept
	{
		*this = buffer;
	}

	template <size_t Columns, size_t Rows, typename Type>
	matrix<Columns, Rows, Type>&
	matrix<Columns, Rows, Type>::operator = (matrix<Columns, Rows, Type> const& from) noexcept
	{
		std::copy(&from, &from + Columns * Rows, _buffer);

		return *this;
	}

	template <size_t Columns, size_t Rows, typename Type>
	matrix<Columns, Rows, Type>&
	matrix<Columns, Rows, Type>::operator = (const Type* data) noexcept
	{
		std::copy(data, data + Columns * Rows, _buffer);

		return *this;
	}

	template <size_t Columns, size_t Rows, typename Type>
	matrix<Columns, Rows, Type>&
	matrix<Columns, Rows, Type>::operator = (std::initializer_list<std::initializer_list<Type>> rows) noexcept
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

	template <size_t Columns, size_t Rows, typename Type>
	template <typename Expr, size_t C, size_t R, typename T>
	typename std::enable_if<C == Expr::columns && R == Expr::rows && std::is_same<T, typename Expr::type>::value,
		matrix<Columns, Rows, Type>&>::type
	matrix<Columns, Rows, Type>::operator = (Expr const& expr) noexcept
	{
		for (size_t row = 0; row < Rows; row++) {
			for (size_t column = 0; column < Columns; column++) {
				_buffer[column * Rows + row] = expr(row, column);
			}
		}

		return *this;
	}

	template <size_t Columns, size_t Rows, typename Type>
	Type const&
	matrix<Columns, Rows, Type>::operator () (size_t row, size_t column) const noexcept
	{
		return _buffer[column * Rows + row];
	}

	template <size_t Columns, size_t Rows, typename Type>
	Type&
	matrix<Columns, Rows, Type>::operator () (size_t row, size_t column) noexcept
	{
		return _buffer[column * Rows + row];
	}

	template <size_t Columns, size_t Rows, typename Type>
	template <size_t R>
	typename std::enable_if<R == 1, Type>::type const&
	matrix<Columns, Rows, Type>::operator () (size_t column) const noexcept
	{
		return _buffer[column];
	}

	template <size_t Columns, size_t Rows, typename Type>
	template <size_t R>
	typename std::enable_if<R == 1, Type>::type&
	matrix<Columns, Rows, Type>::operator () (size_t column) noexcept
	{
		return _buffer[column];
	}

	template <size_t Columns, size_t Rows, typename Type>
	template <size_t RightColumns, size_t RightRows>
	expr::mul<matrix<Columns, Rows, Type>, matrix<RightColumns, RightRows, Type>>
	matrix<Columns, Rows, Type>::operator * (matrix<RightColumns, RightRows, Type> const& other) const
	{
		return expr::mul<matrix<Columns, Rows, Type>, matrix<RightColumns, RightRows, Type>>
			(*this, other);
	}

	template <size_t Columns, size_t Rows, typename Type>
	Type*
	matrix<Columns, Rows, Type>::operator & (void)
	{
		return _buffer;
	}

	template <size_t Columns, size_t Rows, typename Type>
	Type const*
	matrix<Columns, Rows, Type>::operator & (void) const
	{
		return _buffer;
	}
}
