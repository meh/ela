#include <iostream>
#include <vector>
#include <amirite>
#include <ela/ela.hpp>
#include <ela/util.hpp>

int
main (void)
{
	return amirite("storage", {
		{"stack", []{
			ela::matrix<float, 3, 3,
				ela::storage::specifier<ela::storage::stack, ela::storage::row_major>> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

			ela::matrix<float, 3, 3,
				ela::storage::specifier<ela::storage::stack, ela::storage::column_major>> b = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

			amiequal(a, b);
		}},

		{"allocator", []{
			ela::column_vector<float, 3,
				ela::storage::specifier<ela::storage::allocator<std::allocator>>> a = {1, 2, 3};

			amiequal(a[0], 1);
			amiequal(a[1], 2);
			amiequal(a[2], 3);
		}},

		{"duck", []{
			std::vector<float> data = {1.0, 2.0, 3.0};

			ela::column_vector<float, 3,
				ela::storage::specifier<ela::storage::duck<decltype(data)>>> a(data);

			amiequal(a[0], 1.0);
			amiequal(a[1], 2.0);
			amiequal(a[2], 3.0);
		}},
	});
}
