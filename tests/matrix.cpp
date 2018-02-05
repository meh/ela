#include <iostream>
#include <amirite>
#include <ela/ela.hpp>
#include <ela/util.hpp>

int
main (void)
{
	return amirite("matrix", {
		{"zero", []{
			ela::matrix<float, 3, 3> mat;

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
			auto mat = ela::matrix<float, 3, 3>::identity();

			amiequal(mat(0, 0), 1.0);
			amiequal(mat(1, 1), 1.0);
			amiequal(mat(2, 2), 1.0);
		}},

		{"equal", []{
			ela::matrix<float, 3, 3> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
			ela::matrix<float, 3, 3> b = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};

			amiequal(a + b, b + a);
		}},

		{"not equal", []{
			ela::matrix<float, 3, 3> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
			ela::matrix<float, 3, 3> b = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};

			amidifferent(a + b, b + a + a);
		}},

		{"add", []{
			auto a = ela::matrix<float, 3, 3> { { 1.0, 2.0, 3.0 }, { 4.0, 5.0, 6.0 }, { 7.0, 8.0, 9.0 } };
			auto b = ela::matrix<float, 3, 3>::identity();

			ela::matrix<float, 3, 3> c = a + b;

			amiequal(c(0, 0), 2.0);
			amiequal(c(0, 1), 2.0);
			amiequal(c(0, 2), 3.0);

			amiequal(c(1, 0), 4.0);
			amiequal(c(1, 1), 6.0);
			amiequal(c(1, 2), 6.0);

			amiequal(c(2, 0), 7.0);
			amiequal(c(2, 1), 8.0);
			amiequal(c(2, 2), 10.0);
		}},

		{"subtract", []{
			ela::matrix<float, 3, 3> a({ { 1.0, 2.0, 3.0 }, { 4.0, 5.0, 6.0 }, { 7.0, 8.0, 9.0 } });
			ela::matrix<float, 3, 3> b = ela::matrix<float, 3, 3>::identity();
			ela::matrix<float, 3, 3> c = a - b;

			amiequal(c(0, 0), 0.0);
			amiequal(c(0, 1), 2.0);
			amiequal(c(0, 2), 3.0);

			amiequal(c(1, 0), 4.0);
			amiequal(c(1, 1), 4.0);
			amiequal(c(1, 2), 6.0);

			amiequal(c(2, 0), 7.0);
			amiequal(c(2, 1), 8.0);
			amiequal(c(2, 2), 8.0);
		}},

		{"multiply", []{
			ela::matrix<float, 3, 3> a({ { 1.0, 2.0, 3.0 }, { 4.0, 5.0, 6.0 }, { 7.0, 8.0, 9.0 } });
			ela::matrix<float, 3, 3> b = ela::matrix<float, 3, 3>::scaling(2.0);
			ela::matrix<float, 3, 3> c = a * b;

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

		{"scalar multiply", []{
			ela::matrix<float, 3, 3> a({ { 1.0, 2.0, 3.0 }, { 4.0, 5.0, 6.0 }, { 7.0, 8.0, 9.0 } });
			ela::matrix<float, 3, 3> b = a * 2;

			amiequal(b(0, 0), 2.0);
			amiequal(b(0, 1), 4.0);
			amiequal(b(0, 2), 6.0);

			amiequal(b(1, 0), 8.0);
			amiequal(b(1, 1), 10.0);
			amiequal(b(1, 2), 12.0);

			amiequal(b(2, 0), 14.0);
			amiequal(b(2, 1), 16.0);
			amiequal(b(2, 2), 18.0);
		}},

		{"scalar divide", []{
			ela::matrix<float, 3, 3> a({ { 1.0, 2.0, 3.0 }, { 4.0, 5.0, 6.0 }, { 7.0, 8.0, 9.0 } });
			ela::matrix<float, 3, 3> b = a / 2;

			amiequal(b(0, 0), 0.5);
			amiequal(b(0, 1), 1.0);
			amiequal(b(0, 2), 1.5);

			amiequal(b(1, 0), 2.0);
			amiequal(b(1, 1), 2.5);
			amiequal(b(1, 2), 3.0);

			amiequal(b(2, 0), 3.5);
			amiequal(b(2, 1), 4.0);
			amiequal(b(2, 2), 4.5);
		}},

		{"transpose", []{
			ela::matrix<float, 3, 3> a;
			a = { { 1.0, 2.0, 3.0 }, { 4.0, 5.0, 6.0 }, { 7.0, 8.0, 9.0 } };
			ela::matrix<float, 3, 3> b = ~a;

			amiequal(b(0, 0), 1.0);
			amiequal(b(0, 1), 4.0);
			amiequal(b(0, 2), 7.0);

			amiequal(b(1, 0), 2.0);
			amiequal(b(1, 1), 5.0);
			amiequal(b(1, 2), 8.0);

			amiequal(b(2, 0), 3.0);
			amiequal(b(2, 1), 6.0);
			amiequal(b(2, 2), 9.0);
		}},

		{"invert", []{
			ela::matrix<float, 2, 2> a = {{1, 2}, {3, 4}};
			ela::matrix<float, 2, 2> b = !a;

			auto r = b.at<0, 0>();
			amiequal(r, -2.0f);

			amiequal(b(0, 0), -2);
			amiequal(b(0, 1), 1);

			amiequal(b(1, 0), 1.5);
			amiequal(b(1, 1), -0.5);
		}},
	});
}
