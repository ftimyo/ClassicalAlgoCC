/* NP Complete
 * A tour (also called a Hamiltonian circuit) in a directed
 * graph is a path from a vertex to itself that passes
 * through each of the other vertices exactly once.
 *
 * Use backtraking to determine all hamiltonian circuits.
 */

#include <cctype>
#include <vector>
#define DEBUG
static constexpr int NE = 0;

template <typename T, int N, typename P, typename V>
void FindPath(T (&e)[N][N], P& path, V& sol,
		bool visited[], size_t len) {
	auto u = path[len-1];
	if (len == N) {
		auto r = path[0];
		if (e[u][r] == NE) return;
		sol.push_back(path);
	}
	for (size_t v = 0; v < N; ++v) {
		if (visited[v] || e[u][v] == NE) continue;
		visited[v] = true;
		path[len] = v;
		FindPath(e,path,sol,visited,1+len);
		visited[v] = false;
	}
}

template <typename T, int N>
void HamiltonianCircuits(T (&e)[N][N], size_t s) {
	std::vector<size_t> path(N);
	bool visited[N];
	std::vector<decltype(path)> sol;
	std::memset(visited,0,sizeof(visited));
	path[0] = s;visited[s] = true;
	FindPath(e,path,sol,visited,1);

#ifdef DEBUG
	for (auto& p : sol) {
		for (auto v : p) printf("%4lu",v);
		printf("%4lu",s);
		puts("");
	}
#endif
}

int main() {
	bool graph[][5] = {
			{0, 1, 0, 1, 0},
			{1, 0, 1, 1, 1},
			{0, 1, 0, 0, 1},
			{1, 1, 0, 0, 1},
			{0, 1, 1, 1, 0},
		};
	HamiltonianCircuits(graph,0);
	return 0;
}
