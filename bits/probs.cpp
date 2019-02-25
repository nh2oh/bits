//#pragma fenv_access (on)
#include <string>
#include <iostream>
#include <vector>
#include <limits>
#include <cmath> // std::log() in pwr3()
//#include <cfenv>
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


