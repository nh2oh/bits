#include "evens_to_front.h"
#include <iostream>
#include <string>
#include <array>
#include <vector>

int test_evens_to_front() {
	
	std::vector<int> a {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
	auto a_ev_end = evens_to_front(a.begin(),a.end());

	for (std::vector<int>::iterator it = a.begin(); it != a.end(); ++it) {
		std::cout << *it;
		if (it == a_ev_end) {
			std::cout << "*, ";
		} else {
			std::cout << ", ";
		}
	} 
	std::cout << "\n\n";

	// All values even
	std::vector<int> b {0,2,2,14,4,52,6,72,8,90,10,0,12,4};
	auto b_ev_end = evens_to_front(b.begin(),b.end());
	for (std::vector<int>::iterator it = b.begin(); it != b.end(); ++it) {
		std::cout << *it;
		if (it == b_ev_end) {
			std::cout << "*, ";
		} else {
			std::cout << ", ";
		}
	}
	std::cout << "\n\n";

	// No values even
	std::vector<int> c {1,1,3,5,3,55,7,77,9,89,11,1,11,41};
	auto c_ev_end = evens_to_front(c.begin(),c.end());
	for (std::vector<int>::iterator it = c.begin(); it != c.end(); ++it) {
		std::cout << *it;
		if (it == c_ev_end) {
			std::cout << "*, ";
		} else {
			std::cout << ", ";
		}
	}
	std::cout << "\n\n";

	// Empty vector
	std::vector<int> d {};
	auto d_ev_end = evens_to_front(d.begin(),d.end());
	for (std::vector<int>::iterator it = d.begin(); it != d.end(); ++it) {
		std::cout << *it;
		if (it == d_ev_end) {
			std::cout << "*, ";
		} else {
			std::cout << ", ";
		}
	}
	std::cout << "\n\n";

	// std::vector<double> should not compile
	/*std::vector<double> e {1.0,0.0,2.3,27.15,2.0};
	auto e_ev_end = evens_to_front(e.begin(),e.end());
	for (std::vector<double>::iterator it = e.begin(); it != e.end(); ++it) {
		std::cout << *it;
		if (it == e_ev_end) {
			std::cout << "*, ";
		} else {
			std::cout << ", ";
		}
	}
	std::cout << "\n\n";*/

	return 0;
}


int test_dnfp() {
	std::cout << "---------------------------------------------------\n"
		<< "test_dnfp(): \n";

	// vector to be printed, optional int idx of an element to be printed w/a '*'
	auto printvec = [](const std::vector<int>& v, int idx_star=-1){ 
		std::string s {'{'};
		for (const auto& e : v) {
			s += std::to_string(e);
			if (idx_star==0) {
				s += '*';
			}
			s += ',';
			--idx_star;
		};
		s.pop_back();
		s += '}';
		return s;
	};

	// No repeats, already sorted
	std::cout << "No repeats, already sorted\n";
	std::vector<int> a_init {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
	for (int idx_pvt=0; idx_pvt<a_init.size(); ++idx_pvt) {
		std::cout << "a_init = " << printvec(a_init,idx_pvt) << "\n";
		auto a = a_init;
		auto a_dnfp = dnfp(a.begin(),a.end(),a.begin()+idx_pvt);
		std::cout << printvec(a) << "\n";
	}
	std::cout << std::endl;

	// All values even
	std::cout << "All values even\n";
	std::vector<int> b_init {0,2,2,14,4,52,6,72,8,90,10,0,12,4};
	for (int idx_pvt=0; idx_pvt<b_init.size(); ++idx_pvt) {
		std::cout << "b_init = " << printvec(b_init,idx_pvt) << "\n";
		auto b = b_init;
		auto b_dnfp = dnfp(b.begin(),b.end(),b.begin()+idx_pvt);
		std::cout << printvec(b) << "\n";
	}
	std::cout << std::endl;

	// Empty vector
	std::cout << "Empty vector\n";
	std::vector<int> c_init {};
	for (int idx_pvt=0; idx_pvt<c_init.size(); ++idx_pvt) {
		std::cout << "c_init = " << printvec(c_init,idx_pvt) << "\n";
		auto c = c_init;
		auto c_dnfp = dnfp(c.begin(),c.end(),c.begin()+idx_pvt);
		std::cout << printvec(c) << "\n";
	}
	std::cout << std::endl;

	// Vector w/ one element
	std::cout << "Vector w/ one element\n";
	std::vector<int> d_init {7};
	for (int idx_pvt=0; idx_pvt<d_init.size(); ++idx_pvt) {
		std::cout << "d_init = " << printvec(d_init,idx_pvt) << "\n";
		auto d = d_init;
		auto d_dnfp = dnfp(d.begin(),d.end(),d.begin()+idx_pvt);
		std::cout << printvec(d) << "\n";
	}
	std::cout << std::endl;

	// Vector w/ two elements
	std::cout << "Vector w/ two elements\n";
	std::vector<int> e_init {7,1};
	for (int idx_pvt=0; idx_pvt<e_init.size(); ++idx_pvt) {
		std::cout << "e_init = " << printvec(e_init,idx_pvt) << "\n";
		auto e = e_init;
		auto e_dnfp = dnfp(e.begin(),e.end(),e.begin()+idx_pvt);
		std::cout << printvec(e) << "\n";
	}
	std::cout << std::endl;

	// All elements identical
	std::cout << "All elements identical\n";
	std::vector<int> f_init {5,5,5,5,5,5,5};
	for (int idx_pvt=0; idx_pvt<f_init.size(); ++idx_pvt) {
		std::cout << "f_init = " << printvec(f_init,idx_pvt) << "\n";
		auto f = f_init;
		auto f_dnfp = dnfp(f.begin(),f.end(),f.begin()+idx_pvt);
		std::cout << printvec(f) << "\n";
	}
	std::cout << std::endl;

	return 0;

}


bool test_inc_dec_arry() {
	struct tests_four_t {
		std::array<int,4> test {0,0,0,0};
		std::array<int,4> ans {0,0,0,0};
		bool ans_retval {false};
	};
	std::vector<tests_four_t> tests_four {
		{{0,0,0,0},{0,0,0,1},true},
		{{0,0,0,9},{0,0,1,0},true},
		{{0,0,9,9},{0,1,0,0},true},
		{{0,9,9,9},{1,0,0,0},true},
		{{9,9,9,9},{0,0,0,0},false},

		{{1,2,3,4},{1,2,3,5},true},
		{{4,3,2,1},{4,3,2,2},true},
		{{1,1,8,9},{1,1,9,0},true},
	};
	
	for (const auto& e : tests_four) {
		std::array<int,4> curr_test_result = e.test;
		bool curr_test_retval = inc_dec_arry(curr_test_result.begin(),curr_test_result.end());
		if (curr_test_retval != e.ans_retval) {
			std::cout << "test_inc_dec_arry():  curr_test_retval != e.ans_retval  TEST FAILED!" << std::endl;
			return false;
		}

		if (curr_test_result != e.ans) {
			std::cout << "test_inc_dec_arry():  curr_test_result != e.ans  TEST FAILED!" << std::endl;
			return false;
		}
	}

	std::cout << "test_inc_dec_arry():  All tests passed!" << std::endl;
	return true;
}

int test_insort() {
	std::cout << "---------------------------------------------------\n"
		<< "test_insort(): \n";

	// vector to be printed, optional int idx of an element to be printed w/a '*'
	auto printvec = [](const std::vector<int>& v, int idx_star=-1){ 
		std::string s {'{'};
		for (const auto& e : v) {
			s += std::to_string(e);
			if (idx_star==0) {
				s += '*';
			}
			s += ',';
			--idx_star;
		};
		s.pop_back();
		s += '}';
		return s;
	};

	// Already sorted
	std::cout << "Sorted input\n";
	std::vector<int> a {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
	std::cout << "a = " << printvec(a) << "\n";
	insort(a.begin(),a.end());
	std::cout << "a = " << printvec(a) << "\n";
	std::cout << std::endl;

	// All values even
	std::cout << "All values even\n";
	std::vector<int> b {0,2,2,14,4,52,6,72,8,90,10,0,12,4};
	std::cout << "b = " << printvec(b) << "\n";
	insort(b.begin(),b.end());
	std::cout << "b = " << printvec(b) << "\n";
	std::cout << std::endl;

	// Empty input
	std::cout << "Empty input\n";
	std::vector<int> c {};
	std::cout << "c = " << printvec(c) << "\n";
	insort(c.begin(),c.end());
	std::cout << "c = " << printvec(c) << "\n";
	std::cout << std::endl;

	// Size == 1
	std::cout << "Input size == 1\n";
	std::vector<int> d {7};
	std::cout << "d = " << printvec(d) << "\n";
	insort(d.begin(),d.end());
	std::cout << "d = " << printvec(d) << "\n";
	std::cout << std::endl;

	// Size == 2
	std::cout << "Input size == 2\n";
	std::vector<int> e {7,4};
	std::cout << "e = " << printvec(e) << "\n";
	insort(e.begin(),e.end());
	std::cout << "e = " << printvec(e) << "\n";
	std::cout << std::endl;

	return 0;
}



//
// Find unmatched parens
//
// Paren matching is "greedy;" that is, the partner ) for any given ( is the _closest_ ).  Thus, in
// a(b(cd)efgh(i)jk, the unmatched ( is the one following the a, not the one following the b.  However,
// this does not mean that in a str w/ an unmatched (, the very first ( is always the problem.  
// Consider:
// ab((cd)e)fgh(ijk
// Here the unmatched ( follows the h.  
// On the other hand, the very first "excess" ) is considered unmatched.  
//
std::string::const_iterator find_first_uparen(const std::string& s) {
	int depth {0};
	std::string::const_iterator first_open;
	for (std::string::const_iterator it = s.cbegin(); it!=s.cend(); ++it) {
		if (*it == '(') {
			++depth;
			if (depth == 1) {
				first_open = it;
			}
		} else if (*it == ')') {
			--depth;
		}

		if (depth == -1) {
			return it;
		}
	}
	
	if (depth > 0) {
		return first_open;
	} else {
		return s.cend();
	}
}

int test_find_first_uparen() {
	std::string s {};
	std::string::const_iterator it {};

	s = "ab((cd)e)fgh(ijk";
	it = find_first_uparen(s);
	s.insert(it,1,'*');
	std::cout << s << std::endl;

	s = "a(b(cd)efgh(i)jk";
	it = find_first_uparen(s);
	s.insert(it,1,'*');
	std::cout << s << std::endl;

	s = "a()(b(cd)efgh(i)jk";
	it = find_first_uparen(s);
	s.insert(it,1,'*');
	std::cout << s << std::endl;

	// None unmatched
	s = "a()(b(cd)efgh(i))jk";
	it = find_first_uparen(s);
	s.insert(it,1,'*');
	std::cout << s << std::endl;

	s = "a()(b(cd)efgh(i))j)k";
	it = find_first_uparen(s);
	s.insert(it,1,'*');
	std::cout << s << std::endl;

	s.clear();
	it = find_first_uparen(s);
	s.insert(it,1,'*');
	std::cout << s << std::endl;

	s = "no parens at all!";
	it = find_first_uparen(s);
	s.insert(it,1,'*');
	std::cout << s << std::endl;

	return 0;
}



std::string reverse_words(const std::string& s) {
	std::string result {};  result.reserve(s.size());
	int curr_word_len {0};
	for (std::string::const_reverse_iterator rit=s.crbegin(); rit!=s.crend(); ++rit) {
		if (*rit == ' ') {
			if (curr_word_len > 0) {
				// NB rit.base() returns an iterator to the first letter in the word, even though
				// *rit == ' '.  
				std::string::const_iterator w_start = rit.base();
				std::string::const_iterator w_end = w_start; w_end+=curr_word_len;
				result.insert(result.end(), w_start, w_end);
				result.append(1,' ');
			}
			curr_word_len = 0;
		} else {
			++curr_word_len;
		}
	}
	// For s which do not begin with spaces, the very first word of s is not appended to result since 
	// the loop conditional only triggers when *rit == ' '.  It is possible to modify the conditional 
	// to triger when (*rit == ' ' || rit == s.crend()-1), however, for rit -> the first letter of the
	// first word in s, w_start would then point to the _second_ letter of the first word in s (see 
	// the note in the loop conditional).  
	if (curr_word_len > 0) {
		std::string::const_iterator w_start = s.cbegin();
		std::string::const_iterator w_end = w_start; w_end+=curr_word_len;
		result.insert(result.end(), w_start, w_end);
	}

	if (result.size() > 0 && result.back() == ' ') {
		// If s begins w/ leading spaces then the first word is appended to result by the loop, not
		// the post-loop conditional and a space will be appended to the first word in result, which
		// needs to be removed.  
		result.pop_back();
	}
	return result;
}

int test_reverse_words() {
	std::string s {};

	s = "Paren matching is \"greedy;\" that";
	std::cout << "\"" << s << "\"" << "  =>  " << "\"" << reverse_words(s) << "\"" << std::endl;

	s = "Paren matching is \"greedy;\" that     ";
	std::cout << "\"" << s << "\"" << "  =>  " << "\"" << reverse_words(s) << "\"" << std::endl;
	
	s = "     Paren matching is \"greedy;\" that     ";
	std::cout << "\"" << s << "\"" << "  =>  " << "\"" << reverse_words(s) << "\"" << std::endl;

	s.clear();
	std::cout << "\"" << s << "\"" << "  =>  " << "\"" << reverse_words(s) << "\"" << std::endl;

	s = "  ";
	std::cout << "\"" << s << "\"" << "  =>  " << "\"" << reverse_words(s) << "\"" << std::endl;

	s = " ";
	std::cout << "\"" << s << "\"" << "  =>  " << "\"" << reverse_words(s) << "\"" << std::endl;

	s = "onewordonly";
	std::cout << "\"" << s << "\"" << "  =>  " << "\"" << reverse_words(s) << "\"" << std::endl;

	s = "a b c";
	std::cout << "\"" << s << "\"" << "  =>  " << "\"" << reverse_words(s) << "\"" << std::endl;

	s = "x";
	std::cout << "\"" << s << "\"" << "  =>  " << "\"" << reverse_words(s) << "\"" << std::endl;

	return 0;
}





// TODO:  Overflow
int reverse_digits(int n) {
	bool neg = n<0;
	if (neg) { n *= -1; }
	int nr {0};
	while (n != 0) {
		nr *= 10;
		nr += n%10;
		n /= 10;
	}

	return neg ? -1*nr : nr;
}

int test_reverse_digits() {

	int n {0};

	n = 1234;
	std::cout << std::to_string(n) << " => " << std::to_string(reverse_digits(n)) << std::endl;

	n = 1324;
	std::cout << std::to_string(n) << " => " << std::to_string(reverse_digits(n)) << std::endl;

	n = 0;
	std::cout << std::to_string(n) << " => " << std::to_string(reverse_digits(n)) << std::endl;

	n = -4;
	std::cout << std::to_string(n) << " => " << std::to_string(reverse_digits(n)) << std::endl;

	n = -2365;
	std::cout << std::to_string(n) << " => " << std::to_string(reverse_digits(n)) << std::endl;

	// Overflow
	n = 2147483647;
	std::cout << std::to_string(n) << " => " << std::to_string(reverse_digits(n)) << std::endl;

	return 0;
}
