#include "wfind.h"
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <fstream>
#include <exception>
#include <iostream>



std::string load_dict(const std::filesystem::path& fp) {
	std::ifstream f {fp,std::ios::in};
	if (!f.is_open() || f.fail()) {
		std::cout << "!f.is_open() || f.fail() for fp = " << fp.string() << "\n";
		std::abort();
	}

	// TODO:  Enforce some reasonable max size
	std::string result {};  result.reserve(std::filesystem::file_size(fp));
	std::string curr_line {};  result.reserve(100);
	while (std::getline(f,curr_line,'\n')) { 
		result += curr_line;
		result += '\n';
		if (result.capacity()-result.size() < 100) {
			result.reserve(100);
		}
		curr_line.clear();
	}
	f.close();

	return result;
}


std::string search_dict(const std::string& dict, const param_set_t& p) {
	std::string result {};  result.reserve(5000);

	// returns true if c is not in the permitted set
	auto char_not_allowed = [&p](const char c) -> bool {
		return std::find(p.permit_only.begin(),p.permit_only.end(),c)==p.permit_only.end();
	};

	for (auto it=dict.begin(); it!=dict.end(); ++it) {
		auto it_beg = it;
		it = std::find(it_beg,dict.end(),'\n');

		if (p.require_num_letters != 0 && (it-it_beg) != p.require_num_letters) {
			continue;
		}

		if (p.permit_only.size() > 0) {
			auto it_forbidden = std::find_if(it_beg,it,char_not_allowed);
			if (it_forbidden != it) {
				continue;  // *it_forbidden in [it_beg,it) is not in p.permit_only
			}
		}

		std::copy(it_beg,it+1,std::back_inserter(result));
	}

	return result;
}







