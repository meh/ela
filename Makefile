CXX = clang++
override CXXFLAGS += -Wall -Wextra -Werror -ggdb -Iinclude -isystem tests/amirite -std=c++11

SOURCES := $(wildcard tests/*.cpp)
DEPS := $(SOURCES:.cpp=.d)
TESTS := $(SOURCES:.cpp=.test)

-include $(DEPS)

%.d: %.cpp
	@ $(CXX) $(CXXFLAGS) $< -MM -MT $(@:.d=.test) >$@

%.test: %.cpp
	@ $(CXX) $(CXXFLAGS) -o $@ $<

.PHONY: test
test: $(TESTS)
	@ for test in $(TESTS); do \
		$$test; \
		echo; \
	done

.PHONY: clean
clean:
	@ rm -f $(TESTS) $(DEPS)
