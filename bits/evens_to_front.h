#pragma once
#include <vector>
#include <algorithm>
#include <type_traits>
#include <string>

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

// Increment by 1 a decimal "number" represented as an array with each element a digit on [0,9].  
// Returns true on success, false on overflow
template<typename It>
bool inc_dec_arry(It beg, It end) {
	bool carry {false};

	while (end != beg) {
		--end;
		if (*end < 9) {
			*end += 1;
			carry = false;
			break;
		} else {
			carry = true;
			*end = 0;
		}
	}

	return !carry;
}

bool test_inc_dec_arry();


// Multiply two N-digit "numbers" represented as arrays with each element a digit on [0,9].  
// Returns true on success, false on overflow
/*
template<int N>
std::array<int,N> mult_dec_arrys(const std::array<int,N>& lhs, const std::array<int,N>& rhs) {
	static_assert(N>=1);

	// actually gets the most_sig dig
	auto least_sig_dec_dig = [](int d) -> int {
		pten = 1;
		while (d/pten > 9) {
			pten *=10;
		}
		return d/pten;
	};

	int carry {0};
	std::array<int,N> result = rhs;
	for (int i=N-1; i>=0; --i) {
		int curr = (rhs[i]*lhs[i])+carry;
		result[i] = least_sig_dec_dig(curr);
		carry = most_sig_dec_dig(curr);
	}

	return carry!=0;
};
*/

template<typename It>
It insort(It beg, It end) {
	if (end-beg <= 1) {
		return end;
	}
	for (It curr=(beg+1); curr!=end; ++curr) {
		It a=curr;
		It b=curr-1;
		while ((a!=beg) && (*a<*b)) {
			std::iter_swap(b,a);
			if (b==beg) {
				break;
			} else {
				b--;
				a--;
			}
		}
	}

	return end;
};

int test_insort();

//
// Find unmatched parens
//
std::string::const_iterator find_first_uparen(const std::string&);
int test_find_first_uparen();
