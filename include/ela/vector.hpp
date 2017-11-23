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

#ifndef _ELA_VECTOR_H
#define _ELA_VECTOR_H

namespace ela {
	/* A column vector.
	 */
	template <typename Type, size_t Rows>
	using column_vector = matrix<Type, Rows, 1>;

	/* A row vector.
	 */
	template <typename Type, size_t Columns>
	using row_vector = matrix<Type, 1, Columns>;
}

#endif
