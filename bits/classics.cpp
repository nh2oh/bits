#include "classics.h"
#include <iostream>


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

