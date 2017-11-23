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

#ifndef _ELA_EXPR_MUL_H
#define _ELA_EXPR_MUL_H

namespace ela { namespace expr {
	template <typename Left, typename Right>
	class mul : public binary_expression<Left, Right>,
	            public expression_traits<typename Left::type, Left::rows, Right::columns>
	{
		static_assert(Left::columns == Right::rows,
			"rows and columns don't match");

	public:
		typedef expression_traits<typename Left::type, Left::rows, Right::columns> traits;

	public:
		mul (Left const& left, Right const& right) noexcept
			: binary_expression<Left, Right>(left, right)
		{ }

		typename traits::type
		operator () (size_t row, size_t column) const noexcept
		{
			typename traits::type scalar = 0;

			for (size_t i = 0; i < Left::columns; i++) {
				scalar += this->_left(row, i) * this->_right(i, column);
			}

			return scalar;
		}
	};
} }

#endif
