/* Discover the new vertices by growing a spanning tree
 * Search new closest vertices through known closeset vertices
 * Since there are |V| vertices, the path of farthest vertex is
 * at most |V| - 1.
 * Assuming no negative edge, the algorithm search the new vertex
 * by level.
 * Time complexity O(V^2)
 */

#include <climits>
#include <cstring>
#include <cstdio>
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
void SingleSourceShortestPathsLabelSetting(T (&w)[N], int s) {
	int p[N] /*pi*/, d[N] /*delta*/;
	bool visited[N];
	memset(visited,0,sizeof(visited));
	for (auto& i : d) i = INF;
	for (auto& i : p) i = NIL;
	d[s] = 0; p[s] = s; visited[s] = true;
	for (int i = 0; i < N - 1; ++i) {
		int min = INF, u, v;
		for (int i = 0; i < N; ++i) {
/* Find a vertex in the path tree */
			if (!visited[i]) continue;
			for (int j = 0; j < N; ++j) {
/* Find a vertex not in the path tree */
				if (!visited[j] && min - w[i][j] > d[i]) {
					u = i; v = j; min = d[i] + w[i][j];
				}
			}
		}
		if (min == INF)	break;
		visited[v] = true;
		p[v] = u;
		d[v] = min;
	}
#ifdef DEBUG
	fprintf(stdout,"Label Setting\n");
	for (int v = 0; v < N; ++v) {
		if (d[v] == INF) continue;
		fprintf(stdout, "DIST:%5d\nPATH: ",d[v]);
		PrintPath(v, p);
		fprintf(stdout, "\n");
	}
#endif
}
//test
int main() {
	int simpleG[][9] = {
		{INF,4,INF,INF,INF,INF,INF,8,INF},
		{INF,INF,8,INF,INF,INF,INF,11,INF},
		{INF,INF,INF,7,INF,4,INF,INF,2},
		{INF,INF,INF,INF,9,14,INF,INF,INF},
		{INF,INF,INF,INF,INF,10,INF,INF,INF},
		{INF,INF,INF,INF,INF,INF,2,INF,INF},
		{INF,INF,INF,INF,INF,INF,INF,1,6},
		{INF,INF,INF,INF,INF,INF,INF,INF,7},
		{INF,INF,INF,INF,INF,INF,INF,INF,INF}
	};
#ifdef DEBUG
	fprintf(stdout, "Directed Graph\n");
#endif
	SingleSourceShortestPathsLabelSetting(simpleG,0);
}
