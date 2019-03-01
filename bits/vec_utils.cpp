#include "vec_utils.h"
#include <vector>
#include <string>


// vector to be printed, optional int idx of an element to be printed w/a '*'
std::string printv(const std::vector<int>& v, int idx_star) { 
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
