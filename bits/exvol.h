#pragma once
#include <vector>
#include <array>
#include <exception>
#include <string>

using v3d_t = std::array<double,3>;

template<typename T, int N>
T dotprod(const std::array<T,N>& lhs, const std::array<T,N>& rhs) {
	T result {};
	for (int i=0; i<N; ++i) {
		result += lhs[i]*rhs[i];
	}
	return result;
}


//
// Very crude non-allocating 2d matrix
//
template<typename T, int Nr, int Nc>
class matrix {
public:
	matrix() = default;
	matrix(const std::array<T,Nr*Nc>& a) {
		//data[r*Nc+c] = val;
		for (int i=0; i<Nr*Nc; ++i) {
			data[(i/Nc)*Nc+i%Nc] = a[i];
		}
	};

	//
	// Getters
	//
	std::array<T,Nr> col(int c) const {
		if (c<0||c>=Nc) {
			std::abort();
		}
		std::array<T,Nr> result {};
		for (int r=0; r<Nr; ++r) {
			result[r] = data[r*Nc+c];
		}
		return result;
	};
	std::array<T,Nc> row(int r) const {
		if (r<0 || r>=Nr) {
			std::abort();
		}
		std::array<T,Nc> result {};
		for (int c=0; c<Nc; ++c) {
			result[c] = data[r*Nc+c];
		}
		return result;
	};
	T operator()(int r, int c) const {
		if (r>=Nr || c>=Nc || r<0 || c<0) {
			std::abort();
		}
		return data[r*Nc+c];
	};

	//
	// Setters
	//
	void set(int r, int c, T val) {
		if (r<0 || r>=Nr || c<0 || c>=Nc) {
			std::abort();
		}
		data[r*Nc+c] = val;
	};
	void setrow(int r, const std::array<T,Nc>& nr) {  // nr ~ "new row"
		if (r<0 || r>=Nr) {
			std::abort();
		}
		for (int c=0; c<Nc; ++c) {
			data[r*Nc+c] = nr[c];
		}
	};
	void setrow(int r, const std::vector<T>& nr) {  // nr ~ "new row"
		if (r<0 || r >= Nr || nr.size() != Nc) {
			std::abort();
		}
		for (int c=0; c<Nc; ++c) {
			data[r*Nc+c] = nr[c];
		}
	};
	void setcol(int c, const std::array<T,Nr>& nc) {  // nc ~ "new col"
		if (c<0 || c>Nc) {
			std::abort();
		}
		for (int r=0; r<Nr; ++r) {
			data[r*Nc+c] = nc[r];
		}
	};
	void setcol(int c, const std::vector<T>& nc) {  // nc ~ "new col"
		if (c<0 || c>Nc || nc.size() != Nr) {
			std::abort();
		}
		for (int r=0; r<Nr; ++r) {
			data[r*Nc+c] = nc[r];
		}
	};

	//
	// Arithmetic operations 
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
	// Ma += Mb
	matrix<T,Nr,Nc>& operator+=(const matrix<T,Nr,Nc>& lhs) {
		for (int r=0; r<Nr; ++r) {
			for (int c=0; c<Nc; ++c) {
				data[r*Nc + c] += lhs[r*Nc + c];
			}
		}
		return this;
	};
	// Ma -= Mb
	matrix<T,Nr,Nc>& operator-=(const matrix<T,Nr,Nc>& lhs) {
		for (int r=0; r<Nr; ++r) {
			for (int c=0; c<Nc; ++c) {
				data[r*Nc + c] -= lhs[r*Nc + c];
			}
		}
		return this;
	};
	//
	// Comparison operations 
	//
	// M==M
	bool operator==(const matrix<T,Nr,Nc>& rhs) const {
		for (int r=0; r<Nr; ++r) {
			for (int c=0; c<Nc; ++c) {
				if (data[r*Nc+c] != rhs.data[r*Nc+c]) {
					return false;
				}
			}
		}
		return true;
	};
	// M!=M
	bool operator!=(const matrix<T,Nr,Nc>& rhs) const {
		return !(*this==rhs);
	};


	std::array<T,Nr*Nc> data {};
};

// Ma * Mb
template<typename T, int Nr_lhs, int Nc_lhs, int Nr_rhs, int Nc_rhs>
matrix<T,Nr_lhs,Nc_rhs> operator*(const matrix<T,Nr_lhs,Nc_lhs>& lhs, const matrix<T,Nr_rhs,Nc_rhs>& rhs) {
	static_assert(Nc_lhs == Nr_rhs);
	matrix<T,Nr_lhs,Nc_rhs> result {};
	for (int c=0; c<Nc_rhs; ++c) {
		auto rhs_col = rhs.col(c);
		for (int r=0; r<Nr_lhs; ++r) {
			auto lhs_row = lhs.row(r);
			result.data[r*Nc_rhs + c] = dotprod(lhs_row,rhs_col);
		}
	}
	return result;
};


template<typename T, int Nr, int Nc>
std::string print(const matrix<T,Nr,Nc>& m) {
	std::string result {};
	for (int r=0; r<Nr; ++r) {
		for (int c=0; c<Nc; ++c) {
			result += (std::to_string(m(r,c)) + "\t");
		}
		result += "\n";
	}
	return result;
};



int test_matrix_mult();





enum class atom_t : uint8_t {
	h,
	c,
	n,
	o,
	s
};

// Lookup table that returns the radius for the given atom_t
double radius(const atom_t&);

// "xyz atom"
struct xyza_t {
	double x {0.0};
	double y {0.0};
	double z {0.0};
	atom_t atom {atom_t::h};
};

// An angle and corresponding vector about which to rotate some object
struct vec3_angle_t {
	v3d_t v {0.0,0.0,0.0};
	double theta {0.0};
};

struct vec3_dist_t {
	v3d_t v {0.0,0.0,0.0};
	double dist {0.0};
};

bool overlap(const std::vector<xyza_t>&, const std::vector<xyza_t>&);
bool overlap(std::vector<xyza_t>::iterator, std::vector<xyza_t>::iterator,
	std::vector<xyza_t>::iterator, std::vector<xyza_t>::iterator);
double dsq(const xyza_t&, const xyza_t&);
std::array<double,3> max_dimensions(std::vector<xyza_t>::iterator, std::vector<xyza_t>::iterator);

bool center(std::vector<xyza_t>::iterator, std::vector<xyza_t>::iterator);
bool rotate(std::vector<xyza_t>::iterator, std::vector<xyza_t>::iterator, vec3_angle_t);

matrix<double,3,3> make_3d_rotm(v3d_t, double);
bool shift3d(std::vector<xyza_t>::iterator, std::vector<xyza_t>::iterator, v3d_t);
double norm3d(std::array<double,3>::iterator, std::array<double,3>::iterator);

struct exvol_result_t {
	int n_test {0};
	int n_collide {0};
	double v_box {0.0};
	double v_ex {0.0};
};
exvol_result_t exvol(std::vector<xyza_t>::iterator, std::vector<xyza_t>::iterator,
	std::vector<xyza_t>::iterator, std::vector<xyza_t>::iterator,
	int);




