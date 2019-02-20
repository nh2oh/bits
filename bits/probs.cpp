#include <string>
#include <iostream>
#include <limits>
#include "probs.h"



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

