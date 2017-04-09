/*
 * Given N items {1,2,3,...N}, using W[i] and P[i] to
 * represent the weight and value of given item i.
 * Find out the maximum profit subset of item such that sum
 * of the weights of this subset is smaller than or equal to
 * Knapsack capacity C.
 *
 * We'll use backtracking, branch and bound best first search
 * to approach this problem.
 */
#include <iterator>
#include <numeric>
#include <vector>
#include <algorithm>
#define DEBUG

#include <boost/type_index.hpp>
#include <iostream>
template <typename WT, typename PT, typename IT>
void GetSortedIndexAndValue(const WT& wt, const PT& pt, /*input*/
		IT& si, WT& swt, PT& spt) { /*output*/
	auto N = std::size(wt);
	std::vector<double> pd(N);
	si.resize(N);
	std::iota(std::begin(si),std::end(si),0);
	for (int i = 0; i < N; ++i)
		pd[i] = static_cast<double>(pt[i])/wt[i];
	std::sort(std::begin(si),std::end(si),
			[&pd](auto i1,auto i2){
				return pd[i1] > pd[i2];
			});
	std::transform(std::begin(si),std::end(si),
			std::back_inserter(swt),[&wt](auto i){
				return wt[i];
			});
	std::transform(std::begin(si),std::end(si),
			std::back_inserter(spt),[&pt](auto i){
				return pt[i];
			});
}

template <typename WT, typename PT, typename IP,
	typename W, typename P>
auto Promising(IP i, WT& wt, PT& pt, W w, P p, W c,
		long double mp) {
	auto N = std::size(wt);
	if (w >= c) return false;
/* calculate bound */
	for (;i < N && w + wt[i] < c;++i) {
		w += wt[i];
		p += pt[i];
	}
	if (w < c && i < N) {
		p += (c-w)*(static_cast<long double>(pt[i])/wt[i]);
	}
/* compare bound with max profit */
	if (p > mp) return true;
	return false;
}

template <typename IP, typename S, typename WT, typename PT,
	typename W, typename P>
void Backtrack(IP i, S& sol, S& best, WT& wt, PT& pt,
		W w, P p, W c/*capacity*/,
		long double& mp/*max profit*/) {
	if (w <= c && p > mp) {
		mp = p;
		best = sol;
	}
	if (Promising(i,wt,pt,w,p,c,mp)) {
		sol[i] = true;
		Backtrack(i+1,sol,best,wt,pt,w+wt[i],p+pt[i],c,mp);
		sol[i] = false;
		Backtrack(i+1,sol,best,wt,pt,w,p,c,mp);
	}
}

template <typename WT, typename PT,/*table type*/typename T>
void KnapsackBacktrack(const WT& wt, const PT& pt, T c) {
	using W = typename WT::value_type;
	using P = typename PT::value_type;
	W capacity = c;
	std::vector<size_t> si;
	WT swt; /*sorted weight table*/
	PT spt; /*sorted profit table*/
	GetSortedIndexAndValue(wt,pt,si,swt,spt);
	auto N = std::size(wt);
	std::vector<bool> best(N),sol(N);
	auto mp = std::numeric_limits<long double>::min();
	Backtrack(0,sol,best,swt,spt,W{0},P{0},capacity,mp);
#ifdef DEBUG
	printf("%Lf\n",mp);
	for (size_t i = 0; i < std::size(best); ++i) {
		if (best[i]) printf("%-4lu",si[i]);
	}
	puts("");
#endif
}

/* Branch and bound */

//test
int main() {
	std::vector<double> w = {2,3.14,1.98,5,3};
	std::vector<int> p = {40,50,100,95,30};
	KnapsackBacktrack(w,p,10);
	return 0;
}
