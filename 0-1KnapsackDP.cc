/*
 * Let A be an optimal subset of the n items. There are two
 * cases: either A contains item[n] or it does not. If A
 * does not contain item[n], A is equal to an optimal subset
 * of the first n - 1 items. If A does contain item[n], the
 * total profit of the items in A is equal to p[n] plus the
 * optimal profit obtained when the items can be chosen from
 * the first n - 1 items under the restriction that the
 * total weight cannot exceed c - w[n], where c is the
 * capacity. Therefore, the principle of optimality applies.
 * 
 * If for i > 0 and c > 0, when let P[i][c] be the optimal
 * profit obtained when choosing items only from the first i
 * items under the restriction that the total weight cannot
 * exceed c,
 * if w[i] <= c:
 * 	P[i][c] = maximum(P[i-1][c],p[i]+P[i-1][c-w[i]])
 * if w[i] > c:
 * 	P[i][c] = P[i-1][c]
 */
#include <type_traits>
#include <iterator>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>

template <typename WT, typename PT, typename W,
		 typename = std::enable_if_t<
		 std::is_integral<W>::value &&
		 std::is_integral<typename WT::value_type>::value>>
void Knapsack(WT& wt, PT& pt, W C){
	auto N = std::size(wt);
	using I = decltype(N);
	long double P[N+1][C+1];
	memset(P,0,sizeof(P));
	for (I i = 0; i < N; ++i) {
		for (I c = 0; c <= C; ++c) {
			if (wt[i] <= c)
				P[i+1][c] = std::max(P[i][c],
                                     pt[i]+P[i][c-wt[i]]);
			else
				P[i+1][c] = P[i][c];
		}
	}
	printf("%Lf\n",P[N][C]);
}

template <typename WT, typename PT, typename W,
		 typename = std::enable_if_t<
		 std::is_integral<W>::value &&
		 std::is_integral<typename WT::value_type>::value>>
void Knapsack2(WT& wt, PT& pt, W C){
	auto N = std::size(wt);
	using I = decltype(N);
	long double P[C+1];
	memset(P,0,sizeof(P));
	for (I i = 0; i < N; ++i) {
		for (I c = C; wt[i] <= c; --c) {
			P[c] = std::max(P[c],pt[i]+P[c-wt[i]]);
		}
	}
	printf("%Lf\n",P[C]);
}

template <typename WT, typename PT, typename W,
		 typename = std::enable_if_t<
		 std::is_integral<W>::value &&
		 std::is_integral<typename WT::value_type>::value>>
void Knapsack3(WT& wt, PT& pt, W C){
	auto N = std::size(wt);
	using I = long long;
	long double P[C+1];
	bool SOL[N][C+1];
	memset(P,0,sizeof(P));
	memset(SOL,0,sizeof(SOL));
	for (I i = 0; i < N; ++i) {
		for (I c = C; wt[i] <= c; --c) {
			if (pt[i] + P[c-wt[i]] > P[c]) {
				P[c] = pt[i] + P[c-wt[i]];
				SOL[i][c] = true;
			}
		}
	}
	printf("%Lf\n",P[C]);
/* construct the sol */
	for (I i = N-1, c = C; i >= 0;--i) {
		if (SOL[i][c]) {
			printf("%5lld",i);
			c -= wt[i];
		}
	}
	puts("");
}
template <typename WT, typename PT, typename W,
		 typename = std::enable_if_t<
		 std::is_integral<W>::value &&
		 std::is_integral<typename WT::value_type>::value>>
void Knapsack4(WT& wt, PT& pt, W C){
	auto N = std::size(wt);
	using I = long long;
	long double P[N+1][C+1];
	memset(P,0,sizeof(P));
	for (I i = 0; i < N; ++i) {
		for (I c = 0; c <= C; ++c) {
			if (wt[i] <= c)
				P[i+1][c] = std::max(P[i][c],
                                     pt[i]+P[i][c-wt[i]]);
			else
				P[i+1][c] = P[i][c];
		}
	}
	printf("%Lf\n",P[N][C]);
/* construct the solution */
	for (I i = N-1, c = C; i >= 0;--i) {
		if (c-wt[i] >= 0 && P[i+1][c] == pt[i]+P[i][c-wt[i]]) {
			printf("%5lld",i);
			c -= wt[i];
		}
	}
	puts("");
}

//test
int main() {
	std::vector<int> w = {5,10,5,2};
	std::vector<int> p = {10,50,30,40};
	Knapsack(w,p,16);
	Knapsack2(w,p,16);
	Knapsack3(w,p,16);
	Knapsack4(w,p,16);
	std::vector<int> wt = {10, 20, 30};
	std::vector<int> pt = {60, 100, 120};
	Knapsack(wt,pt,50);
	Knapsack2(wt,pt,50);
	Knapsack3(wt,pt,50);
	Knapsack4(wt,pt,50);
	std::vector<int> wt2 = {61,18};
	std::vector<int> pt2 = {94,85};
	Knapsack(wt2,pt2,78);
	Knapsack2(wt2,pt2,78);
	Knapsack3(wt2,pt2,78);
	Knapsack4(wt2,pt2,78);
}
