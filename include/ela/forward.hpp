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

#ifndef _ELA_FORWARD_H
#define _ELA_FORWARD_H

#include <algorithm>
#include <initializer_list>
#include <cmath>
#include <cassert>

namespace ela {
	namespace expression {
		template <typename Expr>
		struct traits;

		template <typename Expr>
		class base;

		template <typename Expr, typename Input>
		class unary;

		template <typename Expr, typename Left, typename Right>
		class binary;

		template <typename Left, typename Right>
		class add;

		template <typename Left, typename Right>
		class subtract;

		template <typename Left, typename Right>
		class multiply;

		template <typename Input>
		class scale;

		template <typename Input>
		class transpose;

		template <typename Input, size_t Dimension>
		struct inversion;

		template <typename Input>
		class invert;
	}

	template <typename Type, size_t Rows, size_t Columns>
	class matrix;
}

#endif
