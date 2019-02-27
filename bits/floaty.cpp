#include "floaty.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <string>

int test_floaty() {
	floaty<2,4,2> f;

	f.set(5);
	std::cout << f.print() << std::endl;

	return 0;
}



int required_digits(int n, int db) {  // number, dest base
	if (db <= 1 || n < 0) {
		std::abort();
	}
	//  max_value = b^d - 1
	// => d = logb(max_value-1)
	return std::ceil(std::log2(n+1)/std::log2(db));
}

int test_required_digits() {
	struct tests {
		int n {0};
		int ans {0};
	};
	int curr_base {0};
	std::vector<tests> curr_tests {};

	curr_base = 2;
	std::cout << "Base 10 -> Base " << std::to_string(curr_base) << std::endl;
	curr_tests = {
		{0,0},{1,1},{2,2},{3,2},{4,3},{5,3},{6,3},{7,3},
		{8,4},{9,4},{14,4},{15,4},{16,5},{17,5}
	};
	for (const auto& e : curr_tests) {
		std::cout << std::to_string(e.n) << " => " 
			<< std::to_string(required_digits(e.n,curr_base)) << std::endl;
		if (required_digits(e.n,curr_base) != e.ans) {
			std::cout << "\tERROR!!!!" << std::endl;
		}
	}
	std::cout << "------------------------------------------------------" << std::endl;


	curr_base = 10;
	std::cout << "Base 10 -> Base " << std::to_string(curr_base) << std::endl;
	curr_tests = {
		{0,0},{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},
		{8,1},{9,1},{14,2},{15,2},{16,2},{17,2}
	};
	for (const auto& e : curr_tests) {
		std::cout << std::to_string(e.n) << " => " 
			<< std::to_string(required_digits(e.n,curr_base)) << std::endl;
		if (required_digits(e.n,curr_base) != e.ans) {
			std::cout << "\tERROR!!!!" << std::endl;
		}
	}
	std::cout << "------------------------------------------------------" << std::endl;


	curr_base = 16;
	std::cout << "Base 10 -> Base " << std::to_string(curr_base) << std::endl;
	curr_tests = {
		{0,0},{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},
		{8,1},{9,1},{14,1},{15,1},{16,2},{17,2}
	};
	for (const auto& e : curr_tests) {
		std::cout << std::to_string(e.n) << " => " 
			<< std::to_string(required_digits(e.n,curr_base)) << std::endl;
		if (required_digits(e.n,curr_base) != e.ans) {
			std::cout << "\tERROR!!!!" << std::endl;
		}
	}
	std::cout << "------------------------------------------------------" << std::endl;

	return 0;
}


