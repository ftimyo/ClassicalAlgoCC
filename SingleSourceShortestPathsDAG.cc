/* By relaxing the edges of a weighted dag (directed acyclic graph)
 * G = (V,E) according to a topological sort of its vertices, we can
 * compute shortest paths from a single source in 𝚯(V_E) time.
 * Shortest paths are always well defined in a dag, since even if
 * there are negative-weight edges, no negative-weight cycles can exist.
 *
 * The algorithm starts by topologically sorting the dag to impose a linear
 * ordering on the vertices. If the dag contains a path from vertex u to
 * vertex v, then u precedes v in the topological sort. We make just one pass
 * over the vertices in the topologically sorted order. As we process
 * each vertex, we relax each edge that leaves the vertex.
 */
/*
 * DAG-SHORTEST-PATHS(G,w,s)
 * 	topologically sort the vertices of G
 * 	INITIALIZE-SINGLE-SOURCE(G,s)
 * 	for each vertex u, taken in topologically sorted order
 * 		for each vertex v ∈ G.Adj[u]
 * 			RELAX(u,v,w)
 */
/* Can hand negative-weight edge, but due to the Topological sorting,
 * it can only process DAG (graph without cycle).
 * Time complexity 𝚯(V+E)*/
#include <cstdio>
#include <climits>
#include <cstring>

#define DEBUG
constexpr int INF = INT_MAX;
constexpr int NIL = INT_MIN;
template<typename T, int N>
void DFSVisit(T (&e)[N], int u, bool visited[], int **ordered) {
	visited[u] = true;
	for (int v = 0; v < N; ++v) {
		if (e[u][v] && !visited[v]) {
			DFSVisit(e, v, visited, ordered);
		}
	}
	*(--*ordered) = u;
}
template<typename T, int N>
void TopologicalSort(T (&e)[N], int root, int ordered[]) {
	bool visited[N];
	memset(visited, 0, sizeof(visited));
	auto back = ordered + N;
	DFSVisit(e, root, visited, &back);
}

void PrintPath(int v, int p[]) {
	if (p[v] == v) printf("%-3d",v);
	else {
		PrintPath(p[v], p);
		printf("%-3d",v);
	}
}

template<typename T, int N>
void SingleSourceShortestPathsDAG(T (&w)[N], int s) {
	int V[N]; /*vertices in topological order*/
	for (auto& i : V) i = NIL;
	TopologicalSort(w,s,V);
	int d[N] /*delta*/, p[N] /*pi*/;
	for (auto& i : d) i = INF;
	d[s] = 0; p[s] = s;
	for (auto u : V) {
		if (u == NIL) continue;
		for (int v = 0; v < N; ++v) {
			if (d[u] != INF && w[u][v] != INF && d[v] > d[u] + w[u][v]) {
				p[v] = u; d[v] = d[u] + w[u][v];
			}
		}
	}
#ifdef DEBUG
	fprintf(stdout,"Shortest Path Directed Acyclic Graph\n");
	for (int v = 0; v < N; ++v) {
		fprintf(stdout, "DIST:%5d\nPATH: ",d[v]);
		if (d[v] == INF) continue;
		PrintPath(v, p);
		fprintf(stdout, "\n");
	}
#endif
}
//test
int main() {
	int W[][6] = {
		{INF,  5,  3,INF,INF,INF},
		{INF,INF,  2,  6,INF,INF},
		{INF,INF,INF,  7,  4,  2},
		{INF,INF,INF,INF, -1,  1},
		{INF,INF,INF,INF,INF, -2},
		{INF,INF,INF,INF,INF,INF}
	};
	SingleSourceShortestPathsDAG(W,1);
	return 0;
}
