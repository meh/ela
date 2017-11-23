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

namespace ela {
	class expression;

	template <typename Type, size_t Rows, size_t Columns>
	struct expression_traits;

	template <typename Input>
	class unary_expression;

	template <typename Left, typename Right>
	class binary_expression;

	template <typename Type, size_t Rows, size_t Columns>
	class matrix;

	namespace expr {
		template <typename Left, typename Right>
		class add;

		template <typename Left, typename Right>
		class sub;

		template <typename Left, typename Right>
		class mul;
	}
}
