#include "exvol.h"
#include <cmath>  // std::pow()
#include <algorithm>  // std::max()
#include <array>
#include <random>
#include <exception>
#include <iostream>


int test_matrix_mult() {
	matrix<int,2,3> a23 {std::array<int,6>{1,2,3,4,5,6}};
	matrix<int,3,2> a32 {std::array<int,6>{7,8,9,10,11,12}};
	auto a23_a32 = a23*a32;
	auto a32_a23 = a32*a23;
	matrix<int,2,2> ans_a23_a32 {std::array<int,4>{58,64,139,154}};
	matrix<int,3,3> ans_a32_a23 {std::array<int,9>{0,0,0,0,0,0,0,0,0}};

	std::cout << print(a23) << std::endl;
	std::cout << print(a32) << std::endl;
	std::cout << print(a23_a32) << std::endl;
	std::cout << print(a32_a23) << std::endl;

	


	if (a23_a32 != ans_a23_a32) {
		std::abort();
	}

	return 0;
}


















