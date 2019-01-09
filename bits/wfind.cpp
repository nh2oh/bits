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
	//f.open();
	if (!f.is_open() || f.fail()) {
		std::cout << "!f.is_open() || f.fail() for fp = " << fp.string() << "\n";
		std::abort();
	}

	// TODO:  Enforce some reasonable max size
	std::string result {};  result.reserve(std::filesystem::file_size(fp));
	std::string curr_line {};  result.reserve(100);
	while (std::getline(f,curr_line,'\n')) { //(!f.eof() && !f.fail()) {
		//std::getline(f,curr_line,'\n');
		//curr_line += '\n';
		result += curr_line;
		result += '\n';
		if (result.capacity()-result.size() < 100) {
			result.reserve(100);
		}
		curr_line.clear();
	}
	if (f.fail()) {
		std::cout << "f.fail() :(  Not sure why\n";
		//std::abort();
	}
	f.close();

	return result;
}


std::string search_dict(const std::string& dict, const param_set_t& p) {
	std::string result {};

	std::string curr_word {};  curr_word.reserve(100);
	for (int i=0; i<dict.size(); i+=curr_word.size()) {
		auto it = std::find(dict.begin()+i,dict.end(),'\n');

		curr_word.clear();
		for (int j=0; j<(it-(dict.begin()+i)); ++j) {
			curr_word += *(dict.begin()+i+j);
		}
		//std::copy(dict.begin()+i,it,std::back_inserter(curr_word));

		if (p.require_num_letters != 0 && curr_word.size() != p.require_num_letters) {
			continue;
		}

		if (p.permit_only.size() > 0) {
			auto it_forbidden = std::find_first_of(curr_word.begin(),curr_word.end(),
				p.permit_only.begin(),p.permit_only.end());
			if (it_forbidden != curr_word.end()) {
				continue;
			}
		}

		result += curr_word;
		result += '\n';
	}

	return result;
}







