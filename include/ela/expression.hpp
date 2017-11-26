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

namespace ela { namespace expression {
	template <typename Expr>
	struct traits
	{
		typedef void type;
		static constexpr size_t rows = 1;
		static constexpr size_t columns = 1;
	};

	/* Base expression type.
	 */
	template <typename Expr>
	class base
	{
	public:
		/* Create an addition expression.
		 */
		template <typename Right>
		inline
		add<Expr, Right>
		operator + (Right const& other) const noexcept
		{
			return add<Expr, Right>(static_cast<Expr const&>(*this), other);
		}

		/* Create a subtraction expression.
		 */
		template <typename Right>
		inline
		subtract<Expr, Right>
		operator - (Right const& other) const noexcept
		{
			return subtract<Expr, Right>(static_cast<Expr const&>(*this), other);
		}

		/* Create a multiplication expression.
		 */
		template <typename Right>
		inline
		typename std::enable_if<!std::is_same<typename traits<Right>::type, void>::value,
		multiply<Expr, Right>>::type
		operator * (Right const& other) const noexcept
		{
			return multiply<Expr, Right>(static_cast<Expr const&>(*this), other);
		}

		/* Create a multiplication expression.
		 */
		inline
		scale<Expr>
		operator * (typename traits<Expr>::type value) const noexcept
		{
			return scale<Expr>(static_cast<Expr const&>(*this), value);
		}

		/* Create a transpose expression.
		 */
		inline
		transpose<Expr>
		operator ~ () const noexcept
		{
			return transpose<Expr>(static_cast<Expr const&>(*this));
		}

		/* Create an inversion expression.
		 */
		inline
		invert<Expr>
		operator ! () const noexcept
		{
			return invert<Expr>(static_cast<Expr const&>(*this));
		}

		template <typename Right>
		inline
		bool
		operator == (Right const& other) const noexcept
		{
			if (traits<Expr>::rows != traits<Right>::rows || traits<Expr>::columns != traits<Right>::columns) {
				return false;
			}

			for (size_t row = 0; row < traits<Expr>::rows; row++) {
				for (size_t column = 0; column < traits<Expr>::columns; column++) {
					if (static_cast<Expr const&>(*this)(row, column) != other(row, column)) {
						return false;
					}
				}
			}

			return true;
		}

		template <typename Right>
		inline
		bool
		operator != (Right const& other) const noexcept
		{
			return !(*this == other);
		}
	};

	/* Unary expressions.
	 */
	template <typename Expr, typename Input>
	class unary: public base<Expr>
	{
	public:
		typedef Input input;

	protected:
		unary (Input const& input) noexcept
			: _input(input)
		{ }

	protected:
		Input const& _input;
	};

	/* Binary expressions.
	 */
	template <typename Expr, typename Left, typename Right>
	class binary: public base<Expr>
	{
		static_assert(std::is_same<typename traits<Left>::type, typename traits<Right>::type>::value,
			"type mismatch");

	public:
		typedef Left  left;
		typedef Right right;

	protected:
		binary (Left const& left, Right const& right) noexcept
			: _left(left), _right(right)
		{ }

	protected:
		Left const&  _left;
		Right const& _right;
	};
} }

/* Binary expressions.
 */
#include "expression/add.hpp"
#include "expression/subtract.hpp"
#include "expression/multiply.hpp"
#include "expression/scale.hpp"

/* Unary expressions.
 */
#include "expression/transpose.hpp"
#include "expression/invert.hpp"

#endif
