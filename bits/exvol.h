#pragma once
#include <vector>
#include <array>
#include <exception>

//
// Very crude non-allocating matrix
//
template<typename T, int Nr, int Nc>
class matrix {
public:
	matrix() = default;

	//
	// Getters
	//
	std::array<T,Nr> col(int c) const {
		if (c<0||c>=Nc) {
			std::abort();
		}
		std::array<T,Nr> result {};
		for (int r=0; r<Nr; ++r) {
			result[r] = data[r*Nc + c];
		}
		return result;
	};
	std::array<T,Nc> row(int r) const {
		if (r<0 || r>=Nr) {
			std::abort();
		}
		std::array<T,Nc> result {};
		for (int c=0; c<Nc; ++c) {
			result[c] = data[r*Nc + c];
		}
		return result;
	};
	T operator()(int r, int c) const {
		if (r>=Nr || c>=Nc || r<0 || c<0) {
			std::abort();
		}
		return data[r*Nc + c];
	};

	//
	// Setters
	//
	void setrow(int r, const std::array<T,Nc>& nr) {  // nr ~ "new row"
		if (r<0 || r>=Nr) {
			std::abort();
		}
		for (int c=0; c<Nc; ++c) {
			data[c] = nr[c];
		}
	};
	void setrow(int r, const std::vector<T>& nr) {  // nr ~ "new row"
		if (r<0 || r >= Nr || nr.size() != Nc) {
			std::abort();
		}
		for (int c=0; c<Nc; ++c) {
			data[c] = nr[c];
		}
	};
	void setcol(int c, const std::array<T,Nr>& nc) {  // nc ~ "new col"
		if (c<0 || c>Nc) {
			std::abort();
		}
		for (int r=0; r<Nr; ++r) {
			data[r*Nc + c] = nc[r];
		}
	};
	void setcol(int c, const std::vector<T>& nc) {  // nc ~ "new col"
		if (c<0 || c>Nc || nc.size() != Nr) {
			std::abort();
		}
		for (int r=0; r<Nr; ++r) {
			data[r*Nc + c] = nc[r];
		}
	};

	//
	// Operations 
	//
	// M*v
	std::array<T,Nr> operator*(const std::array<T,Nc>& rhs) const {
		std::array<T,Nr> result {};
		for (int r=0; r<Nr; ++r) {
			for (int c=0; c<Nc; ++c) {
				result[c] += rhs[c]*data[r*Nc + c];
			}
		}
		return result;
	};
	// M*v
	std::array<T,Nr> operator*(const std::vector<T>& rhs) const {
		if (rhs.size() != Nc) {
			std::abort();
		}
		std::array<T,Nr> result {0.0};
		for (int r=0; r<Nr; ++r) {
			for (int c=0; c<Nc; ++c) {
				result[c] += rhs[c]*data[r*Nc + c];
			}
		}
		return result;
	};

	std::array<T,Nr*Nc> data {};
};


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

