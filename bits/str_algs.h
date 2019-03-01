#pragma once
#include "array_algs.h"
#include <string>


template<typename It, typename T>
void reverse_chunk_order(It beg, It end, T m) {
	bool in = (*beg == m);
	for (It curr=beg; curr!=end; ++curr) {
		if (in && !(*curr==m) || !in && (*curr == m)) {
			// state flip; curr is pointing at the first element of the next chunk
			end = dbkrot(beg,end,curr);
			in = !in; //(*beg == m);
			curr=beg;
		}
	}
}
int test_reverse_chunk_order();


//
// Find unmatched parens
//
std::string::const_iterator find_first_uparen(const std::string&);
int test_find_first_uparen();

//
// Reverse words in sentence
//
std::string reverse_words(const std::string&);
int test_reverse_words();

