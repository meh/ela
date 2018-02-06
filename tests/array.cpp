#include <iostream>
#include <amirite>
#include <ela/ela.hpp>

int
main (void)
{
	return amirite("array", {
		{"access", []{
//			auto a = ela::matrix<float, 3, 3> { { 1.0, 2.0, 3.0 }, { 4.0, 5.0, 6.0 }, { 7.0, 8.0, 9.0 } };
//			auto b = ela::matrix<float, 3, 3> { { 1.0, 1.0, 1.0 }, { 1.0, 1.0, 1.0 }, { 1.0, 1.0, 1.0 } };
//
//			a.array().fill(1.0);
//			amiequal(a, b);
		}},
	});
}
