#include "unsorted_probs.h"
#include <string>
#include <iostream>
#include <vector>
#include <limits>


void fizzbuzz_a() {
	int ntest = 0;
	for (int i=0; i<101; ++i) {
		std::cout << "i= " << i << ":  ";
		if (i%3 == 0) {
			std::cout << "Fizz";
			++ntest;
		}
		if (i%5 == 0) {
			std::cout << "Buzz";
			++ntest;
		}
		std::cout << "\n";
	}
	std::cout << "ntest == " << ntest << std::endl;
}

void fizzbuzz_b() {
	int ntest = 0;
	for (int i=0; i<101; ++i) {
		std::cout << "i= " << i << ":  ";
		if (i%15 == 0) {
			std::cout << "Fizzbuzz";
			ntest += 1;
		} else if (i%3 == 0) {
			std::cout << "Fizz";
			ntest += 2;
		} else if (i%5 == 0) {
			std::cout << "Buzz";
			ntest += 3;
		}
		std::cout << "\n";
	}
	std::cout << "ntest == " << ntest << std::endl;
}

void fizzbuzz_c() {
	int ntest = 0;
	for (int i=0; i<101; ++i) {
		std::cout << "i= " << i << ":  ";
		if (i%15 == 0) {
			std::cout << "Fizzbuzz";
			ntest += 1;
		} else if (i%5 == 0) {
			std::cout << "Buzz";
			ntest += 2;
		} else if (i%3 == 0) {
			std::cout << "Fizz";
			ntest += 3;
		}
		std::cout << "\n";
	}
	std::cout << "ntest == " << ntest << std::endl;
}


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




