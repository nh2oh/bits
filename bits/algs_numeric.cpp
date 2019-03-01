#include "algs_numeric.h"
#include <iostream>
#include <array>
#include <vector>
#include <string>


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



// n = 3^p ?
//
// n = 3^p  =>  log2(n) = p*log2(3)  =>  log2(n)/log2(3) = p;
// log2(n), log2(3) have exact representations in base 2 (std::log2(n), std::log2(3) never raise
// FE_INEXACT), but the ratio log2(n)/log2(3) does not.  The fp-representation of this ratio may be
// slightly > or slightly < the exact value.  A static_cast<int> of this ratio will yield an integer
// < the exact result in all cases except those where the fp-representation of the ratio is greater 
// than the exact value and where there is an integer between the exact value and the fp 
// representation.  If this occurs the int returned by the static_cast will still be > than the exact 
// value.  
// But this is irrelevant.  Unless the exact value is an integer, n is not a power of 3.  If the exact 
// value is an integer, i am only in trouble if the error in the fp representation differs from the 
// exact value by more than 1; this seems unlikely.  
// Summary:
// I need log3(n) to be <= its exact value and to not differ from its exact value by more than 1.  
//
// Wikipedia:
// The integer binary logarithm can be interpreted as the zero-based index of the most 
// significant 1 bit in the input.  
//
bool pwr3(int n) {
	int r = n/3;
	if (n<=0 || (r!=0 && r*3!=n)) {
		// note that this does not disqualify n==1; 1==3^0
		return false;
	}
	auto p = static_cast<int>(std::log2(n)/std::log2(3));
	//bool ispow = (n == std::pow(3,p));
	bool ispow = (n==std::pow(3,p) || n==std::pow(3,p+1));

	/*std::feclearexcept(FE_ALL_EXCEPT);
	if (std::fetestexcept(FE_DIVBYZERO)) {
		std::cout << "divbyzero ";
	}
	if (std::fetestexcept(FE_INVALID)) {
		std::cout << "invalid ";
	}
	if (std::fetestexcept(FE_INEXACT)) {
		std::cout << "inexact ";
	}
	if (std::fetestexcept(FE_OVERFLOW)) {
		std::cout << "overflow ";
	}
	if (std::fetestexcept(FE_UNDERFLOW)) {
		std::cout << "underflow ";
	}
	std::feclearexcept(FE_ALL_EXCEPT);*/

	return ispow;
	//int p = static_cast<int>(std::log2(n/3));
	//return (n==std::pow(3,p) || n==std::pow(3,p+1));
}

int test_pwr3() {
	/*std::vector<int> random_tests {
		-3,-1,0,1,2,3,4,5,6,9,45,100,
		81,243,2184,2185,2186,2187,2188,2189,2130,2131,2132,
		720,721,722,723,724,725,726,727,728,729,730,731,732
	};

	for (const auto& e : random_tests) {
		std::cout << "n==" << std::to_string(e) << " => " << std::to_string(pwr3(e)) << "\n";
	}
	std::cout << std::endl;*/


	for (int i=-10; i<std::numeric_limits<int>::max()/100; ++i) {
		if (pwr3(i)) {
			std::cout << "i==" << std::to_string(i) << "\n";
		}
	}
	std::cout << std::endl;

	return 0;
}


int hamming_dist(int a, int b) {
	unsigned int ua = *static_cast<unsigned int*>(static_cast<void*>(&a));
	unsigned int ub = *static_cast<unsigned int*>(static_cast<void*>(&b));

	int count = 0;
	unsigned int mask=1;
	while (mask > 0) { //(ua>0 || ub>0) {
		if ((ua&mask) != (ub&mask)) {
			++count;
		}
		mask<<=1;
	}

	return count;
}

int test_hamming_dist() {
	std::cout << std::to_string(hamming_dist(1,4)) << std::endl;
	std::cout << std::to_string(hamming_dist(-16,99)) << std::endl;

	return 0;
}
