#include <iostream>
#include "bitcounter.h"

int main() {
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
	return 0;
}

