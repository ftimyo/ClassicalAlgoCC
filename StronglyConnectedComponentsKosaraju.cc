/*
 * STRONGLY-CONNECTED-COMPONENTS(G)
 * 1 call DFS(G) to compute finishing times u.f for each vertex u
 * 2 compute Gᵀ
 * 3 call DFS(Gᵀ), but in the main loop of DFS, consider the
 * 		vertices in order of decreasing u.f (as computed in
 * 		line 1)
 * 4 output the vertices of each tree in the depth-first forest
 * 		formed in line 3 as a separate SCC
 */
#include <cstdio>
#include <cstring>
#include <stack>
#define DEBUG

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
void TopologicalSort(T (&e)[N], int tordered[]) {
	bool visited[N];
	memset(visited, 0, sizeof(visited));
	auto back = tordered + N;
	for (int u = 0; u < N; ++u) {
		if (!visited[u]) {
			DFSVisit(e, u, visited, &back);
		}
	}
}

/*
 * DFS traverse the component and
 * contract the visited vertices to root
 */
template<typename T, int N>
void Contract(T (&e)[N], int root, bool visited[], int scc[]) {
	std::stack<int> ss;
	scc[root] = root;
	visited[root] = true;
	ss.push(root);
	while (!ss.empty()) {
		int u = ss.top(); ss.pop();
		for (int v = 0; v < N; ++v) {
			if (e[v][u] && !visited[v]) {
				visited[v] = true; //mark visited before expand
				scc[v] = root;
				ss.push(v);
			}
		}
	}
}


template<typename T, int N>
void StronglyConnectedComponentsKosaraju(T (&e)[N]) {
	int tordered[N];
	int scc[N];
	TopologicalSort(e, tordered);
	bool visited[N];
	memset(visited, 0, sizeof(visited));
	for (auto u : tordered) {
		if (!visited[u]) {
			Contract(e, u, visited, scc);
		}
	}

#ifdef DEBUG
	fprintf(stderr, "\n");
	for (auto u : tordered) {
		fprintf(stderr, "%4d:%4d\n", u, scc[u]);
	}
#endif
}

//test
int main() {
	bool graph[][5] = {
		{0, 0, 1, 1, 0},
		{1, 0, 0, 0, 0},
		{0, 1, 0, 0, 0},
		{0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0}
	};
	bool graph2[][8] = {
		{0, 1, 1, 1, 0, 0, 0, 0},
		{1, 0, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 0, 1, 0, 0, 0},
		{0, 0, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0, 1, 0},
		{0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 1, 0, 0}
	};
	StronglyConnectedComponentsKosaraju(graph);
	StronglyConnectedComponentsKosaraju(graph2);
	return 0;
}
