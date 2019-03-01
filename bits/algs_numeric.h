#pragma once


// Increment by 1 a decimal "number" represented as an array with each element a digit on [0,9].  
// Returns true on success, false on overflow
template<typename It>
bool inc_dec_arry(It beg, It end) {
	bool carry {false};

	while (end != beg) {
		--end;
		if (*end < 9) {
			*end += 1;
			carry = false;
			break;
		} else {
			carry = true;
			*end = 0;
		}
	}

	return !carry;
}
bool test_inc_dec_arry();


//
// Reverse digits
//
int reverse_digits(int);
int test_reverse_digits();

//
// Checks if input is a power of 3
//
bool pwr3(int);
int test_pwr3();

int hamming_dist(int, int);
int test_hamming_dist();



