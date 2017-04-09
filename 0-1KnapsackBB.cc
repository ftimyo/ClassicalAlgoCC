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
#include <queue>
#include <cstdio>
#define DEBUG
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
	if (i < N) {
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

template <typename I, typename W, typename P>
struct Node{
	I i;
	W w;
	P p;
	long double b;
	std::vector<I> sol;
	Node(const Node& n):i{n.i},w{n.w},p{n.p},b{n.b},
		sol{n.sol}{}
	Node(Node&& n):i{n.i},w{n.w},p{n.p},b{n.b},
		sol{std::move(n.sol)}{}
	Node& operator=(Node&& n){
		i = n.i;w=n.w;p=n.p;b=n.b;sol=std::move(n.sol);
		return *this;
	}
	Node& operator=(const Node& n){
		i = n.i;w=n.w;p=n.p;b=n.b;sol=n.sol;
		return *this;
	}
	Node(I idx,W weight, P profit, long double bound = 0):
		i{idx},w{weight},p{profit},b{bound}{}
	inline bool operator<(const Node& n) const {
		return this->b < n.b;
	}
};

/* Branch and bound */
template <typename WT, typename PT, typename IP,
	typename W, typename P>
auto Bound(IP i, WT& wt, PT& pt, W w, P p, W c) {
	auto N = std::size(wt);
	if (w >= c)
		return std::numeric_limits<long double>::min();
/* calculate bound */
	for (;i < N && w + wt[i] < c;++i) {
		w += wt[i];
		p += pt[i];
	}
	if (i < N) {
		p += (c-w)*(static_cast<long double>(pt[i])/wt[i]);
	}
	return static_cast<long double>(p);
}

template <typename WT, typename PT,/*table type*/typename T>
void KnapsackBranchAndBound(const WT& wt, const PT& pt, T c) {
	using W = typename WT::value_type;
	using P = typename PT::value_type;
	using NODE = Node<size_t,W,P>;
	W capacity = c;
	std::vector<size_t> si;
	WT swt; /*sorted weight table*/
	PT spt; /*sorted profit table*/
	GetSortedIndexAndValue(wt,pt,si,swt,spt);
	auto mp = std::numeric_limits<long double>::min();
	std::vector<size_t> best;
	std::priority_queue<NODE> maxheap;
	maxheap.emplace(0,0,0,
			Bound(size_t{0},swt,spt,W{0},P{0},capacity));
	/*best first search*/
	while (!std::empty(maxheap)) {
		auto u = maxheap.top();maxheap.pop();
		auto i = u.i++;
		NODE v{u.i,u.w+swt[i],u.p+spt[i]};
		v.sol = u.sol; v.sol.push_back(si[i]);
		auto bu = Bound(u.i,swt,spt,u.w,u.p,capacity);
		auto bv = Bound(v.i,swt,spt,v.w,v.p,capacity);
		if (v.w <= capacity && v.p > mp) {
			mp = v.p;
			best = v.sol;
		}
		if (bu > mp) {
			u.b = bu;
			maxheap.emplace(std::move(u));
		}
		if (bv > mp) {
			v.b = bv;
			maxheap.emplace(std::move(v));
		}
	}
#ifdef DEBUG
	printf("%Lf\n",mp);
	for (auto x : best) printf("%-4lu", x);
	puts("");
#endif
}

//test
int main() {
	std::vector<double> w = {2,3.14,1.98,5,3};
	std::vector<int> p = {40,50,100,95,30};
	KnapsackBacktrack(w,p,10);
	KnapsackBranchAndBound(w,p,10);
	return 0;
}
