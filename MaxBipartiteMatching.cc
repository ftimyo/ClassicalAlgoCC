/*
 * A matching in a Bipartite Graph is a set of the edges chosen in such a way
 * that no two edges share an endpoint. A maximum matching is a matching of
 * maximum size (maximum number of edges). In a maximum matching, if any edge is
 * added to it, it is no longer a matching. There can be more than one maximum
 * matchings for a given Bipartite Graph.
 */
#include <algorithm>
#include <climits>
#include <cstdio>
#define DEBUG
constexpr int NIL = -1;
template <typename T, int M, int N>
bool DFS(T (&e)[M][N], int u, bool visited[], int p[]) {
	for (int v = 0; v < N; ++v) {
		if (e[u][v] == 0 || visited[v]) continue;
		visited[v] = true;
		if (p[v] == NIL || DFS(e,p[v],visited,p)) {
			p[v] = u;
			return true;
		}
	}
	return false;
}
template <typename T, int M, int N>
void MaxBipartiteMatchingAugmentingPath(T (&e)[M][N]) {
	int p[N] /*pi*/;
	int mm{0}; /*max match cardinality*/
	for (auto& i : p) i = NIL;
	for (int u = 0; u < M; ++u) {
		bool visited[N];
		memset(visited,0,sizeof(visited));
		mm += DFS(e,u,visited,p);
	}
#ifdef DEBUG
	fprintf(stdout,"AugmentingPath MBM:%5d\nMatches:\n",mm);
	for (int v = 0; v < N; ++v)
		if(p[v]!=NIL)fprintf(stdout,"%3d --> %-3d\n",v,p[v]);
		else fprintf(stdout, "%3d --> NIL\n",v);
#endif
}

int main() {
	int bpGraph[][6] = {
		{0, 1, 1, 0, 0, 0},
		{1, 0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0, 0},
		{0, 0, 1, 1, 0, 0},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1}
	};
	int bpGraph2[][5] = {
		{1,1,0,0,1},
		{0,1,1,1,0},
		{0,0,1,0,0},
		{1,1,0,0,0}
	};
	MaxBipartiteMatchingAugmentingPath(bpGraph);
	MaxBipartiteMatchingAugmentingPath(bpGraph2);
	return 0;
}
