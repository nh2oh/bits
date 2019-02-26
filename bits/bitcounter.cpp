#include "bitcounter.h"
#include <vector>
#include <iostream>
#include <exception>
#include <string>

int tests_ones() {
	struct ui8_tests_t {
		uint8_t v {0};
		int n_ones {0};
	};
	std::vector<ui8_tests_t> ui8 {
		{0,0},{1,1},{2,1},{3,2},{4,1},{8,1},{15,4},{16,1},{32,1},
		{64,1},{127,7},{128,1},{255,8}
	}; 

	for (int i=0; i<ui8.size(); ++i) {
		if (ones(ui8[i].v) != ui8[i].n_ones) {
			std::cout << bitprinter(ui8[i].v) << "\n";
			std::cout << "ones(ui8[i].v) != ui8[i].n_ones for ui8[i].v==" << ui8[i].v
				<< ", ui8[i].n_ones==" << ui8[i].n_ones << ".  ones(ui8[i].v)=="
				<< ones(ui8[i].v) << ".  Aborting...\n";
			std::abort();
		}
	}


	// Note that the "value" field for these tests is int.  I static_cast<int8_t> 
	// on each usage, since i can't use the { } initialization syntax if the field
	// is an 8bit int.  
	struct i8_tests_t {
		int v {0};  
		int n_ones {0};
	};
	std::vector<i8_tests_t> i8 {
		{0,0},{1,1},{2,1},{3,2},{4,1},{8,1},{15,4},{16,1},{32,1},
		{64,1},{127,7},
		{-0,0},{-1,8},{-2,7},{-3,7},{-4,6},{-8,5},{-15,5},{-16,4},{-32,3},
		{-64,2},{-127,2},{-128,1}
	};
	for (int i=0; i<i8.size(); ++i) {
		if (ones(static_cast<int8_t>(i8[i].v)) != i8[i].n_ones) {
			std::cout << bitprinter(static_cast<int8_t>(i8[i].v)) << "\n";
			std::cout << "ones(i8[i].v) != i8[i].n_ones for i8[i].v==" << i8[i].v
				<< ", i8[i].n_ones==" << i8[i].n_ones << ".  ones(i8[i].v)=="
				<< ones(static_cast<int8_t>(i8[i].v)) << ".  Aborting...\n";
			std::abort();
		}
	}

	return 0;
}


int tests_bitprinter() {

	struct f_tests_t {
		float v {0};
		std::string ans {"00000000|"};
	};
	std::vector<f_tests_t> f {
		{0,"00000000|"},{1,"00000001|"},{2,"00000010|"},{3,"00000011|"},{4,"00000100|"},
		{15,"00000011|"},{16,"00000100|"},{255,"00000100|"},{256,"00000100|"}
	}; 

	for (int i=0; i<f.size(); ++i) {
		std::cout << "f[i].v == " << std::to_string(f[i].v) << " => bitprinter(f[i].v) == " 
			<< bitprinter(f[i].v) << std::endl;
	}


	struct ui8_tests_t {
		uint8_t v {0};
		std::string ans {"00000000|"};
	};
	std::vector<ui8_tests_t> ui8 {
		{0,"00000000|"},{1,"00000001|"},{2,"00000010|"},{3,"00000011|"},{4,"00000100|"},
		{8,"00001000|"},{15,"00001111|"},{16,"00010000|"},{32,"00100000|"},
		{64,"01000000|"},{127,"01111111|"},{128,"10000000|"},{255,"11111111|"}
	}; 

	for (int i=0; i<ui8.size(); ++i) {
		if (bitprinter(ui8[i].v) != ui8[i].ans) {
			std::cout << "bitprinter(ui8[i].v) != ui8[i].ans for ui8[i].v==" << ui8[i].v
				<< ", ui8[i].ans==" << ui8[i].ans << ".  bitprinter(ui8[i].v)=="
				<< bitprinter(ui8[i].v) << ".  Aborting...\n";
			std::abort();
		}
	}

	
	// Note that the "value" field for these tests is int.  I static_cast<int8_t> 
	// on each usage, since i can't use the { } initialization syntax if the field
	// is an 8bit int.  
	struct i8_tests_t {
		int v {0};  
		std::string ans {"00000000|"};
	};
	std::vector<i8_tests_t> i8 {
		{0,"00000000|"},{1,"00000001|"},{2,"00000010|"},{3,"00000011|"},{4,"00000100|"},
		{8,"00001000|"},{15,"00001111|"},{16,"00010000|"},{32,"00100000|"},
		{64,"01000000|"},{127,"01111111|"},
		{-0,"00000000|"},{-1,"11111111|"},{-2,"11111110|"},{-3,"11111101|"},{-4,"11111100|"},
		{-8,"11111000|"},{-15,"11110001|"},{-16,"11110000|"},{-32,"11100000|"},
		{-64,"11000000|"},{-127,"10000001|"},{-128,"10000000|"}
	};
	for (int i=0; i<i8.size(); ++i) {
		if (bitprinter(static_cast<int8_t>(i8[i].v)) != i8[i].ans) {
			std::cout << bitprinter(static_cast<int8_t>(i8[i].v)) << "\n";
			std::cout << "bitprinter(i8[i].v) != i8[i].ans for i8[i].v==" << i8[i].v
				<< ", i8[i].ans==" << i8[i].ans << ".  bitprinter(i8[i].v)=="
				<< ones(static_cast<int8_t>(i8[i].v)) << ".  Aborting...\n";
			std::abort();
		}
	}
	
	return 0;
}


int tests_rbyteorder() {
	struct ui32_tests_t {
		uint32_t v {0};
		uint32_t ans {0};
	};
	std::vector<ui32_tests_t> ui32 {
		{0,0},{0x0000000F,0x0F000000},{0xABCDEF00,0x00EFCDAB}
	};

	for (int i=0; i<ui32.size(); ++i) {
		std::array<unsigned char,4> result = rbyteorder(ui32[i].v);
		uint64_t curr {0};
		for (int j=(result.size()-1); j>=0; --j) {
			curr = (curr<<8);
			curr += result[j];
		}
		if (curr != ui32[i].ans) {
			std::cout << "curr != ui32[i].ans for ui32[i].v==" << ui32[i].v
				<< ", ui32[i].ans==" << ui32[i].ans << ".  Aborting...\n";
			std::abort();
		}
	}

	
	struct i32_tests_t {
		int32_t v {0};
		uint32_t ans {0};
	};
	std::vector<i32_tests_t> i32 {
		{0,0},{0x00000002,0x02000000},{1,0x01000000},{-1,0xFFFFFFFF},{-2567,0xF9F5FFFF}
	};

	for (int i=0; i<i32.size(); ++i) {
		std::array<unsigned char,4> result = rbyteorder(i32[i].v);
		uint32_t curr {0};
		for (int j=(result.size()-1); j>=0; --j) {
			curr = (curr<<8);
			curr += result[j];
		}
		if (curr != i32[i].ans) {
			std::cout << "curr != i32[i].ans for i32[i].v==" << i32[i].v
				<< ", i32[i].ans==" << i32[i].ans << ".  Aborting...\n";
			std::abort();
		}
	}

	return 0;
}


