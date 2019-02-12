#include "exvol.h"
#include <cmath>  // std::pow()
#include <algorithm>  // std::max()
#include <array>
#include <random>
#include <exception>
#include <iostream>


int test_matrix_mult() {
	matrix<int,2,3> a23 {};
	a23.setrow(0,std::array<int,3>{1,2,3});
	a23.setrow(1,std::array<int,3>{4,5,6});
	matrix<int,3,2> a32 {};
	a32.setcol(0,std::array<int,3>{7,9,11});
	a32.setcol(1,std::array<int,3>{8,10,12});

	auto a23_a32 = a23*a32;
	auto a32_a23 = a32*a23;

	std::cout << print(a23) << std::endl;
	std::cout << print(a32) << std::endl;
	std::cout << print(a23_a32) << std::endl;
	std::cout << print(a32_a23) << std::endl;

	matrix<int,2,2> ans_a23_a32 {};
	ans_a23_a32.setrow(0,std::array<int,2>{58,64});
	ans_a23_a32.setrow(1,std::array<int,2>{139,154});

	if (a23_a32 != ans_a23_a32) {
		std::abort();
	}

	return 0;
}


















