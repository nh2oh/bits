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


//
// Each iteration:
// - curr is incremented exactly once
// - lt_end is incremented not more than once
// - pvt_end is incemented s.t. pvt_end >= lt_end
//
// Invariants @ the start of each iteration:
// - lt_end <= curr
// - pvt_end <= curr
// - pvt_end >= lt_end
//
//

template<typename It>
It dnfp(It beg, It end, It pvt) {
	auto pvt_v = *pvt;
	It lt_end = beg;
	It pvt_end = beg;
	It curr = beg;
	while (curr != end) {
		if (*curr < pvt_v) {
			std::iter_swap(curr,lt_end);
			++lt_end;
			if (pvt_end < lt_end) {
				pvt_end = lt_end;
			}
		}
		if (*curr == pvt_v) {
			std::iter_swap(curr,pvt_end);
			++pvt_end;
		}
		++curr;
	}

	return end;
}


int test_dnfp();




