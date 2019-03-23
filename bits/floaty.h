#pragma once
#include <array>
#include <cstdint>
#include <string>
#include <cmath>
#include <cstdint>

// B => base, Ps => Prec significand, Pexp => Prec exponent
template<int8_t B, int8_t Ps, int8_t Pexp>
class floaty {
public:
	static_assert(B==2, "Only base 2 is supported at this time");
	static_assert(Ps>0 && Pexp>0, "Precision must be >0");

	enum class eflag {
		overflow,
		underflow,
		inexact,
		nan,
		ok
	};

	std::array<int,Ps+Pexp> value {};
	std::string dig_sep {""};
	std::string sig_exp_sep {"xB^"};
	
	template<typename T>
	floaty::eflag set(T v) {
		int ndig_dropped = 0;
		T cv = v;
		while (cv>0) {
			int rq_ndig = std::ceil(std::log2(cv+1)/std::log2(B));  // also the current digit number+1
			int cd = cv%B;
			cv /= B;
			if (rq_ndig>Ps) {
				// WE _might_ have to drop the LS-digits
				if (cd != 0 || ndig_dropped>0) {
					++ndig_dropped;
				}
			} else {
				this->value[rq_ndig-1] = cd;
			}
		}

		int vexp = std::ceil(std::log2(v+1)/std::log2(B))-1;  // n-digits needed for vexp => value for the exponent
		while (vexp>0) {
			int rq_ndig = std::ceil(std::log2(vexp+1)/std::log2(B));  // also the current digit number+1
			int cd = vexp%B;
			vexp /= B;
			this->value[Ps+rq_ndig-1] = cd;
		}

		return floaty::eflag::ok;
	};


	std::string print() const {
		std::string s;
		s.reserve(Ps+Pexp+dig_sep.size()*Ps+sig_exp_sep.size()+dig_sep.size()*Pexp);

		for (int i=0; i<this->value.size(); ++i) {
			s += std::to_string(this->value[i]);
			if (i<(Ps-1)) {
				s += this->dig_sep;
			} else if (i==(Ps-1)) {
				s += sig_exp_sep;
			} else if (i>(Ps-1) && i<(Ps+Pexp-1)) {
				s += this->dig_sep;
			}
		}
		return s;
	}


private:
};

int test_floaty();
uint16_t exponent_biased_x8664(double);
uint16_t exponent_biased_x8664_m2(double);
int32_t exponent_unbiased_x8664(double);
int64_t significand_x8664(double);
uint8_t signbit_x8664(double);
bool isnan(double);
int test_exponent_x8664();

int probe_radix();
int test_probe_radix();

//
// Computes the minimum number of digits required to represent arg1 (base 10) in the base
// given by arg 2.  
//
int required_digits(int,int);
int test_required_digits();


