Embedded Linear Algebra [![License](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT) [![Build Status](https://travis-ci.org/1aim/ela.svg?branch=master)](https://travis-ci.org/1aim/ela)
=======================
Minimal header only linear algebra library with expression templates and low
footprint designed to run on embedded devices.

Matrix
------
A `matrix` is generic over the scalar type, the number of rows and the number
of columns, dynamically sized matrices are not supported.

The internal buffer is always allocated on the stack as a contiguous
column-major array and by default is set to `0`.

Expression
----------
All matrix operations are implemented as expression templates so no
intermediary objects are created unless explictly assigned to a `matrix`.

If all your matrix values are known at compile time compilers are able to
completely constant unfold the results most of the time.

Examples
========
```cpp
#include <iostream>
#include <ela/ela.hpp>

int
main (void)
{
	ela::matrix<float, 3, 3> a = {
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 9 } };

	ela::matrix<float, 3, 3> b = {
		{ 9, 8, 7 },
		{ 6, 5, 4 },
		{ 3, 2, 1 } };

  // Store the result for future usage without having to recalculate anything.
	ela::matrix<float, 3, 3> c = ((a * b) * 3) + ~b;

	std::cout << c(0, 0) << "\t" << c(0, 1) << "\t" << c(0, 2) << std::endl; //  99  78  57
	std::cout << c(1, 0) << "\t" << c(1, 1) << "\t" << c(1, 2) << std::endl; // 260 212 164
	std::cout << c(2, 0) << "\t" << c(2, 1) << "\t" << c(2, 2) << std::endl; // 421 346 271
}
```
