#include "bigint.h"
#include <vector>
#include <string>
#include <cstdint>
#include <iostream>

/*
std::string print_factorial(int n) {
	std::string s {};


	return s;
}



std::string print_b256(int n) {
	std::vector<uint8_t> f {};

	if (n==0) {
		f.push_back(0);
	}
	while (n!=0) {
		f.push_back(n%256);
		n /= 256;
	}

	std::string s {};
	for (int i=f.size()-1; (f.size()>0 && i>=0); --i) {
		s += std::to_string(f[i]);
	}

	return s;
}

int test_print_b256() {
	std::string s {};
	std::string s_ans {};

	s = print_b256(0);
	s_ans = "0";
	std::cout << s << "\n" << s_ans << std::endl << std::endl;

	s = print_b256(1);
	s_ans = "1";
	std::cout << s << "\n" << s_ans << std::endl << std::endl;

	s = print_b256(255);
	s_ans = "255";
	std::cout << s << "\n" << s_ans << std::endl << std::endl;

	s = print_b256(256);
	s_ans = "10";
	std::cout << s << "\n" << s_ans << std::endl << std::endl;

	s = print_b256(257);
	s_ans = "11";
	std::cout << s << "\n" << s_ans << std::endl << std::endl;

	// 5*256^3 + 0*256^2 + 0*256^1 + 0*256^0 == 83886080
	s = print_b256(83886080);
	s_ans = "5000";
	std::cout << s << "\n" << s_ans << std::endl << std::endl;

	// 5*256^3 + 0*256^2 + 0*256^1 + 1*256^0 == 83886081
	s = print_b256(83886081);
	s_ans = "5001";
	std::cout << s << "\n" << s_ans << std::endl << std::endl;


	return 0;
}

*/




