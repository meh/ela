#include <iostream>
#include <amirite>
#include <ela/ela.hpp>
#include <ela/util.hpp>

int
main (void)
{
	return amirite("expr", {
		{"add", []{
			ela::column_vector<float, 3> a = { 1, 1, 1 };
			ela::column_vector<float, 3> b = { 2, 2, 2 };
			ela::column_vector<float, 3> c = { 3, 3, 3 };
			ela::column_vector<float, 3> d = { 4, 4, 4 };
			ela::column_vector<float, 3> o = (a + b) + (c + d);

			amiequal(o[0], 10);
			amiequal(o[1], 10);
			amiequal(o[2], 10);
		}},

		{"subtract", []{
			ela::column_vector<float, 3> a = { 1, 1, 1 };
			ela::column_vector<float, 3> b = { 2, 2, 2 };
			ela::column_vector<float, 3> c = { 3, 3, 3 };
			ela::column_vector<float, 3> d = { 4, 4, 4 };
			ela::column_vector<float, 3> o = (a + b) - (c + d);

			amiequal(o[0], -4);
			amiequal(o[1], -4);
			amiequal(o[2], -4);
		}},

		{"multiply", []{
			ela::matrix<float, 3, 3> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
			ela::column_vector<float, 3> b = {2, 2, 2};
			ela::column_vector<float, 3> c = a * b;

			amiequal(c[0], 12);
			amiequal(c[1], 30);
			amiequal(c[2], 48);
		}},

		{"transpose", []{
			ela::column_vector<float, 3> a = { 1, 2, 3 };
			ela::row_vector<float, 3> b = ~a;

			amiequal(a[0], b[0]);
			amiequal(a[1], b[1]);
			amiequal(a[2], b[2]);
		}},

		{"transpose (mutable)", []{
			ela::matrix<float, 3> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

			amiequal(a(0, 2), 3);
			(~a)(2, 0) = 42;
			amiequal(a(0, 2), 42);
		}},
	});
}

