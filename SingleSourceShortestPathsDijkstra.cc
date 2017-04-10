/*
 * Dijkstra’s algorithm solves the single-source shortest-paths
 * problem on a weighted, directed graph G = (V,E) for the case
 * in which all edge weights are nonnegative. Therefore, we
 * assume that w(u,v) ≥ 0 for each edge (u,v) ∈ E.
 * As we shall see, with a good implementation, the running time
 * of Dijkstra’s algorithm is lower than that of the
 * Bellman-Ford algorithm.
 *
 * Dijkstra’s algorithm maintains a set S of vertices whose
 * final shortest-path weights from the source s have already
 * been determined. The algorithm repeatedly selects the vertex
 * u ∈ V - S with the minimum shortest-path estimate, adds u to
 * S, and relaxes all edges leaving u.
 */
/*
 * INITIALIZE-SINGLE-SOURCE(G,s)
 * 	for each vertex x ∈ G.V
 * 		v.d = ∞
 * 		v.π = NIL
 * 	s.d = 0
 *
 * RELAX(u,v,w)
 * 	if v.d > u.d + w(u,v)
 * 		v.d = u.d + w(u,v)
 * 		v.π = u
 *
 * DIJKSTRA(G,w,s)
 *	INITIALIZE-SINGLE-SOURCE(G,s)
 *	S = ∅
 *	Q = G.V
 *	while Q ≠ ∅
 *		u = EXTRACT-MIN(Q)
 *		S = S ∪ {u}
 *		for each vertex v ∈ G.Adj[u]
 *			RELAX(u,v,w)
 */
/* Can handle graph with cycles, but Dijkstra cannot process
 * graph with negative-weight edges.
 * Time complexity O(V^2)
 */
#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>

#define DEBUG
const int INF = INT_MAX;

void PrintPath(int v, int p[]) {
	if (p[v] == v) printf("%-3d",v);
	else {
		PrintPath(p[v], p);
		printf("%-3d",v);
	}
}

/*Dijkstra using Heap*/
template <typename T, int N>
void SingleSourceShortestPathsDijkstraCore(T (&w)[N], int u) {
	int d[N], p[N];
	bool visited[N];
	memset(visited, 0, sizeof(visited));
	for (auto& i : d) i = INF;

	auto cmp = [](auto& v1, auto& v2)
				{return v1.first > v2.first;};
	std::priority_queue<
		std::pair<int,int>,
		std::vector<std::pair<int,int>>,
		decltype(cmp)> pq(cmp);

	d[u] = 0; p[u] = u;
	pq.emplace(d[u], u);

	while (!pq.empty()) {
		int u = pq.top().second; pq.pop();
		if (visited[u]) continue;
		visited[u] = true;
		for (int v = 0; v < N; ++v) {
			if (!visited[v] && d[v] - d[u] > w[u][v]) {
				d[v] = d[u] + w[u][v];
				p[v] = u;
				pq.emplace(d[v], v);
			}
		}
	}

#ifdef DEBUG
	fprintf(stdout,"Implementation using Heap\n");
	for (int v = 0; v < N; ++v) {
		fprintf(stdout, "DIST:%5d\nPATH: ",d[v]);
		PrintPath(v, p);
		fprintf(stdout, "\n");
	}
#endif
}

/*Dijkstra not using Heap*/
template <typename T, int N>
void SingleSourceShortestPathsDijkstraCoreSimple(
		T (&w)[N], int u) {
	int d[N], p[N];
	bool visited[N];
	memset(visited, 0, sizeof(visited));
	for (auto& i : d) i = INF;
	d[u] = 0; p[u] = u;

	for (int i = 0; i < N; ++i) {

/* determine the next nearest vertex */
		auto min = INF;
		for (int v = 0; v < N; ++v) {
			if (!visited[v] && d[v] < min) {
				min = d[v];
				u = i;
			}
		}
		if (min == INF) break;
		visited[u] = true;
/* Relax vertices leaving u */
		for (int v = 0; v < N; ++v) {
			if (!visited[v] && d[v] - d[u] > w[u][v]) {
				d[v] = d[u] + w[u][v];
				p[v] = u;
			}
		}
	}

#ifdef DEBUG
	fprintf(stdout,"Simple implementation\n");
	for (int v = 0; v < N; ++v) {
		fprintf(stdout, "DIST:%5d\nPATH: ",d[v]);
		PrintPath(v, p);
		fprintf(stdout, "\n");
	}
#endif
}

template <typename T, int N>
void SingleSourceShortestPathsDijkstra(T (&w)[N], int u) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (i == j) w[i][j] = 0;
			if (w[i][j] < INF) {w[j][i] = w[i][j];}
		}
	}
	SingleSourceShortestPathsDijkstraCore(w, u);
	SingleSourceShortestPathsDijkstraCoreSimple(w, u);
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
	SingleSourceShortestPathsDijkstraCore(simpleG,0);
	SingleSourceShortestPathsDijkstraCoreSimple(simpleG,0);
#ifdef DEBUG
	//fprintf(stdout, "Undirected Graph\n");
#endif
	//SingleSourceShortestPathsDijkstra(simpleG,0);
}
