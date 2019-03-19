#include "floaty.h"
#include "bitcounter.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <cstdint>

int test_floaty() {
	floaty<2,4,2> f;

	f.set(5);
	std::cout << f.print() << std::endl;

	f.set(6);
	std::cout << f.print() << std::endl;

	f.set(7);
	std::cout << f.print() << std::endl;

	return 0;
}


uint16_t exponent_biased_x8664(double d) {
	const unsigned char *p = static_cast<unsigned char*>(static_cast<void*>(&d));
	uint16_t e {0};
	p += 7;
	//std::cout << "e=" << bitprinter(e) << std::endl;
	e += (*p & 0x7Fu);
	//std::cout << "e+=(*p&0x7Fu); => e=" << bitprinter(e) << "=> " << e << std::endl;
	e <<= 8;
	//std::cout << "e<<=8; => e=" << bitprinter(e) << "=> " << e << std::endl;
	--p; e += *p;
	//std::cout << "--p; e+=*p; => e=" << bitprinter(e) << "=> " << e << std::endl;
	e>>=4;
	//std::cout << "e>>=4; => e=" << bitprinter(e) << "=> " << e << std::endl;
	return e;
}

int32_t exponent_unbiased_x8664(double d) {
	auto eb = exponent_biased_x8664(d);
	int32_t e = static_cast<int32_t>(eb)-1023;
	return e;
}

int64_t significand_x8664(double d) {
	const unsigned char *p = static_cast<unsigned char*>(static_cast<void*>(&d));
	uint64_t s {0};
	for (int i=6; i>=0; --i) {
		s<<=8;
		s += *(p+i);
		if (i==6) {
			s &= 0x0Fu;
		}
	}
	return static_cast<int64_t>(s>>4);
}

int test_exponent_x8664() {
	int32_t eu {0};
	uint16_t eb {0};
	int64_t s {0};
	//double d {0.0};
	
	//d = 0.0;
	//std::cout << "d== " << std::to_string(d) << " => [" << bitprinter(d) << "]\n\t"
	//	<< "=> exponent== " << exponent_x8664(d) << std::endl;
	

	std::vector<double> tests {0.0,1.0,2.0,4.0};
	for (const auto& d : tests) {
		eu = exponent_unbiased_x8664(d);
		eb = exponent_biased_x8664(d);
		s = significand_x8664(d);
		std::cout << "d== " << std::to_string(d) << " => [" << bitprinter(d) << "]\n"
			<< "\t=> exponent biased == " << eb << " => [" << bitprinter(eb) << "]\n"
			<< "\t=> exponent unbiased == " << eu << " => [" << bitprinter(eu) << "]\n"
			<< "\t=> significand == " << s << " => [" << bitprinter(s) << "]\n"
			<< std::endl << std::endl;
	}

	auto dd = 2.0;
	/*
	std::cout << "d== " << std::to_string(d) << " => [" << bitprinter(d) << "]\n\t"
		<< "=> exponent== " << exponent_x8664(d) << std::endl;
	
	d = 4.0;
	std::cout << "d== " << std::to_string(d) << " => [" << bitprinter(d) << "]\n\t"
		<< "=> exponent== " << exponent_x8664(d) << std::endl;
	
	d = 1024.0;
	std::cout << "d== " << std::to_string(d) << " => [" << bitprinter(d) << "]\n\t"
		<< "=> exponent== " << exponent_x8664(d) << std::endl;
	//auto i = exponent_x8664(d);
	*/
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


	//constexpr auto merrex = MATH_ERREXCEPT;
	//constexpr auto merrno = MATH_ERRNO;
	//constexpr auto merrh = math_errhandling;


	return 0;
}


