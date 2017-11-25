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

#ifndef _ELA_EXPRESSION_TRANSPOSE_H
#define _ELA_EXPRESSION_TRANSPOSE_H

namespace ela { namespace expression {
	template <typename Input>
	struct traits<transpose<Input>>
	{
		typedef typename traits<Input>::type type;
		static constexpr size_t rows = traits<Input>::columns;
		static constexpr size_t columns = traits<Input>::rows;
	};

	template <typename Input>
	class transpose : public unary<transpose<Input>, Input>
	{
	public:
		transpose (Input const& input) noexcept
			: unary<transpose<Input>, Input>(input)
		{ }

		inline
		typename traits<Input>::type
		operator () (size_t row, size_t column) const noexcept
		{
			assume(row <= traits<Input>::columns && column <= traits<Input>::rows);

			return this->_input(column, row);
		}
	};
} }

#endif
