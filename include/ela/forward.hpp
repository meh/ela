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

namespace ela {
	namespace order {
		struct row_major;
		struct column_major;
	}

	namespace marker {
		template <bool Value>
		struct concrete : public std::integral_constant<bool, Value>
		{ };

		template <bool Value>
		struct owned : public std::integral_constant<bool, Value>
		{ };
	}

	namespace expression {
		template <typename Expr>
		struct traits;

		template <typename Self, typename Concrete = marker::concrete<expression::traits<Self>::concrete>>
		struct base;

		namespace derive {
			template <typename Self>
			struct operators;

			template <typename Self, typename Concrete = marker::concrete<traits<Self>::concrete>>
			struct vectors;

			template <typename Self, typename Concrete = marker::concrete<traits<Self>::concrete>>
			struct iterators;

			template <typename Self, typename Concrete = marker::concrete<traits<Self>::concrete>>
			struct accessors;

			template <typename Self, typename Concrete = marker::concrete<traits<Self>::concrete>>
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

		namespace scalar {
			template <typename Input>
			class multiply;

			template <typename Input>
			class divide;
		}

		template <typename Self, typename Concrete = marker::concrete<traits<Self>::concrete>>
		class transpose;

		template <typename Input, size_t Dimension>
		struct inversion;

		template <typename Input>
		class invert;
	}

	namespace iterator {
		using row_major = order::row_major;
		using column_major = order::row_major;

		template <typename Expr, typename Iterator, typename ConstIterator = Iterator>
		class wrapper;

		template <typename Self, typename Order = order::row_major, typename Concrete = marker::concrete<expression::traits<Self>::concrete>>
		class elements;

		template <typename Self, typename Concrete = marker::concrete<expression::traits<Self>::concrete>>
		class rows;

		template <typename Self, typename Concrete = marker::concrete<expression::traits<Self>::concrete>>
		class columns;
	}

	namespace storage {
		using row_major = order::row_major;
		using column_major = order::row_major;

		template <typename Impl, typename Order = order::row_major>
		struct specifier;

		template <typename Specifier, typename Type, size_t Size>
		class impl;

		struct pointer;
		struct stack;
		struct heap;

		template <template <typename> class Allocator = std::allocator>
		struct allocator;

		template <typename Duck>
		struct duck;
	}

	template <typename Type, size_t Rows, size_t Columns = Rows,
		typename Storage = storage::specifier<storage::stack, order::row_major>,
		typename Owned = marker::owned<std::is_default_constructible<storage::impl<Storage, Type, Rows * Columns>>::value>>
	class matrix;

	template <typename Input>
	class for_column;

	template <typename Input>
	class for_row;

	template <typename Expr, typename Accessor, typename Concrete = marker::concrete<expression::traits<Expr>::concrete>>
	class vector;
}
