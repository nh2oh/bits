#pragma once
#include <string>
#include <array>
#include <vector>
#include <cstdint>

template<int N>
class bigint {
public:
	bigint();
	std::string print() const;

	// LE
	binint<N>& operator+=(const bigint<N>& rhs) {
		int c {0};
		for (int i=0; i<N; ++i) {
			int s = this->d_[i] + rhs.d_[i] + c;
			c = s - std::numeric_limits<uint8_t>::max();
			if (c > 0) {
				s = std::numeric_limits<uint8_t>::max();
			} else {
				c = 0;
			}
			this->d_[i] = s;
		}
		return this;
	};

	binint<N>& operator*=(const bigint<N>& rhs) {
		int c {0};
		for (int i=0; i<N; ++i) {
			int s = this->d_[i] + rhs.d_[i] + c;
			c = s - std::numeric_limits<uint8_t>::max();
			if (c > 0) {
				s = std::numeric_limits<uint8_t>::max();
			} else {
				c = 0;
			}
			this->d_[i] = s;
		}
		return this;
	};
private:
	std::array<uint8_t,N> d_ {};
};


std::string print_b256(int);
int test_print_b256();


