#include <iostream>
#include <amirite>
#include <ela/ela.hpp>

template <typename Type>
struct __attribute__ ((packed)) RGB: ela::expression::base<RGB<Type>>
{
public:
	Type r = 0;
	Type g = 0;
	Type b = 0;

	RGB (Type r, Type g, Type b)
		: r(r), g(g), b(b)
	{ }

	template <typename Expr, typename T = Type>
	RGB (Expr const& expr, typename std::enable_if<
		3 == ela::expression::traits<Expr>::rows &&
		1 == ela::expression::traits<Expr>::columns &&
		std::is_same<T, typename ela::expression::traits<Expr>::type>::value>::type* = 0) noexcept
	{
		*this = expr;
	}

	template <typename Expr, typename T = Type>
	inline
	typename std::enable_if<3 == ela::expression::traits<Expr>::rows &&
	                        1 == ela::expression::traits<Expr>::columns &&
	                        std::is_same<T, typename ela::expression::traits<Expr>::type>::value,
	RGB<Type>&>::type
	operator = (Expr const& expr) noexcept
	{
		r = expr(0, 0);
		g = expr(1, 0);
		b = expr(2, 0);

		return *this;
	}

	inline
	Type const&
	operator () (size_t row, size_t column) const noexcept
	{
		assert(row < 3 && column == 0);

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

template <typename Type>
struct ela::expression::traits<RGB<Type>>
{
	typedef Type type;
	static constexpr size_t rows = 3;
	static constexpr size_t columns = 1;
};

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
