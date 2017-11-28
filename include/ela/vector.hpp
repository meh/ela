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

	template <typename Input>
	struct expression::traits<vector<Input, for_column<Input>>>
	{
		typedef typename expression::traits<Input>::type type;
		static constexpr size_t rows = expression::traits<Input>::rows;
		static constexpr size_t columns = 1;
	};

	template <typename Input>
	class for_column
	{
	public:
		static constexpr size_t rows = expression::traits<Input>::rows;
		static constexpr size_t columns = 1;
		static constexpr size_t elements = expression::traits<Input>::rows;

	public:
		for_column (size_t column) noexcept
			: _column(column)
		{
			ELA_ASSUME(column <= expression::traits<Input>::columns);
		}

		inline
		typename expression::traits<Input>::type const&
		get (Input const& input, size_t index) const noexcept
		{
			ELA_ASSUME(index <= expression::traits<Input>::rows);

			return input(index, _column);
		}

		inline
		typename expression::traits<Input>::type&
		get (Input& input, size_t index) noexcept
		{
			ELA_ASSUME(index <= expression::traits<Input>::rows);

			return input(index, _column);
		}

		inline
		typename expression::traits<Input>::type const&
		get (Input const& input, size_t row, size_t column) const noexcept
		{
			ELA_ASSUME(column == 0);
			return get(input, row);
		}

		inline
		typename expression::traits<Input>::type&
		get (Input& input, size_t row, size_t column) noexcept
		{
			ELA_ASSUME(column == 0);
			return get(input, row);
		}

	private:
		size_t _column;
	};

	template <typename Input>
	struct expression::traits<vector<Input, for_row<Input>>>
	{
		typedef typename expression::traits<Input>::type type;
		static constexpr size_t rows = 1;
		static constexpr size_t columns = expression::traits<Input>::columns;
	};

	template <typename Input>
	class for_row
	{
	public:
		static constexpr size_t rows = 1;
		static constexpr size_t columns = expression::traits<Input>::columns;
		static constexpr size_t elements = expression::traits<Input>::columns;

	public:
		for_row (size_t row) noexcept
			: _row(row)
		{
			ELA_ASSUME(row <= expression::traits<Input>::rows);
		}

		inline
		typename expression::traits<Input>::type const&
		get (Input const& input, size_t index) const noexcept
		{
			ELA_ASSUME(index <= expression::traits<Input>::columns);

			return input(_row, index);
		}

		inline
		typename expression::traits<Input>::type&
		get (Input& input, size_t index) noexcept
		{
			ELA_ASSUME(index <= expression::traits<Input>::columns);

			return input(_row, index);
		}

		inline
		typename expression::traits<Input>::type const&
		get (Input const& input, size_t row, size_t column) const noexcept
		{
			ELA_ASSUME(row == 0);
			return get(input, column);
		}

		inline
		typename expression::traits<Input>::type&
		get (Input& input, size_t row, size_t column) noexcept
		{
			ELA_ASSUME(row == 0);
			return get(input, column);
		}

	private:
		size_t _row;
	};

	template <typename Input, typename Accessor>
	class vector: public expression::base<vector<Input, Accessor>>
	{
	public:
		/* Create a new constant vector view.
		 */
		vector (Input const& input, size_t index) noexcept
			: _input(input), _accessor(index)
		{ }

		/* Access a scalar at the given row and column.
		 */
		inline
		typename expression::traits<Input>::type const&
		operator () (size_t row, size_t column) const noexcept
		{
			return _accessor.get(_input, row, column);
		}

		/* Access a scalar at the given index.
		 */
		inline
		typename expression::traits<Input>::type const&
		operator [] (size_t index) const noexcept
		{
			return _accessor.get(_input, index);
		}

	private:
		Input const& _input;
		Accessor     _accessor;
	};

	template <typename Type, size_t Rows, size_t Columns, typename Accessor>
	class vector<matrix<Type, Rows, Columns>, Accessor>: public expression::base<vector<matrix<Type, Rows, Columns>, Accessor>>
	{
	public:
		/* Create a new mutable vector view.
		 */
		vector (matrix<Type, Rows, Columns>& input, size_t index) noexcept
			: _input(input), _accessor(index)
		{ }

		/* Copy the data present in the pointer.
		 */
		inline
		vector<matrix<Type, Rows, Columns>, Accessor>&
		operator = (const Type* data) noexcept
		{
			for (size_t i = 0; i < Accessor::elements; i++) {
				_accessor.get(_input, i) = data[i];
			}

			return *this;
		}

		/* Copy the data from the initializer list, only for vectors.
		 */
		inline
		vector<matrix<Type, Rows, Columns>, Accessor>&
		operator = (std::initializer_list<Type> elements) noexcept
		{
			ELA_ASSUME(elements.size() == Accessor::elements);

			size_t index = 0;
			for (auto element : elements) {
				_accessor.get(_input, index) = element;
				index++;
			}

			return *this;
		}

		/* Copy the data from the expression.
		 */
		template <typename Expr, typename T = Type, size_t R = Accessor::rows, size_t C = Accessor::columns>
		inline
		typename std::enable_if<R == expression::traits<Expr>::rows &&
		                        C == expression::traits<Expr>::columns &&
		                        std::is_same<T, typename expression::traits<Expr>::type>::value,
		vector<matrix<Type, Rows, Columns>, Accessor>&>::type
		operator = (Expr const& expr) noexcept
		{
			if (Rows == 1) {
				for (size_t column = 0; column < C; column++) {
					_accessor.get(_input, 0, column) = expr(0, column);
				}
			}
			else {
				for (size_t row = 0; row < R; row++) {
					_accessor.get(_input, row, 0) = expr(row, 0);
				}
			}

			return *this;
		}

		/* Access a scalar at the given row and column.
		 */
		inline
		Type const&
		operator () (size_t row, size_t column) const noexcept
		{
			return _accessor.get(_input, row, column);
		}

		/* Access a scalar at the given row and column.
		 */
		inline
		Type&
		operator () (size_t row, size_t column) noexcept
		{
			return _accessor.get(_input, row, column);
		}

		/* Access a scalar at the given index.
		 */
		inline
		Type const&
		operator [] (size_t index) const noexcept
		{
			return _accessor.get(_input, index);
		}

		/* Access a scalar at the given index.
		 */
		inline
		Type&
		operator [] (size_t index) noexcept
		{
			return _accessor.get(_input, index);
		}

	private:
		matrix<Type, Rows, Columns>& _input;
		Accessor                     _accessor;
	};
}

#endif
