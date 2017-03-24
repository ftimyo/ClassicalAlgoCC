/*
 * DFS(G)
 * 	for each vertex u ∈ G.V
 * 		u.color = WHITE
 * 		u.π = NIL
 * 	time = 0
 * 	for each vertex u ∈ G.V
 * 		if u.color == WHITE
 * 			DFS-VISIT(G,u)
 *
 * 	DFS-VISIT(G,u)
 * 		time = time + 1				// white vertex u has just been discovered
 * 		u.d = time
 * 		u.color = GRAY
 * 		for each v ∈ G.Adj[u]	// explore edge (u,v)
 * 			if v.color = WHITE
 * 				v.π = u
 * 				DFS-VISIT(G,v)
 * 		u.color = BLACK				// blacken u; it is finished
 * 		time = time + 1
 * 		u.f = time
 */
#include <cstdio>
#include <cstring>
#define DEBUG

void PrintPath(int v, int p[]) {
	if (v == p[v]) {
		fprintf(stdout, "%3d", v);
	} else {
		PrintPath(p[v], p);
		fprintf(stdout, "%3d", v);
	}
}

template<typename T, int N>
void DFSVisit(T (&e)[N], int u, bool visited[],
		int& t, int d[], int f[], int p[]) {
	t += 1;
	d[u] = t;
	visited[u] = true;
	for (int v = 0; v < N; ++v) {
		if (e[u][v] && !visited[v]) {
			p[v] = u;
			DFSVisit(e, v, visited, t, d, f, p);
		}
	}
	t += 1;
	f[u] = t;
}

template<typename T, int N>
void DFS(T (&e)[N]) {
	bool visited[N];
	int t = 0;
	int d[N]; /*discover time*/
	int f[N]; /*finish time*/
	int p[N]; /*parent*/
	memset(visited, 0, sizeof(visited));
	for (int u = 0; u < N; ++u) {
		if (!visited[u]) {
			p[u] = u;
			DFSVisit(e, u, visited, t, d, f, p);
		}
	}
#ifdef DEBUG
	for (int u = 0; u < N; ++u)
		fprintf(stderr,"%4d:%4d:%4d:%4d\n",u,p[u],d[u],f[u]);
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
	DFS(graph);
	return 0;
}
