#pragma once
#include <vector>
#include <array>

enum class atom_t : uint8_t {
	h,
	c,
	n,
	o,
	s
};

// Lookup table that returns the radius for the given atom_t
double radius(const atom_t&);

struct xyz_type_t {
	double x {0.0};
	double y {0.0};
	double z {0.0};
	atom_t atom {atom_t::h};
};

struct vec3_angle_t {
	std::array<double,3> v {0.0,0.0,0.0};
	double theta {0.0};
};

struct vec3_dist_t {
	std::array<double,3> v {0.0,0.0,0.0};
	double dist {0.0};
};

bool overlap(const std::vector<xyz_type_t>&, const std::vector<xyz_type_t>&);

double dsq(const xyz_type_t&, const xyz_type_t&);

bool center(std::vector<xyz_type_t>::iterator, std::vector<xyz_type_t>::iterator);
bool rotate(std::vector<xyz_type_t>::iterator, std::vector<xyz_type_t>::iterator, vec3_angle_t);
bool shift(std::vector<xyz_type_t>::iterator, std::vector<xyz_type_t>::iterator, vec3_dist_t);

double norm3d(std::array<double,3>::iterator, std::array<double,3>::iterator);

