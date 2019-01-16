#pragma once
#include <cstdint>  // CHAR_BIT
#include <string>
#include <array>

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
	for (int i=0; i<sizeof(T); ++i) {
		unsigned char mask {1};
		for (int j=0; j<nbits(in); ++j) {
			if (mask & *p) { ++count; }
			mask = mask << 1;
		}
		++p;
	}

	return count;
};

int tests_ones();


template<typename T>
std::array<unsigned char,sizeof(T)> rbyteorder(T in) {
	unsigned char *p_in = static_cast<unsigned char*>(static_cast<void*>(&in));
	std::array<unsigned char,sizeof(T)> result {};

	unsigned char *p_r = static_cast<unsigned char*>(static_cast<void*>(&result));
	for (int i=0; i<sizeof(T); ++i) {
		*p_r = *(p_in+sizeof(T)-1-i);
		++p_r;
	}

	return result;
};

int tests_rbyteorder();


// TODO:  memcpy() ?
template<typename T>
std::array<unsigned char,sizeof(T)> to_byte_array(const T& in) {
	std::array<unsigned char,sizeof(T)> result {};
	unsigned char *p_in = static_cast<unsigned char*>(static_cast<void*>(&in));
	
	unsigned char *p_result = &result;
	for (int i=0; i<sizeof(T); ++i) {
		*p_result = *p_in;
		++p_in; ++p_result;
	}

	return result;
}

template<typename T>
T from_byte_array(const std::array<unsigned char,sizeof(T)> *in) {
	T result {};
	const unsigned char *p_result = static_cast<unsigned char*>(static_cast<void*>(&result));
	
	for (int i=0; i<sizeof(T); ++i) {
		*p_result = *in;
		++in; ++p_result;
	}

	return result;
}

template<typename T>
std::string bitprinter(T in, const char byte_sep = '|') {
	unsigned char *p = static_cast<unsigned char*>(static_cast<void*>(&in));

	std::string s {};  s.reserve(nbits(in));
	for (int i=0; i<nbytes(in); ++i) {
		unsigned char mask {0x80};
		for (int j=0; j<nbits(mask); ++j) {
			s += (mask & *p) ? '1' : '0';
			mask = mask >> 1;
		}
		s += byte_sep;
		++p;
	}

	return s;
};

int tests_bitprinter();


