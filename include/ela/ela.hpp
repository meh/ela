// Copyright (c) 2017 1aim GmbH
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is furnished to do
// so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef _ELA_H
#define _ELA_H

#include <algorithm>
#include <initializer_list>
#include <cmath>
#include <cassert>

#ifdef ELA_NO_ASSUMPTIONS
#	define assume(predicate) { \
		assert(predicate); \
	}
#else
#	define assume(predicate) { \
		assert(predicate); \
			if (!(predicate)) { \
				__builtin_unreachable(); \
			} \
		}
#endif

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

	template <typename Input>
	class for_column;

	template <typename Input>
	class for_row;

	template <typename Expr, typename Accessor>
	class vector;
}

#include "expression.hpp"
#include "matrix.hpp"
#include "vector.hpp"

#undef assume
#endif
