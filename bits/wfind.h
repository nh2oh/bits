#pragma once
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>


std::string load_dict(const std::filesystem::path&);

struct param_set_t {
	int require_num_letters {0};
	std::string permit_only {};
};

std::string search_dict(const std::string&, const param_set_t&);
