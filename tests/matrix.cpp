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
			ela::matrix<3, 3> a(1.0);
			ela::matrix<3, 3> b(2.0);
			ela::matrix<3, 3> c(3.0);
			ela::matrix<3, 3> d(4.0);

			auto result = (a * b)();
			std::cerr << result(1, 1) << std::endl;
		}},
	});
}
