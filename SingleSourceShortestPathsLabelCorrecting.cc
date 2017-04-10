/*
 * using B-F = BellmanFord algorithm
 * Similar thought to Bellman, but a little bit faster.
 */
/* Can handle all cases of single source shortest path problem,
 * when encounter negative weight cycle, the algorithm return
 * false
 * Time: O(V^3)
 */
#include <cstdio>
#include <climits>
#include <cstring>
#include <queue>
#define DEBUG

constexpr int INF = INT_MAX;
constexpr int NIL = -1;

void PrintPath(int v, int p[]) {
	if (p[v] == v) printf("%-3d",v);
	else {
		PrintPath(p[v], p);
		printf("%-3d",v);
	}
}


template <typename T, int N>
bool SingleSourceShortestPathsLabelCorrecting(T (&w)[N], int s) {
	int d[N] /*delta*/, p[N] /*pi*/, pe[N] /*# of e in p*/;
	bool inqueue[N];
	std::queue<int> q;
/* initialize single source G,s */
	for (auto& i : d) i = INF;
	for (auto& i : p) i = NIL;
	memset(inqueue, 0, sizeof(inqueue));
	memset(pe, 0, sizeof(pe));
	d[s] = 0; p[s] = s;
	q.push(s);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		inqueue[u] = false;
/* Not required, but perf boost, makes it faster than B-F */
		if (inqueue[p[u]]) continue;
		for (int v = 0; v < N; ++v) {
			if (w[u][v] != INF && w[u][v] + d[u] < d[v]) {
				d[v] = d[u] + w[u][v];
				p[v] = u; pe[v] = pe[u] + 1;
				if (pe[u] > N - 1) return false;
/* Not required, but perf boost, makes it faster than B-F */
				if (inqueue[v]) continue;
				q.push(v); inqueue[v] = true;
			}
		}
	}

#ifdef DEBUG
	fprintf(stdout,"Label Correcting\n");
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
	if (!SingleSourceShortestPathsLabelCorrecting(W1,0))
		printf("Detect Negative Cycle\n");
	if (!SingleSourceShortestPathsLabelCorrecting(W2,4))
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
	SingleSourceShortestPathsLabelCorrecting(W,1);
}
