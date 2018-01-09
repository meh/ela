#include <iostream>
#include <amirite>
#include <ela/ela.hpp>
#include <ela/util.hpp>

int
main (void)
{
	return amirite("storage", {
		{"equal", []{
			ela::column_vector<float, 3> a = {1, 2, 3};

			ela::column_vector<float, 3,
				ela::storage::specifier<ela::storage::heap>> b = {1, 2, 3};

			ela::column_vector<float, 3,
				ela::storage::specifier<ela::storage::pointer>> c = a;

			ela::column_vector<float, 3,
				ela::storage::specifier<ela::storage::pointer>> d = b;

			amiequal(a, b);
			amiequal(a, c);
			amiequal(a, d);
			amiequal(b, c);
			amiequal(c, d);
		}},

		{"allocator", []{
			ela::column_vector<float, 3,
				ela::storage::specifier<ela::storage::allocator<std::allocator>>> a = {1, 2, 3};

			amiequal(a[0], 1);
			amiequal(a[1], 2);
			amiequal(a[2], 3);
		}},
	});
}
