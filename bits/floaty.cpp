#include "floaty.h"
#include "bitcounter.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <cstdint>
#include <cmath>
#include <cstdlib>

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
	// Those bits marked * belong to the exponent; those marked & belong to the
	// significand.  s is the sign-bit for the significand
	//         LSB-exp  MSB-exp
	//          ****&&&& s*******
	// [...|...|01234567|01234567]
	
	p += 7;
	//std::cout << "e=" << bitprinter(e) << std::endl;
	e += (*p & 0x7Fu);  // mask off the sign bit
	//std::cout << "e+=(*p&0x7Fu); => e=" << bitprinter(e) << "=> " << e << std::endl;
	e <<= 8;  
	//                s*******
	// e == [00000000|01234567]
	//std::cout << "e<<=8; => e=" << bitprinter(e) << "=> " << e << std::endl;
	--p; e += *p;
	//       ****&&&& s*******
	// e == [01234567|01234567]
	//std::cout << "--p; e+=*p; => e=" << bitprinter(e) << "=> " << e << std::endl;
	e>>=4;
	//       ********     s***
	// e == [45670123|00000123]
	//std::cout << "e>>=4; => e=" << bitprinter(e) << "=> " << e << std::endl;
	return e;
}

uint16_t exponent_biased_x8664_m2(double d) {
	const unsigned char *p = static_cast<unsigned char*>(static_cast<void*>(&d));
	uint64_t e {0};

	// The loop below assumes doubles are LE-encoded
	static_assert(sizeof(double)==sizeof(uint64_t));
	for (int i=sizeof(double)-1; i>=0; --i) {
		e <<= 8;
		e += *(p+i);
	}
	
	e <<= 1;  // shift off the sign bit
	e >>= 53;  // shr by 53, not 52, b/c above i shl by 1
	return static_cast<uint16_t>(e);

	// Illegal method that voilates aliasing rules
	//const uint64_t *p2 = static_cast<uint64_t*>(static_cast<void*>(&d));
	//uint64_t e2 = *p2;
	//e2<<=1;  // shift off the sign bit
	//e2>>=53;  // shr by 53, not 52, b/c above I shl by 1
	//// Alternate:  e&=0x7FFFFFFFFFFFFFFFu; e>>=52;
	//return static_cast<uint16_t>(e);
}

int32_t exponent_unbiased_x8664(double d) {
	auto eb = exponent_biased_x8664(d);
	int32_t e = static_cast<int32_t>(eb)-1023;
	return e;
}


//
// For an IEEE-754/64 float x = M*2^e, the largest possible M is:
// M_max == 0x00'0F'FF'FF'FF'FF'FF'FFu == 2^52-1 == 4503599627370495
// The leading bit of the MSB is the sign bit; the remainder of the unset bits
// in the leading bytes above belong to the exponent.  Note that in the 
// IEEE754 format, the sign bit "belongs" to the significand, but is physcially
// seperate from the 52 bits of the significand.  The largest magnitude number 
// has all significand bits set, as shown above; this magnitude is the same for
// std::numeric_limits<double>::lowest() and std::numeric_limits<double>::max().  
//
uint64_t raw_significand_x8664(double d) {
	const unsigned char *p = static_cast<unsigned char*>(static_cast<void*>(&d));
	uint64_t us {0};  // us => "unsigned significand"

	// The loop below assumes doubles are LE-encoded
	static_assert(sizeof(double)==sizeof(uint64_t));
	for (int i=sizeof(double)-1; i>=0; --i) {
		us <<= 8;
		us += *(p+i);
	}

	return us&0x000FFFFFFFFFFFFFu;
}


int64_t significand_x8664(double d) {
	const unsigned char *p = static_cast<unsigned char*>(static_cast<void*>(&d));
	uint64_t us {0};  // us => "unsigned significand"

	// The loop below assumes doubles are LE-encoded
	static_assert(sizeof(double)==sizeof(uint64_t));
	for (int i=sizeof(double)-1; i>=0; --i) {
		us <<= 8;
		us += *(p+i);
	}

	if (us>>63) {  // Negative
		return -1*static_cast<int64_t>(us&0x000FFFFFFFFFFFFFu);
	} else {
		return static_cast<int64_t>(us&0x000FFFFFFFFFFFFFu);
	}
}

uint8_t signbit_x8664(double d) {
	const unsigned char *p = static_cast<unsigned char*>(static_cast<void*>(&d));
	p += sizeof(double)-1;
	return static_cast<uint8_t>((*p)>>7);
}

// TODO:  Untested
// TODO:  A nan must not have all 0's in the significand
bool isnan(double d) {
	const unsigned char *p = static_cast<unsigned char*>(static_cast<void*>(&d));
	p += sizeof(double)-1;
	uint16_t highbits {0};
	highbits += *p;  highbits<<=8;
	highbits += *--p;

	highbits&=0x7FFFu;  // masks off the sign bit
	highbits>>=4;  // shift off the 4 bytes of significand
	return highbits==0x0FFF;

	// Illegal method that violates aliasing rules
	//const uint64_t *pu = static_cast<uint64_t*>(static_cast<void*>(&d));
	//uint64_t e = (*pu)&0x7FFFFFFFFFFFFFFFu;
	//e>>=52;
	//return (e==0x00000000000007FFu);
}

int test_exponent_x8664() {
	int32_t eu {0};
	uint16_t eb {0};
	uint16_t ebm2 {0};
	uint8_t sb {0};
	int64_t s {0};
	uint64_t rws {0};

	std::vector<double> tests {
		std::numeric_limits<double>::lowest(), std::numeric_limits<double>::min(),
		-2.0,0.0,0.1,1.0,2.0,4.0,6.0,
		std::numeric_limits<double>::max(),
		std::numeric_limits<double>::quiet_NaN(),
		std::numeric_limits<double>::signaling_NaN()
	};
	for (const auto& d : tests) {
		eu = exponent_unbiased_x8664(d);
		eb = exponent_biased_x8664(d);
		ebm2 = exponent_biased_x8664_m2(d);
		sb = signbit_x8664(d);
		rws = raw_significand_x8664(d);
		s = significand_x8664(d);
		std::cout << "d== " << std::to_string(d) << " => [" << bitprinter(d) << "]\n"
			<< "\t=> exponent biased == " << eb << " => [" << bitprinter(eb) << "]\n"
			<< "\t=> exponent biased m2 == " << ebm2 << " => [" << bitprinter(ebm2) << "]\n"
			<< "\t=> exponent unbiased == " << eu << " => [" << bitprinter(eu) << "]\n"
			<< "\t=> signbit == " << std::to_string(sb) << " => [" << bitprinter(sb) << "]\n"
			<< "\t=> raw significand == " << rws << " => [" << bitprinter(rws) << "]\n"
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



//
// FP notes:
// -p8:  If e==emin the number is denormal
// -p10f:  Underflow => the result is subnormal _and_ inexact
// -p10,11:  For correct rounding and no overflow and no underflow, 
//  relative error of an operation is bounded by:
//  RN => (1/2)*B^(1-p)
//  RD,RU,RZ => B^(p-1)
// -p.11:  For FP numbers x,y where x/2 <= y <= 2*x, x-y if an FP number;
//  rounding mode is irrelevant (ie, x-y is exact).  
//
//
//


int probe_radix() {
	// w/o defining vars for 0.0, 1.0, if double is changed to float, statements
	// such as a+1.0 involve first converting a to a double (since 1.0 => double),
	// adding, then downcasting.  
	const double one = 1.0;
	const double zero = 0.0;
	double a = 1.0;
	double b = 1.0;

	while (((a+one)-a)-one == zero) {
		a *= 2;
	}
	while (((a+b)-a)-b != zero) {
		b += one;
	}

	auto anext = std::nextafter(a,10*a);
	auto anma = anext-a;
	return b;
}

int test_probe_radix() {
	std::cout << "probe_radix() == " << probe_radix() << std::endl;

	return 0;
}
