#include <string>
#include <algorithm>
#include <vector>

std::string printv(const std::vector<int>& v, int idx_star=-1);
int colid2int(const std::string&);
int test_colid2int();


template<typename It> 
It shift_to_end(It v, It end) {
	It ne = v;
	while (++ne!=end) {
		std::iter_swap(v,ne);
		++v;
	}
	return v;
}
int test_shift_to_end();

template<typename It>
It dbkrot(It beg, It end, It pvt) {
	while (pvt!=beg) {
		--pvt;
		end = shift_to_end(pvt,end);
	}
	return end;
}
int test_dbkrot();



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



