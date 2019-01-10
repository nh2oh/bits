#include "wfind.h"
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

	// returns true if c is _not_ in the permitted set
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


// True if 'word' can be made from the letters in 'letters' using each letter in 'letters'
// no more than once.  The same letter in 'letters' may appear more than once.  
//
// Another way:  is_permutation(set_intersection()); 
//
bool is_hangman_set(const std::string& word, std::string letters) {
	std::string::iterator it_letters_beg = letters.begin();
	std::string::const_iterator it_word = word.cbegin();
	while (it_word!=word.end() && it_letters_beg!=letters.end()) {
		auto it = std::find(it_letters_beg,letters.end(),*it_word);
		if (it == letters.end()) { 
			return false;
		}
		std::iter_swap(it,it_letters_beg);
		++it_letters_beg;
		++it_word;
	}

	return it_word == word.end();
}





