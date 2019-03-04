#pragma once
#include <cstdint>  // CHAR_BIT
#include <string>
#include <array>
#include <iostream>
#include <cstring>  // std::memcpy()

//
// The code for T *change_object_type(U *p) below is taken from:
// From:  http://www.open-std.org/pipermail/ub/2016-February/000565.html
// Author:  Richard Smith richardsmith at googlers.com 
//
// See also: 
// From:  http://www.open-std.org/pipermail/ub/2016-February/000561.html
// Credit:  Hubert Tong hubert.reinterpretcast at gmail.com 
// Commenting on the following sample from Robert Haberlach (rh633 at cam.ac.uk):
// 
//   static_assert(alignof(float)>=alignof(int) && sizeof(float)>=sizeof(int));
//   int foo(float f) {
//     return *std::launder(reinterpret_cast<int*>(&f));
//   }
//
// Type-based aliasing analysis (TBAA) is allowed to determine that the 
// write to "f" and the read from the dereference is not related.  Consider 
// the effects of inlining:
// 
//   int main(void) { return !foo(0.5f); }
//
// becomes (loosely):
//
//   int main(void) {
//     int __ret;
//     {
//       float __f = 0.5f;
//       __ret = *std::launder(reinterpret_cast<int *>(&__f));
//     }
//     return !__ret;
//   }
//
// The implementation is allowed to observe that there are no TBAA-compatible
// reads of the value of __f within its lifetime.  The likely result is that
// the initialization of __f would be optimized away.
//
// Robert Haberlach rh633 at cam.ac.uk :
// Isn't the whole idea that launder's definition is, to some extent, intransparent
// to optimizers?  We're passing a pointer to f into launder.  As long as the analyser
// is told to assume that calls to launder perform what not, it cannot elide the 
// initialization, because launder could read.
// 
// Richard Smith richardsmith at googlers.com :
// launder is known to the optimizer, and is known to not read or write any memory.  
// If it could, that would significantly inhibit optimizations in code that uses it.  
//
//--------------------------------------------------
// 03/04/19
// For example: 
//
// int make_int_nlegit(double d) {
//     int *pint = static_cast<int*>(static_cast<void*>(&d));
//     *pint=5;
//     return static_cast<int>(d);
// }          
//            
// int main(int argc, char **argv) {
//     double mydbl {27.31571};
//     return make_int_nlegit(mydbl);
// }
//
// With Clang x86-64 (Trunk) =>
// make_int_nlegit(double):                   # @make_int_nlegit(double)
//         movq    rax, xmm0
//         movabs  rcx, -4294967296
//         and     rcx, rax
//         or      rcx, 5
//         movq    xmm0, rcx
//         cvttsd2si       eax, xmm0
//         ret
// main:                                   # @main
//         mov     eax, 27
//         ret
//
template<typename T, typename U>
T *change_object_type(U *p) {
	static_assert(sizeof(T) == sizeof(U));
	static_assert(is_trivially_copyable_v<T> && is_trivially_copyable_v<U>);
	char buffer[sizeof(T)];
	std::memcpy(buffer, p, sizeof(T));
	p->~U();
	T *result = new (p) T;
	std::memcpy(result, buffer, sizeof(T));
	return result;
}


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


// TODO:  Untested
template<typename T>
T swap_bits(T in, size_t i, size_t j) {
	static_assert(sizeof(T)>0 || (sizeof(T)==0 && i==0 && j==0));
	if (i>nbits(in)-1 || j>nbits(in)-1 || i<0 || j<0) {
		std::cout << "swap_bits(T in, int8_t i, int8_t j):  "
			<< "i>nbits(T)-1 || j>nbits(T)-1 || i<0 || j<0.  \n"
			<< "Aborting...\n";
		std::abort();
	}

	//size_t Nchar = nbits(unsigned char c {});
	size_t Nchar = 8;
	size_t N = nbits(in);
	unsigned char *p_in = static_cast<unsigned char*>(static_cast<void*>(&in));

	unsigned char m_i = 1<<(i%Nchar);
	unsigned char m_j = 1<<(j%Nchar);

	auto bit_i = ((*(p_in+i/Nchar))>>(i%Nchar))&1;
	auto bit_j = ((*(p_in+j/Nchar))>>(j%Nchar))&1;
	if (bit_i != bit_j) {
	//if (((*(p_in+i/Nchar))>>(i%Nchar))&1 != ((*(p_in+j/Nchar))>>(j%Nchar))&1) {
		*(p_in+i/Nchar) ^= m_i;
		*(p_in+j/Nchar) ^= m_j;
	}

	return in;
};

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


