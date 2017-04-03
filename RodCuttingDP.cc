/*
 * Problem: Given a rod of length n inches and a table of prices
 * pi for i = 1,2,...,n, determine the maximum revenue rn
 * obtainable by cutting up the rod and selling the pieces. Note
 * that if the price pn for a rod of length n is large enough, an
 * optimal solution may require no cutting at all.
 *
 * rₙ = max(pᵢ + rₙ₋ᵢ), where 1≤i≤n.
 * ie.
 * rₙ = max(pₙ,r₁ + rₙ₋₁,r₂ + rₙ₋₂,...,rₙ₋₁ + r₁)
 *
 * //Top-down with memoization
 * MEMOIZED-CUT-ROD(p,n)
 * 	let r[0..n] be a new array
 * 	for i = 0 to n
 * 		r[i] = -∞
 * 	return MEMOIZED-CUT-ROD-AUX(p,n,r)
 *
 * MEMOIZED-CUT-AUX(p,n,r)
 * 	if r[n] ≥ 0
 * 		return r[n]
 * 	if n == 0
 * 		q = 0
 * 	else q = -∞
 * 		for i = 1 to n
 * 			q = max(q,p[i]+MEMOIZED-CUT-ROD-AUX(p,n-i,r))
 *	r[n] = q
 *	return q
 *
 * //bottom-up
 * BOTTOM-UP-CUT-ROD(p,n)
 * 	let r[0..n] be a new array
 * 	r[0] = 0
 * 	for j = 1 to n
 * 		q = -∞
 * 		for i = 1 to j
 * 			q = max(q,p[i]+r[j-i])
 * 		r[j] = q
 * 	return r[n]
 *
 * //extend bottom-up
 * EXTENDED-BOTTOM-UP-CUT-ROD(p,n)
 * 	let r[0..n] and s[0..n] be a new array
 * 	r[0] = 0
 * 	for j = 1 to n
 * 		q = -∞
 * 		for i = 1 to j
 * 			if q < p[i] + r[j-i]
 * 				q = p[i]+r[j-i]
 * 				s[j] = i
 * 		r[j] = q
 * 	return r and s
 *
 * PRINT-CUT-ROD-SOLUTION(p,n)
 * 	(r,s) = EXTENDED-BOTTOM-UP-CUT-ROD(p,n)
 * 	while n > 0
 * 		print s[n]
 * 		n = n - s[n]
 */
#include <type_traits>
#include <limits>
#include <cstdio>
#define DEBUG
template <typename T, int N>
void PrintCutRodSolution(T (&r)[N], int s[], int n) {
	printf("R = %4d\n", r[n]);
	while (n > 0) {
		printf("%4d",s[n]);
		n -= s[n];
	}
	puts("");
}
template <typename T, int N>
void BottomUpCutRod(T (&p)[N], int n) {
	using P = std::remove_reference_t<T>; 
	P r[N];
	int s[N];
	r[0] = 0;
	for (int j = 1; j < N; ++j) {
		P q = std::numeric_limits<P>::min();
		for (int i = 1; i <= j; ++i) {
			if (q < p[i] + r[j-i]) {
				q = p[i] + r[j-i];
				s[j] = i;
			}
		}
		r[j] = q;
	}
#ifdef DEBUG
	puts("Bottom Up r[j] = max{p[i]+r[j-i]} 1<=i<=j");
	PrintCutRodSolution(r,s,n);
	for (auto x : r) printf("%4d",x);
	puts("");
	for (auto x : s) printf("%4d",x);
	puts("");
#endif
}
template <typename T, int N>
void BottomUpCutRod2(T (&p)[N], int n) {
	using P = std::remove_reference_t<T>; 
	P r[N];
	int s[N];
	r[0] = 0;
	for (int j = 1; j < N; ++j) {
		auto q = p[j];
		for (int i = 1; i <= j/2; ++i) {
			if (q < r[i] + r[j-i]) {
				q = r[i] + r[j-i];
				s[j] = i;
			}
		}
		r[j] = q;
	}
#ifdef DEBUG
	puts("Bottom Up r[j] = max{r[i]+r[j-i]} 1<=i<=j/2");
	PrintCutRodSolution(r,s,n);
	for (auto x : r) printf("%4d",x);
	puts("");
	for (auto x : s) printf("%4d",x);
	puts("");
#endif
}

template <typename T, int N>
auto MemoizedCutRodAux(T (&p)[N], int n, int r[], int s[]) {
	using P = std::remove_reference_t<T>; 
	if (r[n] >= 0) return r[n];
	P q;
	if (n == 0) {
		q = 0;
		s[n] = 0;
	} else {
		q = std::numeric_limits<P>::min();
		for (int i = 1; i <= n; ++i) {
			auto q0 = p[i]+MemoizedCutRodAux(p,n-i,r,s);
			if (q0 > q) {
				q = q0;
				s[n] = i;
			}
		}
	}
	r[n] = q;
	return q;
}

template <typename T, int N>
void MemoizedCutRod(T (&p)[N], int n) {
	using P = std::remove_reference_t<T>; 
	int r[N], s[N];
	for (auto& x : r) x = std::numeric_limits<P>::min();
	auto q = MemoizedCutRodAux(p,n,r,s);
#ifdef DEBUG
	puts("MemoizedCutRod");
	PrintCutRodSolution(r,s,n);
	for (auto x : r) printf("%4d",x);
	puts("");
	for (auto x : s) printf("%4d",x);
	puts("");
#endif
}

int main() {
	int p[] = {0,1,5,8,9,10,17,17,20,24,30};
	BottomUpCutRod(p,10);
	MemoizedCutRod(p,10);
	BottomUpCutRod2(p,10);
	return 0;
}
