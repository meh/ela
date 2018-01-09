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

#ifndef ELA_MATRIX_H
#define ELA_MATRIX_H

namespace ela {
	namespace expression {
		template <typename Type, size_t Rows, size_t Columns, typename Storage>
		struct traits<matrix<Type, Rows, Columns, Storage>>
		{
			typedef Type type;
			static constexpr size_t rows = Rows;
			static constexpr size_t columns = Columns;
			static constexpr bool concrete = true;
		};
	}

	/* A matrix.
	 */
	template <typename Type, size_t Rows, size_t Columns, typename Storage>
	class matrix<Type, Rows, Columns, Storage, false>
		: public expression::base<matrix<Type, Rows, Columns, Storage, false>>
	{
	public:
		using expression::base<matrix<Type, Rows, Columns, Storage>>::operator =;

	public:
		template <typename... Args>
		matrix (Args&&... args) noexcept
			: _storage(std::forward<Args>(args)...)
		{ }

		/* Access a scalar at the given row and column.
		 */
		inline
		Type const&
		operator () (size_t row, size_t column) const noexcept
		{
			return _storage(row, column);
		}

		/* Access a scalar at the given row and column.
		 */
		inline
		Type&
		operator () (size_t row, size_t column) noexcept
		{
			return _storage(row, column);
		}

		inline
		operator Type* (void) noexcept
		{
			return _storage;
		}

		inline
		operator Type const* (void) const noexcept
		{
			return _storage;
		}

	private:
		storage::impl<Storage, Type, Rows, Columns> _storage;
	};

	template <typename Type, size_t Rows, size_t Columns, typename Storage>
	class matrix<Type, Rows, Columns, Storage, true>
		: public expression::base<matrix<Type, Rows, Columns, Storage, true>>
	{
	public:
		using expression::base<matrix<Type, Rows, Columns, Storage>>::operator =;

	public:
		/* Create an empty matrix.
		 */
		matrix () noexcept
		{ }

		matrix (Type value) noexcept
			: _storage(value)
		{ }

		template <typename Input, typename T = Type, size_t R = Rows, size_t C = Columns>
		matrix (Input const& expr, typename std::enable_if<
			R == expression::traits<Input>::rows &&
			C == expression::traits<Input>::columns &&
			std::is_same<T, typename expression::traits<Input>::type>::value>::type* = 0) noexcept
		{
			expression::base<matrix<Type, Rows, Columns, Storage>>::operator=(expr);
		}

		matrix (std::initializer_list<std::initializer_list<Type>> rows) noexcept
		{
			expression::base<matrix<Type, Rows, Columns, Storage>>::operator=(rows);
		}

		matrix (std::initializer_list<Type> elements) noexcept
		{
			expression::base<matrix<Type, Rows, Columns, Storage>>::operator=(elements);
		}

		/* Create an identity matrix with the given value.
		 */
		template <size_t R = Rows, size_t C = Columns>
		static inline
		typename std::enable_if<R == C, matrix<Type, Rows, Columns, Storage>>::type
		identity () noexcept
		{
			matrix<Type, Rows, Columns> result;

			for (size_t i = 0; i < Rows; i++) {
				result(i, i) = 1;
			}

			return result;
		}

		/* Create a scaling matrix with the given values.
		 */
		template <size_t R = Rows, size_t C = Columns>
		static inline
		typename std::enable_if<R == C && (R == 3 || R == 4), matrix<Type, Rows, Columns, Storage>>::type
		scaling (Type x, Type y, Type z) noexcept
		{
			auto result = identity();

			result(0, 0) = x;
			result(1, 1) = y;
			result(2, 2) = z;

			return result;
		}

		/* Create an identity matrix with the given value.
		 */
		template <size_t R = Rows, size_t C = Columns>
		static inline
		typename std::enable_if<R == C && (R == 3 || R == 4), matrix<Type, Rows, Columns, Storage>>::type
		scaling (Type x) noexcept
		{
			auto result = identity();

			result(0, 0) = x;
			result(1, 1) = x;
			result(2, 2) = x;

			return result;
		}

		/* Access a scalar at the given row and column.
		 */
		inline
		Type const&
		operator () (size_t row, size_t column) const noexcept
		{
			return _storage(row, column);
		}

		/* Access a scalar at the given row and column.
		 */
		inline
		Type&
		operator () (size_t row, size_t column) noexcept
		{
			return _storage(row, column);
		}

		inline
		operator Type* (void) noexcept
		{
			return _storage;
		}

		inline
		operator Type const* (void) const noexcept
		{
			return _storage;
		}

	private:
		storage::impl<Storage, Type, Rows, Columns> _storage;
	};

	/* A column vector.
	 */
	template <typename Type, size_t Rows,
	typename Storage = storage::specifier<storage::stack, storage::row_major>,
	bool Owned = std::is_default_constructible<storage::impl<Storage, Type, Rows, 1>>::value>
	using column_vector = matrix<Type, Rows, 1, Storage, Owned>;

	/* A row vector.
	 */
	template <typename Type, size_t Columns,
	typename Storage = storage::specifier<storage::stack, storage::row_major>,
	bool Owned = std::is_default_constructible<storage::impl<Storage, Type, 1, Columns>>::value>
	using row_vector = matrix<Type, 1, Columns>;
}

#endif
