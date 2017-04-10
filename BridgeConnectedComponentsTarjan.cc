/*An undirected graph is called Bridge-Connected if there are no
 * bridges can be found within the component*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>
#define DEBUG

template<typename T, int N>
void DFSVisit(T (&e)[N], int u, int p, int& time, int visited[],
		int low[], int bcc[], std::stack<int>& ss) {
	low[u] = visited[u] = ++time;
	ss.push(u);
	for (int v = 0; v < N; ++v) {
/* prevent selfloop and revisit the immediate parent */
		if (!(e[u][v] || e[v][u]) || v == p || u == v) continue;
		if (0 == visited[v]) {
			DFSVisit(e, v, u, time, visited, low, bcc, ss);
			low[u] = std::min(low[u], low[v]);
		} else {
			low[u] = std::min(low[u], visited[v]);
		}
	}
/* if u is the highest ancester its descendants can reach, p-u
 * becomes the bridge between u-rooted subtree and u's ancester
 */
	int i;
	if (low[u] == visited[u]) {
		do {
			i = ss.top();
			bcc[i] = u;
			ss.pop();
		} while (i != u);
	}
}

template<typename T, int N>
void BridgeConnectedComponentsTarjan(T (&e)[N]) {
	int visited[N], low[N];
	int bcc[N];
	std::stack<int> ss;
	memset(bcc, ~0u, sizeof(bcc));
	memset(visited, 0, sizeof(visited));
	int time = 0;
	for (int u = 0; u < N; ++u) {
		if (visited[u]) continue;
		DFSVisit(e, u, u, time, visited, low, bcc, ss);
	}
#ifdef DEBUG
	fprintf(stderr, "\n");
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (bcc[j] == i) fprintf(stderr, "%4d:%4d\n",i,j);
		}
	}
#endif
}

/*test*/
int main() {
	int graph[][12] = {
		{0,1,0,0,0,0,1,0,0,0,0,0},
		{0,0,1,1,0,5,0,0,0,0,0,0},
		{0,0,0,1,1,0,0,0,0,0,0,0},
		{0,0,0,0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,1,1,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,1,0,0,0},
		{0,0,0,0,0,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	};
	int graph2[][16] = {
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};
	BridgeConnectedComponentsTarjan(graph);
	BridgeConnectedComponentsTarjan(graph2);
	return 0;
}
