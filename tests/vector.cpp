#include <iostream>
#include <amirite>
#include <ela/ela.hpp>

int
main (void)
{
	return amirite("vector", {
		{"zero", []{
			ela::vector<3> vec;

			amiequal(vec(0), 0);
			amiequal(vec(1), 0);
			amiequal(vec(2), 0);
		}},
	});
}
