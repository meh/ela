// Copyright (c) 2017 1aim GmbH
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is furnished to do
// so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef ELA_H
#define ELA_H

#include <memory>
#include <algorithm>
#include <initializer_list>
#include <cmath>
#include <cassert>

#if !defined(ELA_ASSUME)
# if defined(NDEBUG)
#		if defined(_MSVC_VER)
#			define ELA_ASSUME(e) __assume(e)
#		else
#			define ELA_ASSUME(e) if (!(e)) { __builtin_unreachable(); }
#		endif
#	else
#		define ELA_ASSUME(e) assert(e)
# endif
#endif

#include "forward.hpp"
#include "order.hpp"
#include "storage.hpp"
#include "expression.hpp"
#include "matrix.hpp"
#include "vector.hpp"

#endif
