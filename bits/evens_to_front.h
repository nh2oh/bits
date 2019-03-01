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

//
// Reverse words in sentence
//
std::string reverse_words(const std::string&);
int test_reverse_words();


//
// Reverse digits
//
int reverse_digits(int);
int test_reverse_digits();


//
// reverse
//
template<typename It>
void dbkreverse(It beg, It end) {
	while (beg!=end && beg!=--end) {
		std::iter_swap(beg,end);
		++beg;
	}
}
int test_reverse();




//
// shift_left
// Swaps the elements [beg+n,end) with the elements [beg,end-(beg+n)).  In the new array,
// the elements [beg,end-(beg+n)) and [beg+n,end) retain their initial order.  Returns 
// an iterator to one past the last shifted value (== end-(beg+n)).  
//
// Example:
// v=[1,2,3,4,5,6,7,8,9]; auto r=dbk_shift_left(v.begin(),v.end(),6);  // note v[6] == 7
// => v = [7,8,9,4,5,6,1,2,3]
// => *r = 4
// 
template<typename It>
It dbk_shift_left(It beg, It end, int n) {
	if (n > (end-beg)) {
		return beg;
	}
	It curr = beg+n;
	while (curr!=end) {
		*beg=*curr;
		++curr;
		++beg;
	}
	return beg;
}
int test_dbk_shift_left();

// 
// Moves elem to the position indicated by beg; elements [beg,elem) retain their initial 
// order.  Returns an iterator to one past beg (ie, one past the new position of elem).  
//
// TODO:  Overload to_front(It beg, It start, It end)  // moves [start,end) to front
//
template<typename It>
It to_front(It beg, It elem) {
	It prev=elem;
	while (prev != beg) {
		// prev==elem; prev!=beg; elem!=beg
		--prev;
		// prev==elem-1; prev _may_ == beg;  elem!=beg;
		std::iter_swap(prev,elem);
		if (prev==beg) {
			break;
		}
		--elem;
		// elem==prev; prev!=beg; elem!=beg;
	}
	return elem;

	// Alternate form:
	// The conditional break in the loop is needed, since decrementing past beg is illegal;
	// on the final iteration, prev==beg upon entering the loop.  After iter_sawp(), 
	// --elem => elem==beg
	// (prev--!=beg) => false, but prev-- => prev=beg-1, which is illegal
	//for (It prev=elem; prev--!=beg; --elem) {
	//	// prev==elem-1;  prev _may_==beg;  elem!=beg
	//	std::iter_swap(prev,elem);
	//	if (prev==beg) { break; }
	//}
	//return elem;
}


//
// Takes a _sorted_ array and moves all duplicate elements to the front of the array.  
// Returns an iterator to the beginning of the sequence of non-duplicates (corresponding
// to the end of the "duplicates" subarray).  The initial sorting order is maintained in
// both subarrays.  
//
template<typename It>
It dedup(It beg, It end) {
	if (beg==end) {
		return beg;
	}
	It curr = beg;
	It next = curr;
	while (++next!=end) {
		// next == curr+1;
		auto eb = end-beg;
		auto ec = end-curr;
		auto en = end-next;
		if (*curr==*next) {
			beg = to_front(beg,curr);  // beg points one past the new position of curr
		}
		eb = end-beg;
		ec = end-curr;
		en = end-next;
		++curr;
		// curr == next
	}
	return beg;
}

int test_dedup();







