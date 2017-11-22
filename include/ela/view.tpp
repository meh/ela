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

namespace ela {
	template <typename Accessor, size_t Columns, size_t Rows, typename Type>
	view<Accessor, Columns, Rows, Type>::view (matrix<Columns, Rows, Type> const& inner) noexcept
		: _inner(inner)
	{ }

	template <typename Accessor, size_t Columns, size_t Rows, typename Type>
	Type const&
	view<Accessor, Columns, Rows, Type>::operator [] (size_t index) const noexcept
	{
		return Accessor::get(_inner, index);
	}
}
