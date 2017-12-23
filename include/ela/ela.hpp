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

#if defined(_MSVC_VER)
#	define _ELA_ASSUME(e) __assume(e)
#else
#	define _ELA_ASSUME(e) if (!(e)) { __builtin_unreachable(); }
#endif

#if !defined(ELA_ASSUME)
# if defined(NDEBUG)
#		define ELA_ASSUME(e) _ELA_ASSUME(e)
#	else
#		define ELA_ASSUME(e) assert(e)
# endif
#endif

namespace ela {
	namespace expression {
		template <typename Expr>
		struct traits;

		template <typename Self, bool Concrete = expression::traits<Self>::concrete>
		struct base;

		namespace derive {
			template <typename Self>
			struct operators;

			template <typename Self, bool Concrete = traits<Self>::concrete>
			struct vectors;

			template <typename Self, bool Concrete = traits<Self>::concrete>
			struct accessors;

			template <typename Self, bool Concrete = traits<Self>::concrete>
			struct assignment;
		}

		template <typename Self, typename Input>
		class unary;

		template <typename Self, typename Left, typename Right>
		class binary;

		template <typename Left, typename Right>
		class add;

		template <typename Left, typename Right>
		class subtract;

		template <typename Left, typename Right>
		class multiply;

		template <typename Input>
		class scale;

		template <typename Input, bool Concrete = traits<Input>::concrete>
		class transpose;

		template <typename Input, size_t Dimension>
		struct inversion;

		template <typename Input>
		class invert;
	}

	template <typename Type, size_t Rows, size_t Columns = Rows>
	class matrix;

	template <typename Input, bool Concrete = expression::traits<Input>::concrete>
	class for_column;

	template <typename Input, bool Concrete = expression::traits<Input>::concrete>
	class for_row;

	template <typename Expr, typename Accessor, bool Concrete = expression::traits<Expr>::concrete>
	class vector;

	template <typename Expr>
	struct is_expr
	{
		static constexpr bool value =
			!std::is_void<typename expression::traits<Expr>::type>::value;
	};
}

#include "expression.hpp"
#include "matrix.hpp"
#include "vector.hpp"

#undef assume
#endif
