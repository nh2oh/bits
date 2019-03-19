#pragma once
#include <string>
#include <array>
#include <vector>
#include <cstdint>
/*
template<int N>
class bigint {
public:
	bigint();
	std::string print() const;

	// LE
	int sig_digits() {
		int n=N;
		while (n>0 && this->d_[--n]==0) {}
		return n;
	}

	// LE
	binint<N>& operator+=(const bigint<N>& rhs) {
		int c {0};
		for (int i=0; i<N; ++i) {
			int s = this->d_[i] + rhs.d_[i] + c;
			this->d_[i] = s%256;
			c = s/256;
			//int s = this->d_[i] + rhs.d_[i] + c;
			//c = s - std::numeric_limits<uint8_t>::max();
			//if (c > 0) {
			//	s = std::numeric_limits<uint8_t>::max();
			//} else {
			//	c = 0;
			//}
			//this->d_[i] = s;
		}
		//if (c>0) {
		//	// overflow
		//}
		return this;
	};

	// BE
	binint<N>& operator*=(const bigint<N>& rhs) {
		//
		//    rr  rh  rs
		//  x ll  lh  ls
		//

		// => conv(lhs,rhs)
		std::array<int,2*N> nocarry {0};
		for (int lhs_i=0; lhs_i<N; ++lhs_i) {
			int lhs_idx_init = lhs_i;
			for (int rhs_i=0; rhs_i<N; ++rhs_i) {
				nocarry[lhs_idx_init+rhs_i] += this->d_[lhs_i]*rhs.d_[rhs_i];
			}
		}

		int c {0};
		for (int i=0; i<nocarry.size(); ++i) {
			int s = nocarry[i] + c;
			this->d_[i] = s%256;
			int c = s/256;
		}
		// if (c>0) { // overflow }

		return this;
	};
private:
	std::array<uint8_t,N> d_ {};
};


std::string print_b256(int);
int test_print_b256();
*/

