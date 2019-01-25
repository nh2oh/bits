#include "exvol.h"
#include <cmath>  // std::pow()
#include <algorithm>  // std::max()
#include <array>

double radius(const atom_t& a) {
	switch (a) {
		case atom_t::c:  return 1.7;
		case atom_t::n:  return 1.55;
		case atom_t::o:  return 1.52;
		case atom_t::h:  return 1.09;
		case atom_t::s:  return 1.8;
		default:  return 0.0;
	}

	return 0.0;
}

// TODO:
// - Lookup table for std::pow(radius(a[i].atom)+radius(b[j].atom),2) for all radius pairs
// - Presort?
// - Only compute dsq(a[i],b[j]) if there might plausibly be a clash
bool overlap(const std::vector<xyz_type_t>& a, const std::vector<xyz_type_t>& b) {
	for (int i=0; i<a.size(); ++i) {
		for (int j=0; j<b.size(); ++j) {
			double min_dist_sq = std::pow(radius(a[i].atom)+radius(b[j].atom),2);
			if (dsq(a[i],b[j]) > min_dist_sq) {
				return true;
			}
		}
	}

	return false;
}


// Shift the input vector along (x,y,z) s.t. its maximum extent in direction d == its maximum
// extend in direction -d for d ~ {x,y,z}.  
// "Maximum extent" in x is the atom for which the quantity x + 0.5*r is larger than that for
// all others.  Ie, the radius is included in the dfn of "maximum extent."  
bool center(std::vector<xyz_type_t>::iterator beg, std::vector<xyz_type_t>::iterator end) {
	double max_x {0.0};
	double max_y {0.0};
	double max_z {0.0};
	double min_x {0.0};
	double min_y {0.0};
	double min_z {0.0};

	for (auto curr=beg; curr!=end; ++curr) {
		auto curr_xyzr = *curr;
		auto curr_r_contrib = 0.5*radius(curr_xyzr.atom);

		if ((curr_xyzr.x+curr_r_contrib) > max_x) {
			max_x = curr_xyzr.x+curr_r_contrib;
		}
		if ((curr_xyzr.y+curr_r_contrib) > max_y) {
			max_y = curr_xyzr.y+curr_r_contrib;
		}
		if ((curr_xyzr.z+curr_r_contrib) > max_z) {
			max_z = curr_xyzr.z+curr_r_contrib;
		}

		if ((curr_xyzr.x-curr_r_contrib) < min_x) {
			min_x = curr_xyzr.x-curr_r_contrib;
		}
		if ((curr_xyzr.y-curr_r_contrib) < min_y) {
			min_y = curr_xyzr.y-curr_r_contrib;
		}
		if ((curr_xyzr.z-curr_r_contrib) < min_z) {
			min_z = curr_xyzr.z-curr_r_contrib;
		}
	}

	double delta_x = max_x-min_x;
	double delta_y = max_y-min_y;
	double delta_z = max_z-min_z;
	for (auto curr=beg; curr!=end; ++curr) {
		(*curr).x += delta_x;
		(*curr).y += delta_y;
		(*curr).z += delta_z;
	}

	return true;
}


bool rotate(std::vector<xyz_type_t>::iterator beg, std::vector<xyz_type_t>::iterator end, vec3_angle_t rv) {
	norm3d(rv.v.begin(),rv.v.end());
	double rv_x = rv.v[0];
	double rv_y = rv.v[1];
	double rv_z = rv.v[2];
	double c = std::cos(rv.theta);
	double s = std::sin(rv.theta);
	double t = 1.0 - std::cos(rv.theta);

	std::array<double,3> Rx {t*std::pow(rv_x,2)+c, t*rv_x*rv_y-s*rv_z, t*rv_x*rv_z+s*rv_y};
	std::array<double,3> Ry {t*rv_x*rv_y+s*rv_z, t*std::pow(rv_y,2)+c, t*rv_y*rv_z-s*rv_x};
	std::array<double,3> Rz {t*rv_x*rv_z-s*rv_y, t*rv_y*rv_z+s*rv_x, t*std::pow(rv_z,2)+c};

	// matrix-1d-times-vector-1d
	auto m1dv1d = [](const std::array<double,3>& lhs, const xyz_type_t& v) -> double {
		return lhs[0]*v.x + lhs[1]*v.y + lhs[2]*v.z;
	};

	for (auto it_curr=beg; it_curr!=end; ++it_curr) {
		auto curr = *it_curr;
		xyz_type_t curr_rotated {curr};
		curr_rotated.x = m1dv1d(Rx,curr);
		curr_rotated.y = m1dv1d(Ry,curr);
		curr_rotated.z = m1dv1d(Rz,curr);
		*it_curr = curr_rotated;
	}

	return true;
}


bool shift(std::vector<xyz_type_t>::iterator beg, std::vector<xyz_type_t>::iterator end, vec3_dist_t sv) {
	norm3d(sv.v.begin(),sv.v.end());
	double sv_x = (sv.dist)*sv.v[0];
	double sv_y = (sv.dist)*sv.v[1];
	double sv_z = (sv.dist)*sv.v[2];

	for (auto it_curr=beg; it_curr!=end; ++it_curr) {
		auto curr_shifted {*it_curr};
		curr_shifted.x += sv_x;
		curr_shifted.y += sv_y;
		curr_shifted.z += sv_z;
		*it_curr = curr_shifted;
	}

	return true;
}


// Square of the distance between a, b
double dsq(const xyz_type_t& a, const xyz_type_t& b) {
	return std::pow((a.x-b.x),2) + std::pow((a.x-b.x),2) + std::pow((a.x-b.x),2);
}


// Normalize input vector s.t. its length is == 1; returns the initial length
double norm3d(std::array<double,3>::iterator beg, std::array<double,3>::iterator end) {
	double len_sq {0.0};
	for (auto curr=beg; curr!=end; ++curr) {
		len_sq += (*curr)*(*curr);
	}
	auto N = end-beg;
	double exp = 1.0/N;
	double len = std::pow(len_sq,exp);

	// Normalize
	for (auto curr=beg; curr!=end; ++curr) {
		*curr = (*curr)*(1.0/len);
	}

	return len;
}




