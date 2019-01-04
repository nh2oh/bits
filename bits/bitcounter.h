#pragma once
#include <string>

template<typename T>
constexpr int nbytes(T in) {
	return sizeof(T)/sizeof(unsigned char);
};

template<typename T>
constexpr int nbits(T in) {
	return 8*(sizeof(T)/sizeof(unsigned char));
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

	std::string s {};  s.reserve(nbits(in)); //s.reserve(8*(sizeof(T)/sizeof(unsigned char)));
	for (int i=0; i<nbytes(in)/*sizeof(T)/sizeof(unsigned char)*/; ++i) {
		unsigned char mask {1};
		for (int j=0; j<8; ++j) {
			if (mask & *p) {
				s += '1';
			} else {
				s += '0';
			}
			mask = mask << 1;
		}
		++p;
	}

	return s;
};


