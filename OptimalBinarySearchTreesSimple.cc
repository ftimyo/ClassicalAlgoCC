/*
 * Given a sorted array keys[0.. n-1] of search keys and an
 * array freq[0.. n-1] of frequency counts, where freq[i] is
 * the number of searches to keys[i]. Construct a binary
 * search tree of all keys such that the total cost of all
 * the searches is as small as possible.
 * Let us first define the cost of a BST. The cost of a BST
 * node is level of that node multiplied by its frequency.
 * Level of root is 1.
*/
/* w[i,j] = w[i,j-1] + freq[j]
 * e[i,j] = min{sum(k = i to j, (depth(k) + 1)*freq[k])}
 * e[i,j] = min{freq[k] + e[i,k-1] + w[i,k-1] + e[k+1,j] +
 * 				w[k+1,j]}	i<=k<=j
 * e[i,j] = min{e[i,k-1] + e[k+1,j] + w[i,j]}	i<=k<=j
 *
 * special case, e[i,i-1] = 0
 */
#include <type_traits>
#include <memory>
#include <cstring>
#include <queue>
#include <limits>
#define DEBUG
#ifdef DEBUG
#include <cstdio>
template <typename T, int N, int M>
void PrintOBST(int (&root)[N][N], T (&e)[M][M], T(&w)[M][M]) {
	for (auto& a : root) {
		for (auto x : a) {
			printf("%4d",x);
		}
		puts("");
	}
	puts("");
	for (auto& a : e) {
		for (auto x : a) {
			printf("%4d ",x);
		}
		puts("");
	}
	puts("");
	for (auto& a : w) {
		for (auto x : a) {
			printf("%4d ",x);
		}
		puts("");
	}
}
template <typename NP>
void TraverseBST(NP root) {
	std::queue<NP> q1,q2;
	q1.push(root);
	while (!q1.empty() || !q2.empty()) {
		while (!q1.empty()) {
			auto v = q1.front();q1.pop();
			if (v->l != nullptr) q2.push(v->l);
			if (v->r != nullptr) q2.push(v->r);
			printf("%5d",v->k);
		}
		puts("");
		while (!q2.empty()) {
			auto v = q2.front();q2.pop();
			if (v->l != nullptr) q1.push(v->l);
			if (v->r != nullptr) q1.push(v->r);
			printf("%5d",v->k);
		}
		puts("");
	}
}
#endif
template <typename KT>
struct Node {
	KT k;
	std::shared_ptr<Node> l, r;
	Node(int key):k(key){}
};
template <typename KT, int N>
auto BuildBST(int (&root)[N][N], int i, int j, KT (&key)[N]) {
	using NP = std::shared_ptr<Node<KT>>;
	if (i > j) return NP{nullptr};
	auto k = root[i][j];
	auto t = std::make_shared<Node<KT>>(key[k]);
	t->l = BuildBST(root,i,k-1,key);
	t->r = BuildBST(root,k+1,j,key);
	return t;
}
template <typename T, typename KT, int N>
auto OptimalBST(T (&freq)[N], KT (&key)[N]) {
	using TT = std::remove_reference_t<T>;
	using TKT = std::remove_reference_t<KT>;
	TT p[N+1], e[N+2][N+2], w[N+2][N+2];
	TKT mkey[N+1];
	int root[N+1][N+1];
	memcpy(p+1,freq,sizeof(freq));
	memcpy(mkey+1,key,sizeof(key));
	memset(e,0,sizeof(e));
	memset(w,0,sizeof(w));
	for (int j = 1; j <= N; ++j) {
		for (int i = j; i > 0; --i) {
			w[i][j] = w[i][j-1] + p[j];
			e[i][j] = std::numeric_limits<TT>::max();
			for (int k = i; k <= j; ++k) {
				auto q = e[i][k-1] + e[k+1][j] + w[i][j];
				if (q < e[i][j]) {
					root[i][j] = k;
					e[i][j] = q;
				}
			}
		}
	}
	auto bstroot = BuildBST(root,1,N,mkey);
#ifdef  DEBUG
	PrintOBST(root,e,w);
	TraverseBST(bstroot);
#endif
	return bstroot;
}

int main() {
	int keys[] = {10, 12, 20};
    int freq[] = {34, 8, 50};
	OptimalBST(freq,keys);
	return 0;
}
