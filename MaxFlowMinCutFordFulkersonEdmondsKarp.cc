/*
 * using RN = residual network
 *
 * FORD-FULKERSON-METHOD(G,s,t)
 * 	initialize flow f to 0
 * 	while there exists an augmenting path p in the RN Gf
 * 		augment flow f along p
 * 	return f
 */
/*
 * FORD-FULKERSON(G,s,t)
 * 	for each edge (u,v) ∈ G.E
 * 		(u,v).f = 0
 * 	while there exists a path p form s to t in the RN Gf
 * 		cf(p) = min{cf(u,v):(u,v) is in p}
 * 		for each edge (u,v) in p
 * 			if (u,v) ∈ E
 * 				(u,v).f = (u,v).f + cf(p)
 * 			else
 * 				(u,v).f = (v,u).f - cf(p)
 */
#include <cstdio>
#include <climits>
#include <cstring>
#include <type_traits>
#include <queue>
#define DEBUG

constexpr int NIL = -1;
constexpr int INF = INT_MAX;

/* return the min capacity of the path */
template <typename T, int N>
int BFS(T (&e)[N], int s, int t, int p[]) {
	auto min = INF;
	for (int u = 0; u < N; ++u) p[u] = NIL;
	std::queue<int> q;
	p[s] = s;
	q.push(s);
	while (!q.empty()) {
		int u = q.front();q.pop();
		for (int v = 0; v < N; ++v) {
			if (e[u][v] != 0 && p[v] == NIL) {
				p[v] = u; q.push(v);
				min = std::min(min, e[u][v]);
				if (v == t) return min;
			}
		}
	}
	return 0;
}

template <typename T, int N>
void MaxFlowMinCutFordFulkersonEdmondsKarp(T (&C)[N],
                                           int s,int t){
	std::remove_reference_t<decltype(C)> R;
	std::remove_all_extents_t<T> maxflow = 0;
	int p[N];
	memcpy(R,C,sizeof(C));
/* Calculate Residual Graph and maxflow */
	while (int min = BFS(R,s,t,p)) {
		maxflow += min;
		int u = t;
		while(u != s) {
			R[p[u]][u] -= min;
			R[u][p[u]] += min;
			u = p[u];
		}
	}
/* Calculate the min cut */
	std::vector<std::pair<int,int>> cut;
	for (int u = 0; u < N; ++u) {
		if (p[u]==NIL) continue;
		for (int v = 0; v < N; ++v) {
			if (p[v] != NIL || C[u][v] == 0) continue;
			cut.emplace_back(u,v);
		}
	}

#ifdef DEBUG
	fprintf(stderr, "Max Flow:%5d\nCut:\n",maxflow);
	for (auto& e : cut) printf("%-2d--%2d\n",e.first,e.second);
#endif
}

//test
int main() {
	int graph[][6] = {
		{0,16,13, 0, 0, 0},
		{0, 0,10,12, 0, 0},
		{0, 4, 0, 0,14, 0},
		{0, 0, 9, 0, 0,20},
		{0, 0, 0, 7, 0, 4},
		{0, 0, 0, 0, 0, 0}
	};
	MaxFlowMinCutFordFulkersonEdmondsKarp(graph,0,5);
	return 0;
}
