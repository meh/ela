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

#ifndef _ELA_ADD_MUL_H
#define _ELA_ADD_MUL_H

namespace ela { namespace expr {
	template <typename Left, typename Right>
	class add : public binary_expression<Left, Right>,
	            public expression_traits<Left::columns, Left::rows, typename Left::type>
	{
		static_assert(Left::columns == Right::columns && Left::rows == Right::rows,
			"rows and columns don't match");

	public:
		typedef expression_traits<Left::columns, Left::rows, typename Left::type> traits;

	public:
		add (Left const& left, Right const& right) noexcept
			: binary_expression<Left, Right>(left, right)
		{ }

		typename traits::type
		operator () (size_t row, size_t column) const noexcept
		{
			return this->_left(row, column) + this->_right(row, column);
		}
	};
} }

#endif
