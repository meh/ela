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

namespace ela { namespace expression {
	template <typename Left, typename Right>
	struct traits<multiply<Left, Right>>
	{
		public:
			typedef typename traits<Left>::type type;
			static constexpr size_t rows = traits<Left>::rows;
			static constexpr size_t columns = traits<Right>::columns;
	};

	template <typename Left, typename Right>
	class multiply : public binary<multiply<Left, Right>, Left, Right>
	{
		static_assert(traits<Left>::columns == traits<Right>::rows,
			"rows and columns don't match");

	public:
		multiply (Left const& left, Right const& right) noexcept
			: binary<multiply<Left, Right>, Left, Right>(left, right)
		{ }

		inline
		typename traits<Left>::type
		operator () (size_t row, size_t column) const noexcept
		{
			typename traits<Left>::type scalar = 0;

			for (size_t i = 0; i < traits<Left>::columns; i++) {
				scalar += this->_left(row, i) * this->_right(i, column);
			}

			return scalar;
		}
	};
} }

#endif
