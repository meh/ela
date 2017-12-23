Embedded Linear Algebra [![License](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT) [![Build Status](https://travis-ci.org/1aim/ela.svg?branch=master)](https://travis-ci.org/1aim/ela)
=======================
Minimal header only linear algebra library with expression templates and low
footprint designed to run on embedded devices.

Matrix
======
A `matrix` is generic over the scalar type, the number of rows and the number
of columns, dynamically sized matrices are not supported.

The internal buffer is always allocated on the stack as a contiguous
row-major array and by default is set to `0`.

Vector
======
There are three classes of vectors, two concrete and one as a view.

Column Vector
-------------
A `column_vector<Type, Size>` is just a type alias for `matrix<Type, Size, 1>`
but in addition to expression access it implements direct access through the
`[]` operator.

Row Vector
----------
A `row_vector<Type, Size>` is just a type alias for `matrix<Type, 1, Size>` but
in addition to expression access it implements direct access through the `[]`
operator.

Vector
------
A `vector` is a column or row vector view into an expression (or matrix if
mutable access is required).

### Example

```cpp
ela::matrix<float, 3, 3> a{{1, 0, 3}, {4, 0, 6}, {7, 0, 9}};

// Assign a column of a matrix.
a.column(1) = {2, 5, 8};

// Scale a row of the matrix and save it as a column vector.
ela::column_vector<float, 3> b = ~(a.row(1) * 2);
```

Bound checking
--------------
Bound checks are used at any runtime indexing operation through a call to
`ELA_ASSUME`.

Unless `ELA_ASSUME` is defined before `ela/ela.hpp` is included its definition
will become an `assert` call when `NDEBUG` is not defined and a compiler
unreachable hint when `NDEBUG` is defined.

In your custom expression implementations you're advised to call `ELA_ASSUME`
yourself to make sure the compiler knows what's going on.

Expression
==========
All matrix operations are implemented as expression templates so no
intermediary objects are created unless explictly assigned to a `matrix`.

If all your matrix values are known at compile time compilers are able to
completely constant unfold the results most of the time.

What is an `expression`?
------------------------
An `expression` is any type that implements the `ela::expression::traits` and
provides the appropriate indexing operator.

### Example

We'll implement a generic RGB type as if it were a column vector.

```cpp
/* Inheriting from `ela::expression::base` is not required but it automatically
 * implements all generic expression operators for free, it doesn't add any
 * data.
 */
template <typename Type>
struct RGB: public ela::expression::base<RGB<Type>>
{
public:
	using ela::expression::base<RGB<Type>>::operator =;

public:
	Type r = 0;
	Type g = 0;
	Type b = 0;

	/* Create an empty color.
	 */
	RGB () noexcept
	{ }

	RGB (Type r, Type g, Type b) noexcept
		: r(r), g(g), b(b)
	{ }

	template <typename Input, typename T = Type>
	RGB (Input const& expr, typename std::enable_if<
		3 == ela::expression::traits<Input>::rows &&
		1 == ela::expression::traits<Input>::columns &&
		std::is_same<T, typename ela::expression::traits<Input>::type>::value>::type* = 0) noexcept
	{
		ela::expression::base<RGB<Type>>::operator=(expr);
	}

	RGB (std::initializer_list<std::initializer_list<Type>> elements) noexcept
	{
		ela::expression::base<RGB<Type>>::operator=(elements);
	}

	RGB (std::initializer_list<Type> elements) noexcept
	{
		ela::expression::base<RGB<Type>>::operator=(elements);
	}

	/* This is the expression access operator.
	 */
	inline
	Type const&
	operator () (size_t row, size_t column) const noexcept
	{
		ELA_ASSUME(row < 3 && column == 0);

		if (row == 0) {
			return r;
		}
		else if (row == 1) {
			return g;
		}
		else {
			return b;
		}
	}

	/* This is the expression access operator.
	 */
	inline
	Type&
	operator () (size_t row, size_t column) noexcept
	{
		ELA_ASSUME(row < 3 && column == 0);

		if (row == 0) {
			return r;
		}
		else if (row == 1) {
			return g;
		}
		else {
			return b;
		}
	}
};

namespace ela { namespace expression {
	/* This defines the experssion traits for `RGB<T>`.
	 */
	template <typename Type>
	struct traits<RGB<Type>>
	{
		/* This is always the scalar type.
		 */
		typedef Type type;

		/* This is the number of rows the expression will produce.
		 */
		static constexpr size_t rows = 3;

		/* This is the number of columns the expression will produce.
		 */
		static constexpr size_t columns = 1;

		/* This says the expression can return references.
		 */
		static constexpr bool concrete = true;
	};
} }

```

This code will make `RGB` behave as an expression, you can look into `tests/`
for more examples of expressions and other stuff.
