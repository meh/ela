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

#ifndef _ELA_VIEW_H
#define _ELA_VIEW_H

#include <initializer_list>
#include "matrix.hpp"

namespace ela {
	/* By column view.
	 */
	template <size_t Index>
	class for_column
	{
	public:
		constexpr static size_t index = Index;

	public:
		template <size_t Rows, size_t Columns, typename Type>
		static inline
		Type const&
		get (matrix<Rows, Columns, Type> const& inner, size_t row)
		{
			return inner(row, index);
		}
	};

	/* By row view.
	 */
	template <size_t Index>
	class for_row
	{
	public:
		constexpr static size_t index = Index;

	public:
		template <size_t Rows, size_t Columns, typename Type>
		static inline
		Type const&
		get (matrix<Rows, Columns, Type> const& inner, size_t column)
		{
			return inner(index, column);
		}
	};

	/* A constant view over a matrix.
	 */
	template <typename Accessor, size_t Rows, size_t Columns, typename Type>
	class view
	{
	public:
		typedef Accessor                    accessor;
		typedef matrix<Rows, Columns, Type> for_matrix;

	public:
		/* Create a new view for the index.
		 */
		view (matrix<Rows, Columns, Type> const& inner) noexcept
			: _inner(inner)
		{ }

		/*
		 * Access the value at the index.
		 */
		inline
		Type const&
		operator [] (size_t index) const noexcept
		{
			return Accessor::get(_inner, index);
		}

	private:
		for_matrix const& _inner;
	};

	/* Create a new view.
	 */
	template <typename Accessor, size_t Rows, size_t Columns, typename Type>
	static inline
	view<Accessor, Rows, Columns, Type>
	make_view (matrix<Rows, Columns, Type> const& inner) noexcept
	{
		return view<Accessor, Rows, Columns, Type>(inner);
	}
}

#endif