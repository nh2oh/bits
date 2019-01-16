#include "evens_to_front.h"
#include <iostream>


int test_evens_to_front() {
	
	std::vector<int> a {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
	auto a_ev_end = evens_to_front(a.begin(),a.end());

	for (std::vector<int>::iterator it = a.begin(); it != a.end(); ++it) {
		std::cout << *it;
		if (it == a_ev_end) {
			std::cout << "*, ";
		} else {
			std::cout << ", ";
		}
	} 
	std::cout << "\n\n";

	// All values even
	std::vector<int> b {0,2,2,14,4,52,6,72,8,90,10,0,12,4};
	auto b_ev_end = evens_to_front(b.begin(),b.end());
	for (std::vector<int>::iterator it = b.begin(); it != b.end(); ++it) {
		std::cout << *it;
		if (it == b_ev_end) {
			std::cout << "*, ";
		} else {
			std::cout << ", ";
		}
	}
	std::cout << "\n\n";

	// No values even
	std::vector<int> c {1,1,3,5,3,55,7,77,9,89,11,1,11,41};
	auto c_ev_end = evens_to_front(c.begin(),c.end());
	for (std::vector<int>::iterator it = c.begin(); it != c.end(); ++it) {
		std::cout << *it;
		if (it == c_ev_end) {
			std::cout << "*, ";
		} else {
			std::cout << ", ";
		}
	}
	std::cout << "\n\n";

	// Empty vector
	std::vector<int> d {};
	auto d_ev_end = evens_to_front(d.begin(),d.end());
	for (std::vector<int>::iterator it = d.begin(); it != d.end(); ++it) {
		std::cout << *it;
		if (it == d_ev_end) {
			std::cout << "*, ";
		} else {
			std::cout << ", ";
		}
	}
	std::cout << "\n\n";

	// std::vector<double> should not compile
	/*std::vector<double> e {1.0,0.0,2.3,27.15,2.0};
	auto e_ev_end = evens_to_front(e.begin(),e.end());
	for (std::vector<double>::iterator it = e.begin(); it != e.end(); ++it) {
		std::cout << *it;
		if (it == e_ev_end) {
			std::cout << "*, ";
		} else {
			std::cout << ", ";
		}
	}
	std::cout << "\n\n";*/

	return 0;
}




