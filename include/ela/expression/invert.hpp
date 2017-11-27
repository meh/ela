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

#ifndef _ELA_EXPRESSION_INVERT_H
#define _ELA_EXPRESSION_INVERT_H

namespace ela { namespace expression {
	template <typename Input>
	struct traits<invert<Input>>
	{
		typedef typename traits<Input>::type type;
		static constexpr size_t rows = traits<Input>::rows;
		static constexpr size_t columns = traits<Input>::columns;
	};

	/* Matrix inversion implementations for various matrix dimensions.
	 */
	template <typename Input, size_t Dimension>
	struct inversion
	{
		static_assert(traits<Input>::rows == traits<Input>::columns,
			"only square matrices are invertible");

		static_assert(traits<Input>::rows == Dimension,
			"input and inversion dimensions do not match");

		static_assert(std::numeric_limits<typename traits<Input>::type>::has_quiet_NaN,
			"the type must support NaN");

		/* Calculate the determinant.
		 */
		static inline
		typename traits<Input>::type
		determinant (Input const& input) noexcept;

		/* Access the scalar for the given index.
		 */
		static inline
		typename traits<Input>::type
		get (Input const& input, size_t row, size_t column) noexcept;
	};

	/* Inversion expression.
	 */
	template <typename Input>
	class invert : public unary<invert<Input>, Input>
	{
		static_assert(traits<Input>::rows == traits<Input>::columns,
			"only square matrices are invertible");

	public:
		/* Create a new scaling expression.
		 */
		invert (Input const& input) noexcept
			: unary<invert<Input>, Input>(input)
		{
			_determinant = inversion<Input, traits<Input>::rows>::determinant(input);

			if (_determinant == 0) {
				_determinant = std::numeric_limits<typename traits<Input>::type>::quiet_NaN();
			}
		}

		/* Check whether the expression is invertible or not.
		 */
		inline
		operator bool () const noexcept
		{
			return !std::isnan(_determinant);
		}

		/* Access the inverted scalar at the given index.
		 */
		inline
		typename traits<Input>::type
		operator () (size_t row, size_t column) const noexcept
		{
			assume(row <= traits<Input>::rows && column <= traits<Input>::columns);

			if (std::isnan(_determinant)) {
				return _determinant;
			}

			return (1 / _determinant) * inversion<Input, traits<Input>::rows>::get(this->_input, row, column);
		}

	private:
		typename traits<Input>::type _determinant = 0;
	};

	template <typename Input>
	struct inversion<Input, 2>
	{
		static inline
		typename traits<Input>::type
		determinant (Input const& input) noexcept
		{
			typename traits<Input>::type
				a = input(0, 0),
				b = input(0, 1),
				c = input(1, 0),
				d = input(1, 1);

			return (a * d) - (b * c);
		}

		static inline
		typename traits<Input>::type
		get (Input const& input, size_t row, size_t column) noexcept
		{
			assume(row <= 1 && column <= 1);

			#define a input(0, 0)
			#define b input(0, 1)
			#define c input(1, 0)
			#define d input(1, 1)

			if (row == 0) {
				if (column == 0) {
					return d;
				}
				else {
					return -b;
				}
			}
			else {
				if (column == 0) {
					return -c;
				}
				else {
					return a;
				}
			}

			#undef a
			#undef b
			#undef c
			#undef d
		}
	};

	template <typename Input>
	struct inversion<Input, 3>
	{
		static inline
		typename traits<Input>::type
		determinant (Input const& input) noexcept
		{
			typename traits<Input>::type
				a = input(0, 0),
				b = input(0, 1),
				c = input(0, 2),
				d = input(1, 0),
				e = input(1, 1),
				f = input(1, 2),
				g = input(2, 0),
				h = input(2, 1),
				i = input(2, 2);

			return (a * e * i) - (a * f * h) -
			       (b * i * d) + (b * f * g) +
			       (c * d * h) - (c * e * g);
		}

		static inline
		typename traits<Input>::type
		get (Input const& input, size_t row, size_t column) noexcept
		{
			assume(row <= 2 && column <= 2);

			#define a input(0, 0)
			#define b input(0, 1)
			#define c input(0, 2)
			#define d input(1, 0)
			#define e input(1, 1)
			#define f input(1, 2)
			#define g input(2, 0)
			#define h input(2, 1)
			#define i input(2, 2)

			if (row == 0) {
				if (column == 0) {
					return (e * i) - (f * h);
				}
				else if (column == 1) {
					return (f * g) - (d * i);
				}
				else {
					return (d * h) - (e * g);
				}
			}
			else if (row == 1) {
				if (column == 0) {
					return (c * h) - (b * i);
				}
				else if (column == 1) {
					return (a * i) - (c * g);
				}
				else {
					return (g * b) - (a * h);
				}
			}
			else {
				if (column == 0) {
					return (b * f) - (c * e);
				}
				else if (column == 1) {
					return (c * d) - (a * f);
				}
				else {
					return (a * e) - (b * d);
				}
			}

			#undef a
			#undef b
			#undef c
			#undef d
			#undef e
			#undef f
			#undef g
			#undef h
			#undef i
		}
	};
} }

#endif
