#include <iostream>
#include <amirite>
#include <ela/ela.hpp>

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

int
main (void)
{
	return amirite("custom", {
		{"access", []{
			RGB<float> a(1.0, 0.5, 0.0);

			amiequal(1.0, a[0]);
			amiequal(0.5, a[1]);
			amiequal(0.0, a[2]);
		}},

		{"assign", []{
			ela::column_vector<float, 3> a { 1.0, 0.5, 0.0 };
			RGB<float> b = a * 2;

			amiequal(2.0, b[0]);
			amiequal(1.0, b[1]);
			amiequal(0.0, b[2]);
		}},
	});
}
