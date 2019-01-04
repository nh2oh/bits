#include <iostream>
#include "bitcounter.h"

int main() {
	int myint {3};
	double mydbl {-1.0};
	constexpr int sz_myint = nbits(-1.0);

    std::cout << "bitprinter(myint) == " << bitprinter(myint) << ";  ones(myint) == " << ones(myint) << "\n"; 
    std::cout << "bitprinter(mydbl) == " << bitprinter(mydbl) << ";  ones(mydbl) == " << ones(mydbl) << "\n"; 

	return 0;
}

