/*
 * Codes in which no codeword is also a prefix of some other
 * codeword are called prefix codes.
 * We assume that C is a set of n characters and that each
 * character c ∈ C is an object with an attribute c.freq giving
 * its frequency. The algorithm builds the tree T corresponding to
 * the optimal code in a bottom-up manner. It begins with a set of
 * |C| leaves and performs a sequence of |C| - 1 “merging”
 * operations to create the final tree. The algorithm uses a
 * min-priority queue Q, keyed on the freq attribute, to identify
 * the two least-frequent objects to merge together. When we merge
 * two objects, the result is a new object whose frequency is the
 * sum of the frequencies of the two objects that were merged.
 *
 * HUFFMAN(C)
 * 	n = |C|
 * 	Q = C
 * 	for i = 1 to n - 1
 * 		allocate a new node z
 * 		z.left = x = EXTRACT-MIN(Q)
 * 		z.right = y = EXTRACT-MIN(Q)
 * 		z.freq = x.freq + y.freq
 * 		INSERT(Q,z)
 * 	return EXTRACT-MIN(Q) //	return the root of the tree
 */
#include <type_traits>
#include <utility>
#include <vector>
#include <string>
/* Heed, the reason not to use priority queue is that
 * top() returns a const ref. Therefore if we use unique_ptr
 * we are not able to get it from priority queue, since const ref
 * cannot be moved.
 * Hence heap helper functions provided by <algorithm> are used.
 * if shared_ptr or raw ptr is used, it can definitely
 * companioned with std::priority_queue.
 */
#include <algorithm>
#define DEBUG

struct HTN { /*huffman Tree Node*/
	using P = std::unique_ptr<HTN>;
	int idx;
	P left;
	P right;
	HTN(int i, P& l, P& r):idx{i},left{std::move(l)},right{std::move(r)}{}
	HTN(int i) : idx{i}{}
};
template <typename T, int N>
auto Huffman(T (&F)[N]) {
	std::remove_reference_t<T> f[N];
	std::memcpy(f,F,sizeof(f));
	auto cmp = [&f](auto& c1, auto& c2){return f[c1->idx] > f[c2->idx];};
	std::vector<HTN::P> hp;
	for (int i = 0; i < N; ++i) hp.push_back(std::make_unique<HTN>(i));
	for (int i = 0; i < N - 1; ++i) {
		std::pop_heap(std::begin(hp),std::end(hp),cmp);
		auto x = std::move(hp.back()); hp.pop_back();
		std::pop_heap(std::begin(hp),std::end(hp),cmp);
		auto y = std::move(hp.back()); hp.pop_back();
		f[x->idx] += f[y->idx];
		hp.push_back(std::make_unique<HTN>(x->idx,x,y));
		std::push_heap(std::begin(hp),std::end(hp),cmp);
	}
	return std::move(hp.front());
}

void DFS(std::vector<std::string>& ct, HTN::P& root, std::string& s) {
/* It is fine to check either left or right */
	if (root->left == nullptr) {
		ct[root->idx] = s;
	} else {
		s.push_back('0');
		DFS(ct,root->left,s);
		s.pop_back();
		s.push_back('1');
		DFS(ct,root->right,s);
		s.pop_back();
	}
}

template <typename CT /*Char Type*/, typename T, int N>
void Huffman(CT (&C)[N], T (&F)[N]) {
	std::vector<std::string> ct(N,""); /*code table*/
	std::string s;
	auto root = std::move(Huffman(F));
	DFS(ct,root,s);
#ifdef DEBUG
	for (int i = 0; i < N; ++i) {
		fprintf(stderr, "%c -- %s\n",C[i],ct[i].c_str());
	}
#endif
}

//test
int main () {
	char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
	int freq[] = {5, 9, 12, 13, 16, 45};
	Huffman(arr,freq);
	return 0;
}
