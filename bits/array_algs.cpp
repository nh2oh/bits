#include "array_algs.h"
#include "vec_utils.h"
#include <vector>
#include <iostream>
#include <string>  // std::to_string()
#include <exception>

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


int test_dnfp() {
	std::cout << "---------------------------------------------------\n"
		<< "test_dnfp(): \n";

	// vector to be printed, optional int idx of an element to be printed w/a '*'
	auto printvec = [](const std::vector<int>& v, int idx_star=-1){ 
		std::string s {'{'};
		for (const auto& e : v) {
			s += std::to_string(e);
			if (idx_star==0) {
				s += '*';
			}
			s += ',';
			--idx_star;
		};
		s.pop_back();
		s += '}';
		return s;
	};

	// No repeats, already sorted
	std::cout << "No repeats, already sorted\n";
	std::vector<int> a_init {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
	for (int idx_pvt=0; idx_pvt<a_init.size(); ++idx_pvt) {
		std::cout << "a_init = " << printvec(a_init,idx_pvt) << "\n";
		auto a = a_init;
		auto a_dnfp = dnfp(a.begin(),a.end(),a.begin()+idx_pvt);
		std::cout << printvec(a) << "\n";
	}
	std::cout << std::endl;

	// All values even
	std::cout << "All values even\n";
	std::vector<int> b_init {0,2,2,14,4,52,6,72,8,90,10,0,12,4};
	for (int idx_pvt=0; idx_pvt<b_init.size(); ++idx_pvt) {
		std::cout << "b_init = " << printvec(b_init,idx_pvt) << "\n";
		auto b = b_init;
		auto b_dnfp = dnfp(b.begin(),b.end(),b.begin()+idx_pvt);
		std::cout << printvec(b) << "\n";
	}
	std::cout << std::endl;

	// Empty vector
	std::cout << "Empty vector\n";
	std::vector<int> c_init {};
	for (int idx_pvt=0; idx_pvt<c_init.size(); ++idx_pvt) {
		std::cout << "c_init = " << printvec(c_init,idx_pvt) << "\n";
		auto c = c_init;
		auto c_dnfp = dnfp(c.begin(),c.end(),c.begin()+idx_pvt);
		std::cout << printvec(c) << "\n";
	}
	std::cout << std::endl;

	// Vector w/ one element
	std::cout << "Vector w/ one element\n";
	std::vector<int> d_init {7};
	for (int idx_pvt=0; idx_pvt<d_init.size(); ++idx_pvt) {
		std::cout << "d_init = " << printvec(d_init,idx_pvt) << "\n";
		auto d = d_init;
		auto d_dnfp = dnfp(d.begin(),d.end(),d.begin()+idx_pvt);
		std::cout << printvec(d) << "\n";
	}
	std::cout << std::endl;

	// Vector w/ two elements
	std::cout << "Vector w/ two elements\n";
	std::vector<int> e_init {7,1};
	for (int idx_pvt=0; idx_pvt<e_init.size(); ++idx_pvt) {
		std::cout << "e_init = " << printvec(e_init,idx_pvt) << "\n";
		auto e = e_init;
		auto e_dnfp = dnfp(e.begin(),e.end(),e.begin()+idx_pvt);
		std::cout << printvec(e) << "\n";
	}
	std::cout << std::endl;

	// All elements identical
	std::cout << "All elements identical\n";
	std::vector<int> f_init {5,5,5,5,5,5,5};
	for (int idx_pvt=0; idx_pvt<f_init.size(); ++idx_pvt) {
		std::cout << "f_init = " << printvec(f_init,idx_pvt) << "\n";
		auto f = f_init;
		auto f_dnfp = dnfp(f.begin(),f.end(),f.begin()+idx_pvt);
		std::cout << printvec(f) << "\n";
	}
	std::cout << std::endl;

	return 0;
}



int test_insort() {
	std::cout << "---------------------------------------------------\n"
		<< "test_insort(): \n";

	// vector to be printed, optional int idx of an element to be printed w/a '*'
	auto printvec = [](const std::vector<int>& v, int idx_star=-1){ 
		std::string s {'{'};
		for (const auto& e : v) {
			s += std::to_string(e);
			if (idx_star==0) {
				s += '*';
			}
			s += ',';
			--idx_star;
		};
		s.pop_back();
		s += '}';
		return s;
	};

	// Already sorted
	std::cout << "Sorted input\n";
	std::vector<int> a {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
	std::cout << "a = " << printvec(a) << "\n";
	insort(a.begin(),a.end());
	std::cout << "a = " << printvec(a) << "\n";
	std::cout << std::endl;

	// All values even
	std::cout << "All values even\n";
	std::vector<int> b {0,2,2,14,4,52,6,72,8,90,10,0,12,4};
	std::cout << "b = " << printvec(b) << "\n";
	insort(b.begin(),b.end());
	std::cout << "b = " << printvec(b) << "\n";
	std::cout << std::endl;

	// Empty input
	std::cout << "Empty input\n";
	std::vector<int> c {};
	std::cout << "c = " << printvec(c) << "\n";
	insort(c.begin(),c.end());
	std::cout << "c = " << printvec(c) << "\n";
	std::cout << std::endl;

	// Size == 1
	std::cout << "Input size == 1\n";
	std::vector<int> d {7};
	std::cout << "d = " << printvec(d) << "\n";
	insort(d.begin(),d.end());
	std::cout << "d = " << printvec(d) << "\n";
	std::cout << std::endl;

	// Size == 2
	std::cout << "Input size == 2\n";
	std::vector<int> e {7,4};
	std::cout << "e = " << printvec(e) << "\n";
	insort(e.begin(),e.end());
	std::cout << "e = " << printvec(e) << "\n";
	std::cout << std::endl;

	return 0;
}



int test_reverse() {
	// vector to be printed, optional int idx of an element to be printed w/a '*'
	auto printvec = [](const std::vector<int>& v, int idx_star=-1){ 
		std::string s {'{'};
		for (const auto& e : v) {
			s += std::to_string(e);
			if (idx_star==0) {
				s += '*';
			}
			s += ',';
			--idx_star;
		};
		if (v.size()>0) {
			s.pop_back();
		}
		s += '}';
		return s;
	};

	std::vector<int> a {1,2,3,4,5,6,7,8,9};
	std::cout << printvec(a) << " => ";
	dbkreverse(a.begin(),a.end());
	std::cout << printvec(a) << std::endl;


	std::vector<int> b {};
	std::cout << printvec(b) << " => ";
	dbkreverse(b.begin(),b.end());
	std::cout << printvec(b) << std::endl;

	return 0;
}


int test_dbk_shift_left() {
	// vector to be printed, optional int idx of an element to be printed w/a '*'
	auto printvec = [](const std::vector<int>& v, int idx_star=-1){ 
		std::string s {'{'};
		for (const auto& e : v) {
			s += std::to_string(e);
			if (idx_star==0) {
				s += '*';
			}
			s += ',';
			--idx_star;
		};
		if (v.size()>0) {
			s.pop_back();
		}
		s += '}';
		return s;
	};

	std::vector<int> a {};


	a = std::vector<int> {1,2,3,4,5,6,7,8,9};
	std::cout << printvec(a) << " => ";
	auto rit = dbk_shift_left(a.begin()+2,a.begin()+6,0);
	std::cout << printvec(a,rit-a.begin()) << "; " << std::to_string(*rit) << std::endl;

	a = std::vector<int> {1,2,3,4,5,6,7,8,9};
	std::cout << printvec(a) << " => ";
	rit = dbk_shift_left(a.begin()+2,a.begin()+6,1);
	std::cout << printvec(a,rit-a.begin()) << "; " << std::to_string(*rit) << std::endl;

	a = std::vector<int> {1,2,3,4,5,6,7,8,9};  // 1,2,5,6,5*,6,7,8,9
	std::cout << printvec(a) << " => ";
	rit = dbk_shift_left(a.begin()+2,a.begin()+6,2);
	std::cout << printvec(a,rit-a.begin()) << "; " << std::to_string(*rit) << std::endl;

	a = std::vector<int> {1,2,3,4,5,6,7,8,9};  // 1,2,6,4*,5,6,7,8,9
	std::cout << printvec(a) << " => ";
	rit = dbk_shift_left(a.begin()+2,a.begin()+6,3);
	std::cout << printvec(a,rit-a.begin()) << "; " << std::to_string(*rit) << std::endl;

	a = std::vector<int> {1,2,3,4,5,6,7,8,9};  // 1,2,3*,4,5,6,7,8,9
	std::cout << printvec(a) << " => ";
	rit = dbk_shift_left(a.begin()+2,a.begin()+6,4);
	std::cout << printvec(a,rit-a.begin()) << "; " << std::to_string(*rit) << std::endl;

	a = std::vector<int> {1,2,3,4,5,6,7,8,9};  // 1,2,3*,4,5,6,7,8,9
	std::cout << printvec(a) << " => ";
	rit = dbk_shift_left(a.begin()+2,a.begin()+6,5);
	std::cout << printvec(a,rit-a.begin()) << "; " << std::to_string(*rit) << std::endl;

	return 0;
}


int test_shift_to_end() {
	std::vector<int> v_init {0,1,2,3,4,5,6,7,8,9};

	for (int i=0; i<v_init.size(); ++i) {
		auto v = v_init;
		std::cout << printv(v,i) << " => ";
		auto rv = shift_to_end(v.begin()+i,v.end());
		std::cout << printv(v) << "; *rv== " << std::to_string(*rv) << std::endl;
	}

	return 0;
}


int test_dbkrot() {
	std::vector<int> v_init {0,1,2,3,4,5,6,7,8,9};

	for (int i=1; i<v_init.size(); ++i) {
		auto v = v_init;
		std::cout << printv(v,i) << " => ";
		auto rv = dbkrot(v.begin(),v.end(),v.begin()+i);
		std::cout << printv(v) << "; *rv== " << std::to_string(*rv) << std::endl;
	}

	return 0;
}


int test_dedup() {
	std::vector<int> v {};
	std::vector<int> ans {};
	std::vector<int>::iterator r {};
	std::vector<int>::iterator r_ans {};

	/*v = std::vector<int> {0,1,2,3,4,5,6,7,8,9};
	ans = v; r_ans = v.begin()+0;
	std::cout << "v == " << printv(v) << ";  dedup(v) == ";
	r = dedup(v.begin(),v.end());
	std::cout << printv(v,r-v.begin()) << std::endl;
	if (r!=r_ans) {
		std::cout << "r!=r_ans";  std::abort();
	}

	v = std::vector<int> {0,1,2,2,3,4,5,6,7,8,9};
	ans = std::vector<int> {2,0,1,2,3,4,5,6,7,8,9};  r_ans=v.begin()+1;
	std::cout << "v == " << printv(v) << ";  dedup(v) == ";
	r = dedup(v.begin(),v.end());
	std::cout << printv(v,r-v.begin()) << std::endl;
	if (r!=r_ans) {
		std::cout << "r!=r_ans";  std::abort();
	}

	v = std::vector<int> {0,1,2,3,4,5,6,7,8,9,9};
	ans = v; r_ans = v.begin()+1;
	std::cout << "v == " << printv(v) << ";  dedup(v) == ";
	r = dedup(v.begin(),v.end());
	std::cout << printv(v,r-v.begin()) << std::endl;
	if (r!=r_ans) {
		std::cout << "r!=r_ans";  std::abort();
	}

	v = std::vector<int> {0,1,2,2,3,4,4,4,5,6,7,7,7,7,7,8,9};
	ans = std::vector<int> {2,4,4,7,7,7,7,0,1,2,3,4,5,6,7,8,9};  r_ans=v.begin()+7;
	std::cout << "v == " << printv(v) << ";  dedup(v) == ";
	r = dedup(v.begin(),v.end());
	std::cout << printv(v,r-v.begin()) << std::endl;
	if (r!=r_ans) {
		std::cout << "r!=r_ans";  std::abort();
	}

	v = std::vector<int> {};
	ans = std::vector<int> {};  r_ans=v.begin()+0;
	std::cout << "v == " << printv(v) << ";  dedup(v) == ";
	r = dedup(v.begin(),v.end());
	std::cout << printv(v,r-v.begin()) << std::endl;
	if (r!=r_ans) {
		std::cout << "r!=r_ans";  std::abort();
	}*/


	/*v = std::vector<int>   {1,2,3};
	ans = std::vector<int> {3,1,2};  r_ans=v.begin()+1;  // *=>1
	std::cout << "v == " << printv(v) << ";  to_front(v) == ";
	r = to_front(v.begin(),v.begin()+2);
	std::cout << printv(v,r-v.begin()) << std::endl;

	std::cout << "v == " << printv(v) << ";  to_front(v) == ";
	r = to_front(v.begin()+1,v.begin()+2);
	std::cout << printv(v,r-v.begin()) << std::endl;
	if (r!=r_ans) {
		auto n = r-v.begin();
		std::cout << "r!=r_ans";  std::abort();
	}*/


	v = std::vector<int>   {1,1,1};
	ans = std::vector<int> {1,1,1};  r_ans=v.begin()+2;
	std::cout << "v == " << printv(v) << ";  dedup(v) == ";
	r = dedup(v.begin(),v.end());
	std::cout << printv(v,r-v.begin()) << std::endl;
	if (r!=r_ans) {
		auto n = r-v.begin();
		std::cout << "r!=r_ans";  std::abort();
	}

	return 0;
}





