#include <iostream>
#include <amirite>
#include <ela/ela.hpp>

int
main (void)
{
	return amirite("matrix", {
		{"zero", []{
			ela::matrix<3, 3> mat;

			amiequal(mat(0, 0), 0);
			amiequal(mat(0, 1), 0);
			amiequal(mat(0, 2), 0);

			amiequal(mat(1, 0), 0);
			amiequal(mat(1, 1), 0);
			amiequal(mat(1, 2), 0);

			amiequal(mat(2, 0), 0);
			amiequal(mat(2, 1), 0);
			amiequal(mat(2, 2), 0);
		}},

		{"identity", []{
			ela::matrix<3, 3> mat(1.0);

			amiequal(mat(0, 0), 1.0);
			amiequal(mat(1, 1), 1.0);
			amiequal(mat(2, 2), 1.0);
		}},

		{"multiply", []{
			ela::matrix<3, 3> a({ { 1.0, 2.0, 3.0 }, { 4.0, 5.0, 6.0 }, { 7.0, 8.0, 9.0 } });
			ela::matrix<3, 3> b(2.0);
			ela::matrix<3, 3> c = a * b;

			amiequal(c(0, 0), 2.0);
			amiequal(c(0, 1), 4.0);
			amiequal(c(0, 2), 6.0);

			amiequal(c(1, 0), 8.0);
			amiequal(c(1, 1), 10.0);
			amiequal(c(1, 2), 12.0);

			amiequal(c(2, 0), 14.0);
			amiequal(c(2, 1), 16.0);
			amiequal(c(2, 2), 18.0);
		}},
	});
}
