#include <iostream>
#include <filesystem>
#include "bitcounter.h"
#include "wfind.h"

int main() {
	std::filesystem::path dictpath {"C:\\Users\\ben\\Desktop\\cpp\\git\\bits\\x64\\Debug\\words.txt"};
	auto dict = load_dict(dictpath);
	param_set_t ws_params {5, "achdcekmorrywz"};
	auto sresult = search_dict(dict,ws_params);
	std::cout << sresult << std::endl;


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

    /*
	std::cout << "bitprinter(myint) == " << bitprinter(myint) << ";  ones(myint) == " << ones(myint) << "\n"; 
    std::cout << "bitprinter(mydbl) == " << bitprinter(mydbl) << ";  ones(mydbl) == " << ones(mydbl) << "\n"; 
	std::cout << "bitprinter(mydbl2) == " << bitprinter(mydbl2) << ";  ones(mydbl2) == " << ones(mydbl2) << "\n"; 
	std::cout << "bitprinter(true) == " << bitprinter(true) << ";  ones(true) == " << ones(true) << "\n"; 
	std::cout << "bitprinter(false) == " << bitprinter(false) << ";  ones(false) == " << ones(false) << "\n"; 
	std::cout << "bitprinter(mystruct1_t) == " << bitprinter(mystruct1_t{1,2,false,true}) << ";  ones(mystruct1_t{1,2,false,true}) == " << ones(mystruct1_t{1,2,false,true}) << "\n"; 
	std::cout << "bitprinter(mystruct2_t) == " << bitprinter(mystruct2_t{1,false,2,true}) << ";  ones(mystruct2_t{1,false,2,true}) == " << ones(mystruct2_t{1,false,2,true}) << "\n"; 
	*/

	/*
	std::cout << "bitprinter(myint) == " << bitprinter(myint) << "\n"; 
	unsigned char *p_myint = static_cast<unsigned char*>(static_cast<void*>(&myint));
	std::cout << "bitprinter(*(p_myint+0)) == " << bitprinter(*(p_myint+0)) << "\n"; 
	std::cout << "bitprinter(*(p_myint+1)) == " << bitprinter(*(p_myint+1)) << "\n"; 
	std::cout << "bitprinter(*(p_myint+2)) == " << bitprinter(*(p_myint+2)) << "\n"; 
	std::cout << "bitprinter(*(p_myint+3)) == " << bitprinter(*(p_myint+3)) << "\n"; 
	std::cout << "bitprinter(rbyteorder(myint)) == " << bitprinter(rbyteorder(myint)) << "\n"; 
	*/
	
	std::cout << "bitprinter(mydbl2) == " << bitprinter(mydbl2) << "\n"; 
	auto rev_mydbl2 = rbyteorder(mydbl2);
	std::cout << "bitprinter(rbyteorder(mydbl2)) == " << bitprinter(rbyteorder(mydbl2)) << "\n"; 

	void *vp_rev_mydbl2 = static_cast<void*>(&rev_mydbl2);
	double *dp_revmydbl2 = static_cast<double*>(vp_rev_mydbl2);
	double dbl_revmydbl2 = *dp_revmydbl2;
	std::cout << "bitprinter(dbl_revmydbl2) == " << bitprinter(dbl_revmydbl2) << "\n"; 
	std::cout << "bitprinter(rbyteorder(dbl_revmydbl2)) == " << bitprinter(rbyteorder(dbl_revmydbl2)) << "\n"; 
	//std::cout << dbl_revmydbl2 << std::endl;
	
	

	return 0;
}

