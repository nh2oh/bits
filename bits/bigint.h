#pragma once
#include <string>
#include <array>
#include <vector>
#include <cstdint>

template<int N> class bigint {
public:
	bigint();
	std::string print() const;

	template<typename Tlhs>

private:
	std::array<uint8_t,N> d_ {};
};


std::string print_b256(int);
int test_print_b256();


