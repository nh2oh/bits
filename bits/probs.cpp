#include <string>
#include <iostream>
#include <vector>
#include <limits>
#include "probs.h"


// vector to be printed, optional int idx of an element to be printed w/a '*'
std::string printv(const std::vector<int>& v, int idx_star) { 
	std::string s {'{'};
	for (const auto& e : v) {
		s += std::to_string(e);
		if (idx_star==0) {
			s += '*';
		}
		s += ',';
		--idx_star;
	};
	if (v.size()>0) {
		s.pop_back();
	}
	s += '}';
	return s;
};



int colid2int(const std::string& s) {
	// Want A=>1, B=>2, AA=>27, ZZ=>702, etc.  There are 26 letters in the alphabet.  
	int r = 0;
	for (const auto& e : s) {
		if (std::numeric_limits<int>::max()/26 < r) {
			return 0;
		}
		r *= 26;
		r += e - 'A' + 1;
	}

	return r;
}


int test_colid2int() {
	if (colid2int("A") != 1) {
		std::cout  << "Failed :(" << std::endl;
	}
	if (colid2int("D") != 4) {
		std::cout  << "Failed :(" << std::endl;
	}
	if (colid2int("AA") != 27) {
		std::cout  << "Failed :(" << std::endl;
	}
	if (colid2int("ZZ") != 702) {
		std::cout  << "Failed :(" << std::endl;
	}

	return 0;
}


int test_shift_to_end() {
	std::vector<int> v_init {0,1,2,3,4,5,6,7,8,9};

	for (int i=0; i<v_init.size(); ++i) {
		auto v = v_init;
		std::cout << printv(v,i) << " => ";
		auto rv = shift_to_end(v.begin()+i,v.end());
		std::cout << printv(v) << "; *rv== " << std::to_string(*rv) << std::endl;
	}

	return 0;
}

int test_dbkrot() {
	std::vector<int> v_init {0,1,2,3,4,5,6,7,8,9};

	for (int i=1; i<v_init.size(); ++i) {
		auto v = v_init;
		std::cout << printv(v,i) << " => ";
		auto rv = dbkrot(v.begin(),v.end(),v.begin()+i);
		std::cout << printv(v) << "; *rv== " << std::to_string(*rv) << std::endl;
	}

	return 0;
}


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





