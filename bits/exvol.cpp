#include "exvol.h"
#include <cmath>  // std::pow()
#include <algorithm>  // std::max()
#include <array>
#include <random>


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



exvol_result_t exvol(std::vector<xyza_t>::iterator a_beg, std::vector<xyza_t>::iterator a_end,
				std::vector<xyza_t>::iterator b_beg, std::vector<xyza_t>::iterator b_end,
				int n) {

	auto v3d_subtract = [](const v3d_t& a, const v3d_t& b) -> v3d_t {
		return v3d_t {a[0]-b[0],a[1]-b[1],a[2]-b[2]};
	};
	auto v3d_add = [](const v3d_t& a, const v3d_t& b) -> v3d_t {
		return v3d_t {a[0]+b[0],a[1]+b[1],a[2]+b[2]};
	};

	center(a_beg,a_end);
	center(b_beg,b_end);

	auto max_dims_a = max_dimensions(a_beg,a_end);
	double length_a = std::max({max_dims_a[0],max_dims_a[1],max_dims_a[2]});
	auto max_dims_b = max_dimensions(b_beg,b_end);
	double length_b = std::max({max_dims_b[0],max_dims_b[1],max_dims_b[2]});
	double r_sphere = 0.5*(length_a + length_b);  // TODO:  The matlab versions adds a small fudge fctr

	std::random_device rdev {};
	std::default_random_engine re {rdev()};
	std::uniform_real_distribution rd_angle {};
	std::uniform_real_distribution rd_center {-1*r_sphere,r_sphere};
	
	int n_collide {0};
	v3d_t rand_shift_vec {};
	for (int i=0; i<n; ++i) {

		if (i%1000 == 0) {
			v3d_t rand_rotation_vec {rd_center(re),rd_center(re),rd_center(re)};
			//matrix<double,3,3> rand_rotation_mtrx = make_3d_rotm(rand_rotation_vec, rd(re));
			rotate(a_beg, a_end, vec3_angle_t {rand_rotation_vec,rd_angle(re)});
		}

		rand_shift_vec = v3d_subtract({rd_center(re),rd_center(re),rd_center(re)},rand_shift_vec);
		shift3d(a_beg,a_end,rand_shift_vec);

		if (overlap(a_beg,a_end,b_beg,b_end)) {
			++n_collide;
		}

		/*
		bool collide {false};
		for (auto it_a=a_beg; it_a!=a_end; ++it_a) {
			for (auto it_b=b_beg; it_b!=b_end; ++it_b) {
				if (overlap(*it_a,*it_b)) {
					collide = true;
					break;
				}
			}
			if (collide) {
				++n_collide;
				collide = false;
				break;  // To next shift-rotate
			}
		}  // To next atom in a
		*/


	}  // To next shift-rotate

	double v_box = (4.0/3.0)*3.14159*std::pow(r_sphere,3);
	double v_ex = (static_cast<double>(n)/static_cast<double>(n_collide))*v_box;
	exvol_result_t result {n,n_collide,v_box,v_ex};

	return result;
}


// TODO:
// - Lookup table for std::pow(radius(a[i].atom)+radius(b[j].atom),2) for all radius pairs
// - Presort?
// - Only compute dsq(a[i],b[j]) if there might plausibly be a clash
// - Partition the sphere in half; only test pairs on the same half 
bool overlap(const std::vector<xyza_t>& a, const std::vector<xyza_t>& b) {
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
bool overlap(std::vector<xyza_t>::iterator a_beg, std::vector<xyza_t>::iterator a_end,
				std::vector<xyza_t>::iterator b_beg, std::vector<xyza_t>::iterator b_end) {
	
	for (std::vector<xyza_t>::iterator a_curr=a_beg; a_curr!=a_end; ++a_curr) {
		for (std::vector<xyza_t>::iterator b_curr=b_beg; b_curr!=b_end; ++b_curr) {
			double min_dist_sq = std::pow(radius((*a_curr).atom)+radius((*b_curr).atom),2);
			if (dsq(*a_curr,*b_curr) > min_dist_sq) {
				return true;
			}
		}
	}

	return false;
}

// "Maximum extent" in x is the atom for which the quantity x + 0.5*r is larger than that for
// all others.  Ie, the radius is included in the dfn of "maximum extent."  
std::array<double,3> max_dimensions(std::vector<xyza_t>::iterator beg, std::vector<xyza_t>::iterator end) {
	double max_x {0.0};
	double max_y {0.0};
	double max_z {0.0};
	double min_x {0.0};
	double min_y {0.0};
	double min_z {0.0};

	for (auto it_curr=beg; it_curr!=end; ++it_curr) {
		max_x = std::max(max_x, (*it_curr).x+0.5*radius((*it_curr).atom));
		min_x = std::min(min_x, (*it_curr).x-0.5*radius((*it_curr).atom));

		max_y = std::max(max_y, (*it_curr).y+0.5*radius((*it_curr).atom));
		min_y = std::min(min_y, (*it_curr).y-0.5*radius((*it_curr).atom));

		max_z = std::max(max_z, (*it_curr).z+0.5*radius((*it_curr).atom));
		min_z = std::min(min_z, (*it_curr).z-0.5*radius((*it_curr).atom));
	}

	return v3d_t {std::abs(max_x-min_x),std::abs(max_y-min_y),std::abs(max_z-min_z)};
}



// Shift the input vector along (x,y,z) s.t. its maximum extent in direction d == its maximum
// extend in direction -d for d ~ {x,y,z}.  
// "Maximum extent" in x is the atom for which the quantity x + 0.5*r is larger than that for
// all others.  Ie, the radius is included in the dfn of "maximum extent."  
// A std::vector<xyza_t> represents a "molecule."  
bool center(std::vector<xyza_t>::iterator beg, std::vector<xyza_t>::iterator end) {
	double max_x {0.0};
	double max_y {0.0};
	double max_z {0.0};
	double min_x {0.0};
	double min_y {0.0};
	double min_z {0.0};

	// Iterate through all atoms in [beg,end) and store the max and min x,y,z extents in max_x, ... min_z
	// Note that different atoms may contribute to each of the 9 {min,max}_{x,y,z} variables.  
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


// A std::vector<xyza_t> represents a "molecule."  
bool rotate(std::vector<xyza_t>::iterator beg, std::vector<xyza_t>::iterator end, vec3_angle_t rv) {
	norm3d(rv.v.begin(),rv.v.end());
	double rv_x = rv.v[0];
	double rv_y = rv.v[1];
	double rv_z = rv.v[2];
	double c = std::cos(rv.theta);
	double s = std::sin(rv.theta);
	double t = 1.0 - std::cos(rv.theta);

	v3d_t Rx {t*std::pow(rv_x,2)+c, t*rv_x*rv_y-s*rv_z, t*rv_x*rv_z+s*rv_y};
	v3d_t Ry {t*rv_x*rv_y+s*rv_z, t*std::pow(rv_y,2)+c, t*rv_y*rv_z-s*rv_x};
	v3d_t Rz {t*rv_x*rv_z-s*rv_y, t*rv_y*rv_z+s*rv_x, t*std::pow(rv_z,2)+c};

	// matrix-1d-times-vector-1d
	auto m1dv1d = [](const v3d_t& lhs, const xyza_t& v) -> double {
		return lhs[0]*v.x + lhs[1]*v.y + lhs[2]*v.z;
	};

	for (auto it_curr=beg; it_curr!=end; ++it_curr) {
		auto curr = *it_curr;
		xyza_t curr_rotated {curr};
		curr_rotated.x = m1dv1d(Rx,curr);
		curr_rotated.y = m1dv1d(Ry,curr);
		curr_rotated.z = m1dv1d(Rz,curr);
		*it_curr = curr_rotated;
	}

	auto rm = make_3d_rotm(rv.v,rv.theta);
	for (auto it_curr=beg; it_curr!=end; ++it_curr) {
		v3d_t curr_v {(*it_curr).x,(*it_curr).y,(*it_curr).z};
		curr_v = rm*curr_v;
		xyza_t curr_result {curr_v[0],curr_v[1],curr_v[2],(*it_curr).atom};
		*it_curr = curr_result;
	}

	return true;
}


matrix<double,3,3> make_3d_rotm(v3d_t v, double theta) {
	matrix<double,3,3> result {};
	norm3d(v.begin(),v.end());
	double c = std::cos(theta);
	double s = std::sin(theta);
	double t = 1.0 - std::cos(theta);
	//std::array<double,3> Rx {t*std::pow(v[0],2)+c, t*v[0]*v[1]-s*v[2], t*v[0]*v[2]+s*v[1]};
	//std::array<double,3> Ry {t*v[0]*v[1]+s*v[2], t*std::pow(v[1],2)+c, t*v[1]*v[2]-s*v[0]};
	//std::array<double,3> Rz {t*v[0]*v[2]-s*v[1], t*v[1]*v[2]+s*v[0], t*std::pow(v[2],2)+c};
	result.setrow(0, v3d_t {t*std::pow(v[0],2)+c, t*v[0]*v[1]-s*v[2], t*v[0]*v[2]+s*v[1]});
	result.setrow(1, v3d_t {t*v[0]*v[1]+s*v[2], t*std::pow(v[1],2)+c, t*v[1]*v[2]-s*v[0]});
	result.setrow(2, v3d_t {t*v[0]*v[2]-s*v[1], t*v[1]*v[2]+s*v[0], t*std::pow(v[2],2)+c});

	return result;
}


//// Shift _to_
//bool shift3d(std::vector<xyza_t>::iterator beg, std::vector<xyza_t>::iterator end, vec3_dist_t sv) {
//	norm3d(sv.v.begin(),sv.v.end());
//	double sv_x = (sv.dist)*sv.v[0];
//	double sv_y = (sv.dist)*sv.v[1];
//	double sv_z = (sv.dist)*sv.v[2];
	

// Shift _by_
bool shift3d(std::vector<xyza_t>::iterator beg, std::vector<xyza_t>::iterator end, v3d_t sv) {

	for (auto it_curr=beg; it_curr!=end; ++it_curr) {
		auto curr_shifted {*it_curr};
		curr_shifted.x += sv[0];
		curr_shifted.y += sv[1];
		curr_shifted.z += sv[2];
		*it_curr = curr_shifted;
	}

	return true;
}


// Square of the distance between a, b
double dsq(const xyza_t& a, const xyza_t& b) {
	return std::pow((a.x-b.x),2) + std::pow((a.x-b.x),2) + std::pow((a.x-b.x),2);
}


// Normalize input vector s.t. its length is == 1; returns the initial length
double norm3d(std::array<double,3>::iterator beg, std::array<double,3>::iterator end) {
	double len_sq {0.0};
	for (auto curr=beg; curr!=end; ++curr) {
		len_sq += (*curr)*(*curr);
	}
	auto N = static_cast<double>(end-beg);
	double exp = 1.0/N;
	double len = std::pow(len_sq,exp);

	// Normalize
	for (auto curr=beg; curr!=end; ++curr) {
		*curr = (*curr)*(1.0/len);
	}

	return len;
}




