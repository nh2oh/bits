#pragma once
#include <cstdint>  // CHAR_BIT
#include <string>

template<typename T>
constexpr size_t nbytes(T in) {
	return sizeof(T);
};

template<typename T>
constexpr size_t nbits(T in) {
	return CHAR_BIT*sizeof(T);
};


template<typename T>
int ones(T in) {
	unsigned char *p = static_cast<unsigned char*>(static_cast<void*>(&in));

	int count {0};
	for (int i=0; i<sizeof(T)/sizeof(unsigned char); ++i) {
		char mask {1};
		for (int j=0; j<8; ++j) {
			if (mask & *p) { ++count; }
			mask = mask << 1;
		}
		++p;
	}

	return count;
};



template<typename T>
std::string bitprinter(T in) {
	unsigned char *p = static_cast<unsigned char*>(static_cast<void*>(&in));

	std::string s {};  s.reserve(nbits(in));
	for (int i=0; i<nbytes(in); ++i) {
		unsigned char mask {1};
		for (int j=0; j<nbits(mask); ++j) {
			s += (mask & *p) ? '1' : '0';
			mask = mask << 1;
		}
		++p;
	}

	return s;
};


