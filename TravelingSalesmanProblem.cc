/* NP Hard
 * TravelingSalemanProblem is
 * Minimum Weight Hamiltonian Circuit
 */

#include <cctype>
#include <vector>
#include <limits>
#define DEBUG
constexpr int NE = std::numeric_limits<int>::max();

template <typename T, int N, typename P>
void FindPath(T (&e)[N][N], P& path, P& sol,
		bool visited[], size_t len, T w, T& mw) {
	auto u = path[len-1];
	if (len == N) {
		auto r = path[0];
		if (e[u][r] == NE) return;
		w += e[u][r];
		if (w < mw) {
			sol.assign(std::begin(path),std::end(path));
			mw = w;
		}
	}
	for (size_t v = 0; v < N; ++v) {
		if (visited[v] || e[u][v] == NE || w+e[u][v] >= mw)
			continue;
		visited[v] = true;
		path[len] = v;
		FindPath(e,path,sol,visited,1+len,w+e[u][v],mw);
		visited[v] = false;
	}
}

template <typename T, int N>
void TSP(T (&e)[N][N], size_t s) {
	std::vector<size_t> path(N),sol(N);
	bool visited[N];
	std::memset(visited,0,sizeof(visited));
	path[0] = s;visited[s] = true;
	T mw = NE;
	FindPath(e,path,sol,visited,1,0,mw);

#ifdef DEBUG
	printf("weight%5d\n",mw);
	for (auto v : sol) printf("%4lu",v);
	printf("%4lu",s);
	puts("");
#endif
}

int main() {
	int graph[][7] = {
		{NE,18, 6,NE,NE,NE,NE},
		{18,NE,NE, 8,NE,NE,29},
		{ 6,NE,NE,NE, 2, 6,NE},
		{NE, 8,NE,NE,NE, 9, 3},
		{NE,NE, 2,NE,NE, 5,NE},
		{NE,NE, 6, 9, 5,NE, 7},
		{NE,29,NE, 3,NE, 7,NE},
	};
	TSP(graph,0);
	return 0;
}
