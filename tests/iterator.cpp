#include <iostream>
#include <amirite>
#include <ela/ela.hpp>
#include <ela/util.hpp>

int
main (void)
{
	return amirite("iterator", {
		{"elements (row_major)", []{
			ela::matrix<int, 3> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
			std::vector<int> b = {1, 2, 3, 4, 5, 6, 7, 8, 9};
			std::vector<int> c;

			for (auto e : a.elements<ela::order::row_major>()) {
				c.push_back(e);
			}

			amiequal(b, c);
		}},

		{"elements (column_major)", []{
			ela::matrix<int, 3> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
			std::vector<int> b = {1, 4, 7, 2, 5, 8, 3, 6, 9};
			std::vector<int> c;

			for (auto e : a.elements<ela::order::column_major>()) {
				c.push_back(e);
			}

			amiequal(b, c);
		}},

		{"elements (mutable)", []{
			ela::matrix<int, 3> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
			std::vector<int> b = {0, 0, 0, 0, 0, 0, 0, 0, 0};
			std::vector<int> c;

			for (auto& e : a.elements()) {
				e = 0;
			}

			for (auto e : a.elements()) {
				c.push_back(e);
			}

			amiequal(b, c);
		}},

		{"elements (expression)", []{
			ela::matrix<int, 3> a = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
			auto b = a * 2;

			for (auto e : b.elements()) {
				amiequal(e, 2);
			}
		}},

		{"rows", []{
			ela::matrix<int, 3> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
			std::vector<int> b = {1, 2, 3, 4, 5, 6, 7, 8, 9};
			std::vector<int> c;

			for (auto row : a.rows()) {
				for (auto e : row.elements()) {
					c.push_back(e);
				}
			}

			amiequal(b, c);
		}},

		{"columns", []{
			ela::matrix<int, 3> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
			std::vector<int> b = {1, 4, 7, 2, 5, 8, 3, 6, 9};
			std::vector<int> c;

			for (auto column : a.columns()) {
				for (auto e : column.elements()) {
					c.push_back(e);
				}
			}

			amiequal(b, c);
		}},
	});
}
