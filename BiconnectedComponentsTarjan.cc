/*An undirected graph is called Biconnected if there are two vertex-disjoint
 * paths between any two vertices. In a Biconnected Graph, there is a simple
 * cycle through any two vertices.
 * By convention, two nodes connected by an edge form a biconnected graph, but
 * this does not verify the above properties. For a graph with more than two
 * vertices, the above properties must be there for it to be Biconnected.*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>
#define DEBUG

template<typename T, int N>
void DFSVisit(T (&e)[N], int u, int p, int& time, int visited[],
		int low[], int bcc[][N], int& bccID, std::stack<std::pair<int,int>>& ss) {
	low[u] = visited[u] = ++time;
	for (int v = 0; v < N; ++v) {
/* prevent selfloop and revisit the immediate parent */
		if (!(e[u][v] || e[v][u]) || v == p || u == v) continue;
		if (0 == visited[v]) {
			ss.emplace(u, v);
			DFSVisit(e, v, u, time, visited, low, bcc, bccID, ss);
			low[u] = std::min(low[u], low[v]);
/* if the subtree does not reach a earlier visited vertex, u becomes the
 * articulation point for the ancesters and the v-rooted descendants */
			if (low[v] >= visited[u]) {
				++bccID;
				int i, j;
				do {
					i = ss.top().first;
					j = ss.top().second;
					ss.pop();
					bcc[i][j] = bccID;
				} while (i != u || j != v);
			}
		} else if (visited[v] < visited[u]/*avoid adding visited-edges*/) {
			low[u] = std::min(low[u], visited[v]);
			ss.emplace(u, v);
		}
	}
}

template<typename T, int N>
void BiconnectedComponentsTarjan(T (&e)[N]) {
	int visited[N], low[N];
	int bcc[N][N];
	int bccID = 0;
	std::stack<std::pair<int,int>> ss;
	memset(bcc, 0, sizeof(bcc));
	memset(visited, 0, sizeof(visited));
	int time = 0;
	for (int u = 0; u < N; ++u) {
		if (visited[u]) continue;
		DFSVisit(e, u, u, time, visited, low, bcc, bccID, ss);
	}
#ifdef DEBUG
	for (int k = 1; k <= bccID; ++k) {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				if (bcc[i][j] == k)
					fprintf(stderr, "%4d:%2d,%2d\n", bcc[i][j], i, j);
			}
		}
	}
	fprintf(stderr, "\n");
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
	BiconnectedComponentsTarjan(graph);
	return 0;
}
