#include "str_algs.h"
#include <string>
#include <iostream>



int test_reverse_chunk_order() {
	std::string s {};
	s = "alice likes bob fatty";
	std::cout << "[" << s << "]" << " => ";
	reverse_chunk_order(s.begin(),s.end(),' ');
	std::cout << "[" << s << "]" << std::endl;

	s = "alice likes  bob   fatty";
	std::cout << "[" << s << "]" << " => ";
	reverse_chunk_order(s.begin(),s.end(),' ');
	std::cout << "[" << s << "]" << std::endl;

	s = "     alice likes  bob   fatty";
	std::cout << "[" << s << "]" << " => ";
	reverse_chunk_order(s.begin(),s.end(),' ');
	std::cout << "[" << s << "]" << std::endl;

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


