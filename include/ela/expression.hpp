#ifndef _ELA_EXPRESSION_H
#define _ELA_EXPRESSION_H

#include <optional.hpp>
using std::experimental::optional;

namespace ela {
	template <typename Output>
	class expression
	{
	public:
		typedef Output output;
		typedef typename Output::type type;
	};

	template <typename Input, typename Output>
	class unary_expression: public expression<Output>
	{
		static_assert(std::is_same<typename Input::type, typename Output::type>::value,
			"type mismatch");

	public:
		typedef Input input;

	protected:
		unary_expression (Input const& input) noexcept
			: _input(input);

	protected:
		Input const& _input;
	};

	template <typename Left, typename Right, typename Output>
	class binary_expression: public expression<Output>
	{
		static_assert(std::is_same<typename Left::type, typename Right::type>::value,
			"type mismatch");

		static_assert(std::is_same<typename Output::type, typename Right::type>::value,
			"type mismatch");

	public:
		typedef Left  left;
		typedef Right right;

	protected:
		binary_expression (Left const& lhs, Right const& rhs) noexcept
			: _lhs(lhs), _rhs(rhs);

	protected:
		Left const&  _lhs;
		Right const& _rhs;
	};
}

#endif
