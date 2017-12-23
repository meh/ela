#include <iostream>
#include <amirite>
#include <ela/ela.hpp>

int
main (void)
{
	return amirite("vector", {
		{"zero", []{
			ela::column_vector<float, 3> vec;

			amiequal(vec[0], 0);
			amiequal(vec[1], 0);
			amiequal(vec[2], 0);
		}},

		{"view", []{
			ela::matrix<float, 3, 3> a{{1, 0, 3}, {4, 0, 6}, {7, 0, 9}};
			a.column(1) = a.column(0) + a.column(2);

			ela::column_vector<float, 3> b{1, 2, 3};
			ela::column_vector<float, 3> c = b + a.column(1);

			amiequal(5, c[0]);
			amiequal(12, c[1]);
			amiequal(19, c[2]);
		}},

		{"view (expr)", []{
			ela::matrix<float, 3, 3> a{{1, 0, 3}, {4, 0, 6}, {7, 0, 9}};

			amiequal(2, (a * 2).column(0)[0]);
		}},
	});
}
