#include <iostream>
#include <amirite>
#include <matrix.hpp>

int
main (void)
{
	return amirite("matrix", {
		{"zero", []{
			meh::matrix<3, 3> mat;

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
			meh::matrix<3, 3> mat(1.0);

			amiequal(mat(0, 0), 1.0);
			amiequal(mat(1, 1), 1.0);
			amiequal(mat(2, 2), 1.0);
		}},
	});
}
