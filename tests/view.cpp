#include <iostream>
#include <amirite>
#include <ela/ela.hpp>

int
main (void)
{
	return amirite("view", {
		{"dummy", []{
			ela::matrix<3, 3> mat(1.0);
			auto columns = ela::make_view<ela::for_column<1>>(mat);

			amiequal(columns[0], 0);
			amiequal(columns[1], 1);
			amiequal(columns[2], 0);
		}},
	});
}
