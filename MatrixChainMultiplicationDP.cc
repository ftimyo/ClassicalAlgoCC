/*
 * Problem: Given a chain ＜A₁,A₂,...,Aₙ＞ of n matrices, where
 * for i = 1,2,...,n, matrix Aᵢ has dimension pᵢ₋₁ × pᵢ, fully
 * parenthesize the product A₁A₂...Aₙ in a way that minimizes the
 * number of scalar multiplications.
 * Let us adopt the notation Aᵢ․․ⱼ, where i ≤ j, for the matrix
 * that results from evaluating the product AᵢAᵢ₊₁...Aⱼ.
 * Let m[i,j] be the minimum number of scalar multiplications
 * needed to compute the matrix Aᵢ․․ⱼ; for the full problem, the
 * lowest-cost way to compute A₁․․ₙ would thus be m[1,n].
 * Let us assume that to optimally parenthesize, we split the
 * product AᵢAᵢ₊₁...Aⱼ between Aₖ and Aₖ₊₁, where i ≤ k < j.
 * m[i,j] = m[i,k] + m[k+1,j] + pᵢ₋₁ × pₖ ×  pⱼ
 *
 * Thus the recursive definition for the minimum cost of
 * parenthesizing the product AᵢAᵢ₊₁...Aⱼ becomes
 * m[i,j] = 0						if i = j,
 * m[i,j] = min{m[i,k]+m[k+1,j]+pᵢ₋₁pₖpⱼ},where i≤k<j	if i<j.
 *
 * To construct the optimal solution, we define s[i,j] to be a
 * value of k at which we split the product AᵢAᵢ₊₁...Aⱼ in an
 * optimal parentheization.
 *
 * MATRIX-CHAIN-ORDER(p)
 * 	n = p.length - 1
 * 	let m[1..n,1..n] and s[1..n-1,2..n] be new tables
 * 	for i = 1 to n
 * 		m[i,i] = 0
 * 	for l = 2 to n			// l is the chain length
 * 		for i = 1 to n-l+1
 * 			j = i+l-1
 * 			m[i,j] = ∞
 * 			for k = i to j - 1
 * 				q = m[i,k] + m[k+1,j] + pᵢ₋₁ × pₖ ×  pⱼ
 * 				if q < m[i,j]
 * 					m[i,j] = q
 * 					s[i,j] = k
 * 	return m and s
 *
 * PRINT-OPTIMAL-PARENS(s,i,j)
 * 	if i == j
 * 		print "A"ᵢ
 * 	else print"("
 * 		PRINT-OPTIMAL-PARENS(s,i,s[i,j])
 * 		PRINT-OPTIMAL-PARENS(s,s[i,j]+1,j)
 * 		print ")"
 *
 * //Top-down solution
 * MEMOIZED-MATRIX-CHAIN(p)
 * 	n = p.length - 1
 * 	let m[1..n,1..n] be new tables
 * 	for i = 1 to n
 * 		for j = i to n
 * 			m[i,j] = ∞
 * 	return LOOKUP-CHAIN(m,p,1,n)
 *
 * LOOKUP-CHAIN(m,p,i,j)
 * 	if m[i,j] < ∞
 * 		return m[i,j]
 * 	if i == j
 * 		m[i,j] = 0
 * 	else for k = i to j - 1
 * 		q = LOOKUP-CHAIN(m,p,i,k) + LOOKUP-CHAIN(m,p,k+1,j)
 * 				+ pᵢ₋₁ × pₖ ×  pⱼ
 * 		if q < m[i,j]
 * 			m[i,j] = q
 *	return m[i,j]
 */

#include <type_traits>
#include <limits>
#include <cstdio>
#define DEBUG
template <int N>
void PrintOptimalParens(int (&s)[N][N], int i, int j) {
	if (i == j) printf("A%d",i);
	else {
		printf("(");
		PrintOptimalParens(s,i,s[i][j]);
		PrintOptimalParens(s,s[i][j]+1,j);
		printf(")");
	}
}
template <typename T, int N>
void MatrixChainOrder(T (&p)[N]) {
	using NT = std::remove_reference_t<T>;
	NT m[N][N];
	int s[N][N];
	for (int i = 0; i < N; ++i) m[i][i] = 0;
	for (int l = 2; l < N; ++l) {
		for (int i = 1; i <= N - l; ++i) {
			int j = i + l - 1;
			m[i][j] = std::numeric_limits<NT>::max();
			for (int k = i; k < j; ++k) {
				auto q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
				if (q < m[i][j]) {
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
#ifdef DEBUG
	puts("Bottomup");
	printf("Total Multiplication: %lu\n", m[1][N-1]);
	PrintOptimalParens(s,1,N-1);
	puts("");
#endif
}

template <typename T, int N>
auto LookupChain(T (&p)[N], T(&m)[N][N], int (&s)[N][N], int i, int j) {
	using NT = std::remove_reference_t<T>;
	static constexpr auto INF = std::numeric_limits<NT>::max();
	if (m[i][j] < INF) return m[i][j];
	if (i == j) m[i][j] = 0;
	else {
		for (int k = i; k < j; ++k) {
			auto q = LookupChain(p,m,s,i,k) +
				LookupChain(p,m,s,k+1,j) +
				p[i-1]*p[k]*p[j];

			if (q < m[i][j]) {
				m[i][j] = q;
				s[i][j] = k;
			}
		}
	}
	return m[i][j];
}
template <typename T, int N>
void MemoizedMatrixChain(T (&p)[N]) {
	using NT = std::remove_reference_t<T>;
	static constexpr auto INF = std::numeric_limits<NT>::max();
	NT m[N][N];
	int s[N][N];
	for (int i = 0; i < N; ++i) {
		for (int j = i; j < N; ++j) {
			m[i][j] = INF;
		}
	}
	LookupChain(p,m,s,1,N-1);
#ifdef DEBUG
	puts("Memoized");
	printf("Total Multiplication: %lu\n", m[1][N-1]);
	PrintOptimalParens(s,1,N-1);
	puts("");
#endif
}

int main () {
	size_t p[] = {30,35,15,5,10,20,25};
	MatrixChainOrder(p);
	MemoizedMatrixChain(p);
	return 0;
}
