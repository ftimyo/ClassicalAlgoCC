/* BELLMAN-FORD(G,w,s)
 * 	INITIALIZE-SINGLE-SOURCE(G,s)
 * 	for i = 1 to |G.V| - 1
 * 		for each edge (u,v) ∈ G.E
 * 			RELAX(u,v,w)
 * 	for each edge (u,v) ∈ G.E
 * 		if v.d > u.d + w(u,v)
 * 			return FALSE
 * 	return TRUE
 */
/* Can handle all cases of single source shortest path problem,
 * when encounter negative weight cycle, the algorithm return
 * false
 * Time: O(V^3)
 */
#include <cstdio>
#include <climits>
#define DEBUG

constexpr int INF = INT_MAX;
constexpr int NIL = INT_MIN;

void PrintPath(int v, int p[]) {
	if (p[v] == v) printf("%-3d",v);
	else {
		PrintPath(p[v], p);
		printf("%-3d",v);
	}
}


template <typename T, int N>
bool SingleSourceShortestPathsBellmanFord(T (&w)[N], int s) {
	int d[N] /*delta*/, p[N] /*pi*/;
/* initialize single source G,s */
	for (auto& i : d) i = INF;
	for (auto& i : p) i = NIL;
	d[s] = 0; p[s] = s;
/* calculate shortest distance */
	for (int i = 0; i < N - 1; ++i) {

/* at least update the ith level of the path tree,
 * after the following iterations */
		for (int u = 0; u < N; ++u)  {
			for (int v = 0; v < N; ++v) {
				if (w[u][v] < INF &&
                    d[u] < INF && d[v] > w[u][v] + d[u]) {
                    /*relaxation*/
					p[v] = u; d[v] = d[u] + w[u][v];
				}
			}
		}
	}
/* checking for negative weighted cycle */
	for (int u = 0; u < N; ++u)
		for (int v = 0; v < N; ++v)
			if (d[v] < INF && d[u] < INF &&
                d[v] - d[u] > w[u][v]) return false;
#ifdef DEBUG
	fprintf(stdout,"Bellman-Ford\n");
	for (int v = 0; v < N; ++v) {
		fprintf(stdout, "DIST:%5d\nPATH: ",d[v]);
		if (d[v] == INF) continue;
		PrintPath(v, p);
		fprintf(stdout, "\n");
	}
#endif
	return true;
}

int main() {
	int W1[][5] = {
		{INF,	-1,	 4,INF,INF},
		{INF,INF,	 3,	 2,	 2},
		{INF,INF,INF,INF,INF},
		{INF,	1,	 5,INF,INF},
		{INF,INF,INF,	-3,INF}
	};
	int W2[][5] = {
		{INF, -3,INF,INF,INF},
		{INF,INF,  5,  1,INF},
		{INF,INF,INF,INF,INF},
		{  2,  2,	 3,INF,INF},
		{INF,INF,	 4, -1,INF},
	};
	if (!SingleSourceShortestPathsBellmanFord(W1,0))
		printf("Detect Negative Cycle\n");
	if (!SingleSourceShortestPathsBellmanFord(W2,4))
		printf("Detect Negative Cycle\n");
/*Graph W is a DAG*/
	int W[][6] = {
		{INF,  5,  3,INF,INF,INF},
		{INF,INF,  2,  6,INF,INF},
		{INF,INF,INF,  7,  4,  2},
		{INF,INF,INF,INF, -1,  1},
		{INF,INF,INF,INF,INF, -2},
		{INF,INF,INF,INF,INF,INF}
	};
	SingleSourceShortestPathsBellmanFord(W,1);
}
