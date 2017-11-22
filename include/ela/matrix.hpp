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

#include <initializer_list>

namespace ela {
	/* A matrix.
	 */
	template <size_t Columns, size_t Rows, typename Type>
	class matrix: public expression<matrix<Columns, Rows, Type>>
	{
	public:
		typedef Type type;
		static constexpr size_t columns = Columns;
		static constexpr size_t rows = Rows;
		static constexpr size_t bytes = Columns * Rows * sizeof(Type);
		static constexpr size_t elements = Columns * Rows;

	public:
		/* Create an empty matrix.
		 */
		matrix () noexcept;

		/* Create an identity matrix with the given value.
		 */
		template <size_t C = Columns, size_t R = Rows>
		matrix (Type value, typename std::enable_if<C == R>::type* = 0) noexcept;

		/* Create a matrix from another matrix, copying the data.
		 */
		matrix (matrix<Columns, Rows, Type> const& from) noexcept;

		/* Create a matrix from an initializer list.
		 */
		matrix (std::initializer_list<std::initializer_list<Type>> list) noexcept;

		/* Create a matrix from a pointer, copying the data.
		 */
		matrix (const Type* data) noexcept;

		void
		force (matrix<Columns, Rows, Type>& out) const noexcept;

		/* Copy the contents of the matrix.
		 */
		matrix<Columns, Rows, Type>&
		operator = (matrix<Columns, Rows, Type> const& from) noexcept;

		/* Copy the data present in the pointer.
		 */
		matrix<Columns, Rows, Type>&
		operator = (const Type* data) noexcept;

		/* Copy the data from the initializer list.
		 */
		matrix<Columns, Rows, Type>&
		operator = (std::initializer_list<std::initializer_list<Type>> list) noexcept;

		/* Access a scalar at the given row and column.
		 */
		Type const&
		operator () (size_t row, size_t column) const noexcept;

		/* Access a scalar at the given row and column.
		 */
		Type&
		operator () (size_t row, size_t column) noexcept;

		/* Access a scalar at the given column, only available for vectors.
		 */
		template <size_t R = Rows>
		typename std::enable_if<R == 1, Type>::type const&
		operator () (size_t column) const noexcept;

		/* Access a scalar at the given column, only available for vectors.
		 */
		template <size_t R = Rows>
		typename std::enable_if<R == 1, Type>::type&
		operator () (size_t column) noexcept;

		/* Create a multiplication.
		 */
		template <size_t RightColumns, size_t RightRows>
		expr::mul<
			matrix<Columns, Rows, Type>,
			matrix<RightColumns, RightRows, Type>,
			matrix<RightColumns, Rows, Type>
		>
		operator * (matrix<RightColumns, RightRows, Type> const& other) const;

		/* Return the wrapped raw pointer (row major).
		 */
		Type* operator & (void);

		/* Return the wrapped constant raw pointer (row major).
		 */
		Type const* operator & (void) const;

	private:
		Type _buffer[Columns * Rows] = { 0 };
	};

	/* A vector.
	 */
	template <size_t Columns, typename Type = float>
	using vector = matrix<Columns, 1, Type>;
}

#ifndef _ELA_MATRIX_NO_IMPL
#include "matrix.tpp"
#endif

#endif
