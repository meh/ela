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

#ifndef ELA_VECTOR_H
#define ELA_VECTOR_H

namespace ela {
	/* A column vector.
	 */
	template <typename Type, size_t Rows>
	using column_vector = matrix<Type, Rows, 1>;

	/* A row vector.
	 */
	template <typename Type, size_t Columns>
	using row_vector = matrix<Type, 1, Columns>;

	namespace expression {
		template <typename Input>
		struct traits<vector<Input, for_column<Input>>>
		{
			typedef typename traits<Input>::type type;
			static constexpr size_t rows = traits<Input>::rows;
			static constexpr size_t columns = 1;
			static constexpr bool concrete = traits<Input>::concrete;
		};
	}

	template <typename Input, bool Concrete>
	class for_column
	{ };

	template <typename Input>
	class for_column<Input, false>
	{
		static constexpr size_t elements = expression::traits<Input>::rows;
		static constexpr size_t rows = expression::traits<Input>::rows;
		static constexpr size_t columns = 1;

	public:
		for_column (size_t column) noexcept
			: _column(column)
		{
			ELA_ASSUME(column < expression::traits<Input>::columns);
		}

		inline
		typename expression::traits<Input>::type
		get (Input const& input, size_t index) const noexcept
		{
			ELA_ASSUME(index < expression::traits<Input>::rows);

			return input(index, _column);
		}

		inline
		typename expression::traits<Input>::type
		get (Input const& input, size_t row, size_t column) const noexcept
		{
			ELA_ASSUME(column == 0);

			return get(input, row);
		}

	private:
		size_t _column;
	};

	template <typename Input>
	class for_column<Input, true>
	{
	public:
		static constexpr size_t elements = expression::traits<Input>::rows;
		static constexpr size_t rows = expression::traits<Input>::rows;
		static constexpr size_t columns = 1;

	public:
		for_column (size_t column) noexcept
			: _column(column)
		{
			ELA_ASSUME(column < expression::traits<Input>::columns);
		}

		inline
		typename expression::traits<Input>::type const&
		get (Input const& input, size_t index) const noexcept
		{
			ELA_ASSUME(index < expression::traits<Input>::rows);

			return input(index, _column);
		}

		inline
		typename expression::traits<Input>::type&
		get (Input& input, size_t index) noexcept
		{
			ELA_ASSUME(index < expression::traits<Input>::rows);

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

	namespace expression {
		template <typename Input>
		struct traits<vector<Input, for_row<Input>>>
		{
			typedef typename traits<Input>::type type;
			static constexpr size_t rows = 1;
			static constexpr size_t columns = traits<Input>::columns;
			static constexpr bool concrete = traits<Input>::concrete;
		};
	}

	template <typename Input, bool Concrete>
	class for_row
	{ };

	template <typename Input>
	class for_row<Input, false>
	{
	public:
		static constexpr size_t elements = expression::traits<Input>::columns;
		static constexpr size_t rows = 1;
		static constexpr size_t columns = expression::traits<Input>::columns;

	public:
		for_row (size_t row) noexcept
			: _row(row)
		{
			ELA_ASSUME(row < expression::traits<Input>::rows);
		}

		inline
		typename expression::traits<Input>::type
		get (Input const& input, size_t index) const noexcept
		{
			ELA_ASSUME(index < expression::traits<Input>::columns);

			return input(_row, index);
		}

		inline
		typename expression::traits<Input>::type
		get (Input const& input, size_t row, size_t column) const noexcept
		{
			ELA_ASSUME(row == 0);

			return get(input, column);
		}

	private:
		size_t _row;
	};

	template <typename Input>
	class for_row<Input, true>
	{
	public:
		static constexpr size_t elements = expression::traits<Input>::columns;
		static constexpr size_t rows = 1;
		static constexpr size_t columns = expression::traits<Input>::columns;

	public:
		for_row (size_t row) noexcept
			: _row(row)
		{
			ELA_ASSUME(row < expression::traits<Input>::rows);
		}

		inline
		typename expression::traits<Input>::type const&
		get (Input const& input, size_t index) const noexcept
		{
			ELA_ASSUME(index < expression::traits<Input>::columns);

			return input(_row, index);
		}

		inline
		typename expression::traits<Input>::type&
		get (Input& input, size_t index) noexcept
		{
			ELA_ASSUME(index < expression::traits<Input>::columns);

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
	class vector<Input, Accessor, false>: public expression::base<vector<Input, Accessor>>
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
		typename expression::traits<Input>::type
		operator () (size_t row, size_t column) const noexcept
		{
			return _accessor.get(_input, row, column);
		}

	private:
		Input const& _input;
		Accessor     _accessor;
	};

	template <typename Input, typename Accessor>
	class vector<Input, Accessor, true>: public expression::base<vector<Input, Accessor>>
	{
	public:
		using expression::base<vector<Input, Accessor>>::operator =;

	public:
		/* Create a new mutable vector view.
		 */
		vector (Input& input, size_t index) noexcept
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

		/* Access a scalar at the given row and column.
		 */
		inline
		typename expression::traits<Input>::type&
		operator () (size_t row, size_t column) noexcept
		{
			return _accessor.get(_input, row, column);
		}

	private:
		Input&   _input;
		Accessor _accessor;
	};
}

#endif
