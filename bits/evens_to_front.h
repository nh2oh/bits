#pragma once
#include <vector>
#include <algorithm>
#include <type_traits>

// Moves all the even numbers in [beg,end) to the front of the range.  Returns an
// iterator to one past the final even number.  
template<typename It>
It evens_to_front(It beg, It end) {
	static_assert(std::is_integral<std::remove_reference<decltype(*beg)>::type>::value,
		"Arguments must dereference to yield an integral type.");

	It evens_end = beg;
	while (beg != end) {
		if ((*beg)%2 == 0) {
			std::iter_swap(evens_end,beg);
			++evens_end;
		}
		++beg;
	}

	return evens_end;
};

int test_evens_to_front();

