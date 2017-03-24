/*
 * PRINT-ALL-PAIRS-SHORTEST-PATH(π,i,j)
 * 	if i == j
 * 		print i
 * 	elseif π[i][j] == NIL
 * 		print "no path from" i "to" j "exisits"
 * 	else
 * 		PRINT-ALL-PAIRS-SHORTEST-PATH(π,i,j)
 * 		print j
 */
/*
 * FLOYD-WARSHALL(W)
 * 	n = W.rows
 * 	D⁽⁰⁾ = W
 * 	for k = 1 to n
 * 		let D⁽ᵏ⁾ = (d⁽ᵏ⁾ [i][j]) be a new n×n matrix
 * 		for i = 1 to n
 * 			for j = 1 to n
 * 				if d⁽ᵏ⁻¹⁾[i][k]+d⁽ᵏ⁻¹⁾[k][j] < d⁽ᵏ⁻¹⁾[i][j]
 * 					d⁽ᵏ⁾[i][j] = d⁽ᵏ⁻¹⁾[i][k]+d⁽ᵏ⁻¹⁾[k][j]
 * 					π⁽ᵏ⁾[i][j] = π⁽ᵏ⁻¹⁾[k][j]
 * 	return D⁽ⁿ⁾
 */
/* Compare this algorithm to TransitiveClosureWarshall */
#include <cstring>
#include <climits>
#include <type_traits>
#include <cstdio>
#define DEBUG

constexpr int INF = INT_MAX;
constexpr int NIL = -1;

template <typename T, int N>
void AllPairsShortestPathsFloydWarshall(T (&w)[N]) {
	std::remove_reference_t<decltype(w)> d /*delta*/;
	int p[N][N] /*pi*/;
	memcpy(d, w, sizeof(w));

	for (int u = 0; u < N; ++u) {
		for (int v = 0; v < N; ++v) {
			if (u == v) p[u][u] = u;
			else if (w[u][v] != INF) p[u][v] = u;
			else p[u][v] = NIL;
		}
	}

	for (int k = 0; k < N; ++k) {
		for (int u = 0; u < N; ++u) {
			for (int v = 0; v < N; ++v) {
				if (d[u][k] != INF && d[k][v] != INF
						&& d[u][v] > d[u][k] + d[k][v]) {
					p[u][v] = p[k][v];
					d[u][v] = d[u][k] + d[k][v];
				}
			}
		}
	}
#ifdef DEBUG
	for (int u = 0; u < N; ++u) {
		for (int v = 0; v < N; ++v) {
			if (p[u][v] != NIL) fprintf(stderr,"%5d",p[u][v]);
			else fprintf(stderr,"  NIL");
		}
		fprintf(stderr,"\n");
	}
	fprintf(stderr, "\n");
	for (int u = 0; u < N; ++u) {
		for (int v = 0; v < N; ++v) {
			if (d[u][v] != INF) fprintf(stderr,"%5d",d[u][v]);
			else fprintf(stderr, "  INF");
		}
		fprintf(stderr,"\n");
	}
#endif
}

int main () {
	int a[][4] = {
		{  0,  5,INF, 10},
		{INF,  0,  3,INF},
		{INF,INF,  0,  1},
		{INF,INF,INF,  0}
	};
	AllPairsShortestPathsFloydWarshall(a);
	return 0;
}
