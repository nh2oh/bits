#include <iostream>
#include <filesystem>
#include <string>
#include <algorithm>
#include <cmath>
#include "bitcounter.h"
#include "wfind.h"
#include "algs_numeric.h"
#include "array_algs.h"
#include "str_algs.h"
#include "exvol.h"
#include "unsorted_probs.h"
#include "floaty.h"
#include "bigint.h"


int main() {
	test_probe_radix();
	test_exponent_x8664();
	test_floaty();
	test_required_digits();

	//test_print_b256();
	//test_dedup();
	test_hamming_dist();
	test_pwr3();
	test_reverse_chunk_order();
	test_shift_to_end();
	test_dbkrot();
	test_colid2int();

	test_dbk_shift_left();
	test_reverse_digits();
	test_find_first_uparen();
	test_reverse_words();
	test_reverse();

	test_matrix_mult();
	test_matrix_add();
	test_matrix_subt();
	test_dotp();
	test_cnorm();

	tests_ones();
	tests_bitprinter();
	tests_rbyteorder();
	test_evens_to_front();
	test_dnfp();
	test_inc_dec_arry();
	test_insort();

	/*
	std::filesystem::path dictpath {"D:\\cpp\\nh2oh\\bits\\x64\\Debug\\words.txt"};
	auto dict = load_dict(dictpath);
	*/
	/*
	while (true) {
		std::cout << "input letter-set[, result-size]:  ";
		param_set_t curr_params {};
		std::getline(std::cin, curr_params.permit_only);
		//std::cin >> curr_params.permit_only;
		curr_params.require_num_letters = curr_params.permit_only.size();
		
		auto sresult = search_dict(dict,curr_params);
		std::cout << sresult << "------------------------------" << std::endl;
	}*/

	/*
	param_set_t ws_params {7, "aabcddiknpsy"};
	auto sresult = search_dict(dict,ws_params);
	std::cout << sresult << std::endl;
	*/

	//int newint = swap_bits(2,0,1);

	/*
	int myint {3};
	double mydbl {-1.0};
	double mydbl2 {1.0};
	mydbl2 /= (mydbl2-1);

	struct mystruct1_t {
		int a {0};
		int b {0};
		bool c {false};
		bool d {false};
	};
	struct mystruct2_t {
		int a {0};
		bool c {false};
		int b {0};
		bool d {false};
	};
	

	constexpr int sz_myint = nbits(-1.0);
	

    
	std::cout << "bitprinter(myint) == " << bitprinter(myint) << ";  ones(myint) == " << ones(myint) << "\n"; 
    std::cout << "bitprinter(mydbl) == " << bitprinter(mydbl) << ";  ones(mydbl) == " << ones(mydbl) << "\n"; 
	std::cout << "bitprinter(mydbl2) == " << bitprinter(mydbl2) << ";  ones(mydbl2) == " << ones(mydbl2) << "\n"; 
	std::cout << "bitprinter(true) == " << bitprinter(true) << ";  ones(true) == " << ones(true) << "\n"; 
	std::cout << "bitprinter(false) == " << bitprinter(false) << ";  ones(false) == " << ones(false) << "\n"; 
	std::cout << "bitprinter(mystruct1_t) == " << bitprinter(mystruct1_t{1,2,false,true}) << ";  ones(mystruct1_t{1,2,false,true}) == " << ones(mystruct1_t{1,2,false,true}) << "\n"; 
	std::cout << "bitprinter(mystruct2_t) == " << bitprinter(mystruct2_t{1,false,2,true}) << ";  ones(mystruct2_t{1,false,2,true}) == " << ones(mystruct2_t{1,false,2,true}) << "\n"; 
	

	
	std::cout << "bitprinter(myint) == " << bitprinter(myint) << "\n"; 
	unsigned char *p_myint = static_cast<unsigned char*>(static_cast<void*>(&myint));
	std::cout << "bitprinter(*(p_myint+0)) == " << bitprinter(*(p_myint+0)) << "\n"; 
	std::cout << "bitprinter(*(p_myint+1)) == " << bitprinter(*(p_myint+1)) << "\n"; 
	std::cout << "bitprinter(*(p_myint+2)) == " << bitprinter(*(p_myint+2)) << "\n"; 
	std::cout << "bitprinter(*(p_myint+3)) == " << bitprinter(*(p_myint+3)) << "\n"; 
	std::cout << "bitprinter(rbyteorder(myint)) == " << bitprinter(rbyteorder(myint)) << "\n"; 

	
	std::cout << "bitprinter(mydbl2) == " << bitprinter(mydbl2) << "\n"; 
	auto rev_mydbl2 = rbyteorder(mydbl2);
	std::cout << "bitprinter(rbyteorder(mydbl2)) == " << bitprinter(rbyteorder(mydbl2)) << "\n"; 

	void *vp_rev_mydbl2 = static_cast<void*>(&rev_mydbl2);
	double *dp_revmydbl2 = static_cast<double*>(vp_rev_mydbl2);
	double dbl_revmydbl2 = *dp_revmydbl2;
	std::cout << "bitprinter(dbl_revmydbl2) == " << bitprinter(dbl_revmydbl2) << "\n"; 
	std::cout << "bitprinter(rbyteorder(dbl_revmydbl2)) == " << bitprinter(rbyteorder(dbl_revmydbl2)) << "\n"; 
	//std::cout << dbl_revmydbl2 << std::endl;
	*/
	

	return 0;
}

