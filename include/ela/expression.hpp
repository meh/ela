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

#ifndef _ELA_EXPRESSION_H
#define _ELA_EXPRESSION_H

namespace ela {
	/* Base expression type.
	 */
	class expression
	{ };

	template <size_t Columns, size_t Rows, typename Type>
	struct expression_traits
	{
	public:
		typedef Type type;
		static constexpr size_t columns = Columns;
		static constexpr size_t rows = Rows;
		static constexpr size_t bytes = Columns * Rows * sizeof(Type);
		static constexpr size_t elements = Columns * Rows;
	};

	/* Unary expressions.
	 */
	template <typename Input>
	class unary_expression: public expression
	{
	public:
		typedef Input input;

	protected:
		unary_expression (Input const& input) noexcept
			: _input(input)
		{ }

	protected:
		Input const& _input;
	};

	/* Binary expressions.
	 */
	template <typename Left, typename Right>
	class binary_expression: public expression
	{
		static_assert(std::is_same<typename Left::type, typename Right::type>::value,
			"type mismatch");

	public:
		typedef Left  left;
		typedef Right right;

	protected:
		binary_expression (Left const& left, Right const& right) noexcept
			: _left(left), _right(right)
		{ }

	protected:
		Left const&  _left;
		Right const& _right;
	};
}

#include "expr/add.hpp"
#include "expr/sub.hpp"
#include "expr/mul.hpp"

#endif
