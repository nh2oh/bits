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
	matrix<int,3,3> ans_a32_a23 {std::array<int,9>{39,54,69,49,68,87,59,82,105}};

	std::cout << print(a32_a23) << std::endl;
	std::cout << print(ans_a32_a23) << std::endl;

	if (a23_a32 != ans_a23_a32) {
		std::abort();
	}
	if (a32_a23 != ans_a32_a23) {
		std::abort();
	}
	return 0;
}


int test_matrix_add() {
	matrix<int,2,3> a23 {std::array<int,6>{1,2,3, 4, 5, 6}};
	matrix<int,2,3> b23 {std::array<int,6>{7,8,9,10,11,12}};
	auto a23_p_b23 = a23+b23;
	auto b23_p_a23 = b23+a23;
	matrix<int,2,3> ans_a23_p_b23 {std::array<int,6>{8,10,12,14,16,18}};

	if (a23_p_b23 != ans_a23_p_b23) {
		std::abort();
	}
	if (b23_p_a23 != ans_a23_p_b23) {
		std::abort();
	}
	return 0;
}

int test_matrix_subt() {
	matrix<int,2,3> a23 {std::array<int,6>{1,2,3, 4, 5, 6}};
	matrix<int,2,3> b23 {std::array<int,6>{7,8,9,10,11,12}};
	auto a23_m_b23 = a23-b23;
	auto b23_m_a23 = b23-a23;
	matrix<int,2,3> ans_a23_m_b23 {std::array<int,6>{-6,-6,-6,-6,-6,-6}};
	matrix<int,2,3> ans_b23_m_a23 {std::array<int,6>{6,6,6,6,6,6}};

	if (a23_m_b23 != ans_a23_m_b23) {
		std::abort();
	}
	if (b23_m_a23 != ans_b23_m_a23) {
		std::abort();
	}
	return 0;
}


int test_dotp() {
	std::array<int,6> a {std::array<int,6>{1,2,3, 4, 5, 6}};
	std::array<int,6> b {std::array<int,6>{7,8,9,10,11,12}};
	if (dotprod(a,b) != 217 || dotprod(b,a) != 217) {
		std::abort();
	}

	return 0;
}

int test_cnorm() {
	matrix<double,6,1> a {std::array<double,6>{1.0,2.0,3.0, 4.0, 5.0, 6.0}};
	matrix<double,3,1> b {std::array<double,3>{7.0,8.0,9.0}};
	std::cout << print(a.cnorm()) << "\n\n" << print(b.cnorm()) << std::endl;
	/*if (std::round(a.cnorm()*1000) != 21208) {
		std::abort();
	}
	if (std::round(b.cnorm()*1000) != 57889) {
		std::abort();
	}*/

	return 0;
}







