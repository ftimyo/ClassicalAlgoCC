#include <cstdio>
#include <algorithm>
#include <cstring>
#define DEBUG

template<typename T, int N>
void DFSVisit(T (&e)[N], int u, int p, int& time, int visited[],
		int low[], bool av[]) {
	low[u] = visited[u] = ++time;
	int child = 0;
	bool nbe = false; //No Back Edge
	for (int v = 0; v < N; ++v) {
		if (!(e[u][v] || e[v][u]) || v == p || u == v) continue;
		if (0 == visited[v]) {
			DFSVisit(e, v, u, time, visited, low, av);
			++child;
/* if there is no vertex in subtree rooted with v has
 * a back edge to one of the ancestors of u, set the nbe flag.
 * if u is not the root of the tree, u is an articulation vertex 
 */
			if (low[v] >= visited[u]) nbe = true;
			low[u] = std::min(low[u], low[v]);
		} else {
			low[u] = std::min(low[u], visited[v]);
		}
	}
/* if u is the root of the tree, and it has more than 1 children,
 * u is an articulation vertex. */
	if ((u == p && child > 1) || (u != p && nbe)) av[u] = true;
}

template<typename T, int N>
void ArticulationVerticesTarjan(T (&e)[N]) {
	int visited[N], low[N];
	bool av[N];
	memset(av, 0, sizeof(av));
	memset(visited, 0, sizeof(visited));
	int time = 0;
	for (int u = 0; u < N; ++u) {
		if (visited[u]) continue;
		DFSVisit(e, u, u, time, visited, low, av);
	}
#ifdef DEBUG
	for (int u = 0; u < N; ++u) {
		if (av[u]) fprintf(stderr, "%4d", u);
	}
	fprintf(stderr, "\n");
#endif
}

int main() {
	int graph[][5] = {
		{0, 1, 1, 1, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0}
	};
	bool graph2[][10] {
		{0, 1, 0, 0, 1, 1, 0, 0, 0, 0},
		{0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 1, 0, 0}
	};
	ArticulationVerticesTarjan(graph);
	ArticulationVerticesTarjan(graph2);
	return 0;
}
