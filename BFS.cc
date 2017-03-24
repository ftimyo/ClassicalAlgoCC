/*
 * BFS(G,s)
 * 	for each vertex u ∈ G.V - {s}
 * 		u.color = WHITE
 * 		u.d = ∞
 * 		u.π = NIL
 * 	s.color = GRAY
 * 	s.d = 0
 * 	s.π = NIL
 * 	Q = ∅
 * 	ENQUEUE(Q,s)
 * 	while Q ≠ ∅
 * 		u = DEQUEUE(Q)
 * 		for each v ∈ G.Adj[u]
 * 			if v.color == WHITE
 * 				v.color = GRAY
 * 				v.d = u.d + 1
 * 				v.π = u
 * 				ENQUEUE(Q,v)
 * 		u.color = BLACK
 */
#include <cstdio>
#include <cstring>
#include <queue>
#define DEBUG

template<typename T, int N>
void BFSVisit(T (&e)[N], int u, bool visited[], int d[], int p[]) {
	std::queue<int> q;
	visited[u] = true;
	q.push(u);
	while (!q.empty()) {
		int u = q.front(); q.pop();
#ifdef DEBUG
		fprintf(stderr,"%4d:%4d:%4d\n",u,p[u],d[u]);
#endif
		for (int v = 0; v < N; ++v) {
			if (e[u][v] && !visited[v]) {
				visited[v] = true;
				p[v] = u;
				d[v] = d[u] + 1;
				q.push(v);
			}
		}
	}
}

void PrintPath(int v, int p[]) {
	if (v == p[v]) {
		fprintf(stdout, "%3d", v);
	} else {
		PrintPath(p[v], p);
		fprintf(stdout, "%3d", v);
	}
}

template<typename T, int N>
void BFS(T (&e)[N]) {
	bool visited[N];
	int d[N]; /*distance from root*/
	int p[N]; /*parent*/
	memset(visited, 0, sizeof(visited));
	for (int u = 0; u < N; ++u) {
		if (!visited[u]) {
			p[u] = u; d[u] = 0;
			BFSVisit(e, u, visited, d, p);
		}
	}
#ifdef DEBUG
	for (int u = 0; u < N; ++u) {
		PrintPath(u, p);
		fprintf(stdout, "\n");
	}
#endif
}


//test
int main() {
	bool graph[][5] = {
		{0, 1, 0, 1, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 0, 1, 0},
		{0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0}
	};
	BFS(graph);
	return 0;
}
