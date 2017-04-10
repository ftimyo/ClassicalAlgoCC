#include <cstdio>
#include <algorithm>
#include <cstring>
#define DEBUG

template<typename T, int N>
void DFSVisit(T (&e)[N], int u, int p, int& time, int visited[],
		int low[], bool br[][N]) {
	low[u] = visited[u] = ++time;
	for (int v = 0; v < N; ++v) {
		if (!(e[u][v] || e[v][u]) || v == p || u == v) continue;
		if (0 == visited[v]) {
			DFSVisit(e, v, u, time, visited, low, br);
			if (low[v] > visited[u]) br[u][v] = true;
			low[u] = std::min(low[u], low[v]);
		} else {
			low[u] = std::min(low[u], visited[v]);
		}
	}
}

template<typename T, int N>
void BridgeTarjan(T (&e)[N]) {
	int visited[N], low[N];
	bool br[N][N];
	memset(br, 0, sizeof(br));
	memset(visited, 0, sizeof(visited));
	int time = 0;
	for (int u = 0; u < N; ++u) {
		if (visited[u]) continue;
		DFSVisit(e, u, u, time, visited, low, br);
	}
#ifdef DEBUG
	fprintf(stderr, "\n");
	for (int u = 0; u < N; ++u) for (int v = 0; v < N; ++v)
        if (br[u][v])
            fprintf(stderr, "%4d,%4d\n", u, v);
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
	BridgeTarjan(graph);
	BridgeTarjan(graph2);
	return 0;
}
