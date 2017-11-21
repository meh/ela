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

#ifndef _MATRIX_H
#define _MATRIX_H

#include <initializer_list>

namespace meh {
	template <size_t Columns, size_t Rows, typename Type = float>
	class matrix
	{
	public:
		const size_t columns = Columns;
		const size_t rows = Rows;
		typedef Type type;

	public:
		matrix (Type value = 0) noexcept;
		matrix (matrix<Columns, Rows, Type> const& from) noexcept;
		matrix (std::initializer_list<std::initializer_list<Type>> list) noexcept;
		matrix (const Type* data) noexcept;

		matrix<Columns, Rows, Type>&
		operator = (matrix<Columns, Rows, Type> const& from) noexcept;

		matrix<Columns, Rows, Type>&
		operator = (const Type* data) noexcept;

		matrix<Columns, Rows, Type>&
		operator = (std::initializer_list<std::initializer_list<Type>> list) noexcept;

		Type const&
		operator () (size_t row, size_t column) const noexcept;

		Type&
		operator () (size_t row, size_t column) noexcept;

		template <size_t R = Rows>
		typename std::enable_if<R == 1, Type>::type const&
		operator () (size_t column) const noexcept;

		template <size_t R = Rows>
		typename std::enable_if<R == 1, Type>::type&
		operator () (size_t column) noexcept;

	private:
		Type _buffer[Columns * Rows] = { 0 };
	};

	template <size_t Columns, typename Type = float>
	using vector = matrix<Columns, 1, Type>;
}

#ifndef _MATRIX_NO_IMPL
#include "matrix.tpp"
#endif

#endif
