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

#ifndef _ELA_EXPRESSION_SCALE_H
#define _ELA_EXPRESSION_SCALE_H

namespace ela { namespace expression {
	template <typename Input>
	struct traits<scale<Input>>
	{
		typedef typename traits<Input>::type type;
		static constexpr size_t rows = traits<Input>::rows;
		static constexpr size_t columns = traits<Input>::columns;
	};

	/* Scaling expression.
	 */
	template <typename Input>
	class scale : public unary<scale<Input>, Input>
	{
	public:

	public:
		/* Create a new scaling expression.
		 */
		scale (Input const& input, typename traits<Input>::type factor) noexcept
			: unary<scale<Input>, Input>(input), _factor(factor)
		{ }

		/* Access the scaled scalar at the given index.
		 */
		inline
		typename traits<Input>::type
		operator () (size_t row, size_t column) const noexcept
		{
			assume(row <= traits<Input>::rows && column <= traits<Input>::columns);

			return this->_input(row, column) * this->_factor;
		}

	private:
		typename traits<Input>::type _factor;
	};
} }

#endif
