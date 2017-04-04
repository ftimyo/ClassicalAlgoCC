/*
 * Problem:
 * Given a sequence K = ＜k₁,k₂,...,kₙ＞ of n distinct keys in sorted order (so
 * that k₁ < k₂ < ... < kₙ), and we wish to build a binary search tree from
 * these keys. For each key kᵢ, we have a probability pᵢ that a search will be
 * for kᵢ. We also have n + 1 "dummy keys" ＜d₀,d₁,d₂,...,dₙ＞ representing
 * values not in K. The dummy key dᵢ represent all values between kᵢ and kᵢ₊₁.
 * For each dummy key dᵢ, we have a probability qᵢ that a search will correspond
 * to dᵢ.
 *
 * Solution:
 *
 * w[i,j] = ∑p(i to j) + ∑q(i-1 to j)
 * e[i,j] represents the expected cost of the OBST for k[i] to k[j].
 *
 * w[i,j] = w[i,k-1] + pₖ + w[k+1,j]
 * e[i,j] = pₖ + (e[i,k-1] + w[i,k-1]) + (e[k+1,j] + w[k+1,j])
 *
 * e[i,j] = e[i,k-1] + e[k+1,j] + w[i,j]
 *
 * e[i,j] = qᵢ₋₁		if j = i - 1,
 * e[i,j] = min(i≤k≤j){e[i,k-1] + e[k+1,j] + w[i,j]} if i ≤ j.
 *
 * w[i,j] can also be recursively defined as
 * w[i,j] = w[i,j-1] + pⱼ+ qⱼ
 *
 * Pseudocode:
 *
 * OPTIMAL-BST(p,q,n)
 * 	let e[1..n+1,0..n],w[1..n+1,0..n],root[1..n,1..n] be new
 * 			tables
 * 	for i = 1 to n + 1
 * 		e[i,i-1] = qᵢ₋₁
 * 		w[i,i-1] = qᵢ₋₁
 * 	for l = 1 to n
 * 		for i = 1 to n - l + 1
 * 			j = i + l - 1
 * 			e[i,j] = ∞
 * 			w[i,j] = w[i,j-1] + pⱼ+ qⱼ
 * 			for r = i to j
 * 				t = e[i,r-1] + e[r+1,j] + w[i,j]
 * 				if t < e[i,j]
 * 					e[i,j] = t
 * 					root[i,j] = r
 * 	return e and root
 *
 * def BuildBST(root,i,j):
 * 	if i < j:
 * 		return None
 * 	r = root[i][j]
 * 	k = Key(r)
 * 	k.left = BuildBST(root,i,r-1)
 * 	k.right = BuildBST(root,r+1,j)
 * 	if not k.left:
 * 		k.left = DummyKey(r-1)
 * 	if not k.right:
 * 		k.right = DummyKey(r)
 *
 */
#include <cstdio>
#include <type_traits>
#include <limits>
#include <cstring>
#include <memory>
#include <queue>

#define DEBUG
template <typename T, int N, int M>
void PrintOBST(int (&root)[N][N], T (&e)[M][M], T(&w)[M][M]) {
	for (auto& a : root) {
		for (auto x : a) {
			printf("%2d",x);
		}
		puts("");
	}
	puts("");
	for (auto& a : e) {
		for (auto x : a) {
			printf("%.2f ",x);
		}
		puts("");
	}
	puts("");
	for (auto& a : w) {
		for (auto x : a) {
			printf("%.2f ",x);
		}
		puts("");
	}
}
struct Node {
	int k;
	std::shared_ptr<Node> l, r;
	Node(int key):k(key){}
};
using NP = std::shared_ptr<Node>;
template <int N>
auto BuildBST(int (&root)[N][N], int i, int j) {
	if (i > j) return NP{nullptr};
	auto k = root[i][j];
	auto t = std::make_shared<Node>(k);
	t->l = BuildBST(root,i,k-1);
	t->r = BuildBST(root,k+1,j);
	return t;
}
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
template <typename T, int N>
void OptimalBinarySearchTree(T (&p)[N], T(&q)[N]) {
	using TT = std::remove_reference_t<T>;
	TT w[N+1][N+1], e[N+1][N+1];
	int root[N][N];
	memset(w,0,sizeof(w));
	memset(e,0,sizeof(e));
	memset(root,0,sizeof(root));
	for (int i = 1; i <= N; ++i) {
		w[i][i-1] = q[i-1];
		e[i][i-1] = q[i-1];
	}
	for (int j = 1; j < N; ++j) {
		for (int i = j; i > 0; --i) {
			w[i][j] = w[i][j-1] + p[j] + q[j];
			e[i][j] = std::numeric_limits<TT>::max();
			for (int k = i; k <= j; ++k) {
				auto q = e[i][k-1] + e[k+1][j] + w[i][j];
				if (q < e[i][j]) {
					e[i][j] = q;
					root[i][j] = k;
				}
			}
		}
	}
#ifdef DEBUG
	PrintOBST(root,e,w);
	auto bstroot = BuildBST(root,1,N-1);
	fprintf(stderr, "BST tree built\n");
	TraverseBST(bstroot);
#endif
}

int main() {
	float p[] = {0.00,	0.15,	0.10,	0.05,	0.10,	0.20};
	float q[] = {0.05,	0.10,	0.05,	0.05,	0.05,	0.10};
	OptimalBinarySearchTree(p,q);
	return 0;
}
