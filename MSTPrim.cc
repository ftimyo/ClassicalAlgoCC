/*
 * MST-PRIM(G,w,r)
 * 	for each u ∈ G.V
 * 		u.key = ∞
 * 		u.π = NIL
 * 	r.key = 0
 * 	Q = G.V
 * 	while Q ≠ ∅
 * 		u = EXTRACT-MIN(Q)
 * 		for each v ∈ G.Adj[u]
 * 			if v ∈ Q and w(u,v) < v.key
 * 				v.π = u
 * 				v.key = w(u,v)
 */
#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#define DEBUG
const int INF = INT_MAX;

/*Implementation using Heap*/
template<typename T, int N>
void MSTPrimCore(T (&w)[N], int u) {
	int tw = 0; /*total weight*/
	bool visited[N];
	memset(visited, 0, sizeof(visited));
	int d[N]/*dist to tree*/, p[N] /*parent*/;
	for (auto& i : d) i = INF;

	/*build a min Heap*/
	auto cmp = [](auto v1, auto v2){return v1.first > v2.first;};
	std::priority_queue<std::pair<int, int>,
        std::vector<std::pair<int,int>>,
		decltype(cmp)> pq(cmp);

	d[u] = 0; p[u] = u;
	pq.emplace(d[u],u);
	while (!pq.empty()) {
		int u = pq.top().second; pq.pop();
		if (visited[u]) continue;
		tw += d[u];
		visited[u] = true;
		for (int v = 0; v < N; ++v) {
			if (!visited[v] && w[u][v] < d[v]) {
				d[v] = w[u][v];
				p[v] = u;
				pq.emplace(d[v],v);
			}
		}
	}
#ifdef DEBUG
	printf("Implementation using Heap | weight:%3d\n",tw);
	for (int u = 0; u < N; ++u) {
		if (u == p[u]) continue;
		fprintf(stderr, "%-4d -- %4d\n",p[u],u);
	}
#endif
}

template<typename T, int N>
void MSTPrimCoreSimple(T (&w)[N], int u) {
	int tw = 0; /*total weight*/
	bool visited[N];
	memset(visited, 0, sizeof(visited));
	int d[N]/*dist to tree*/, p[N] /*parent*/;
	for (auto& i : d) i = INF;
	d[u] = 0; p[u] = u;
	for (int i = 0; i < N; ++i) {
/* search for the vertex closest to the spanning tree */
		auto min = INF;
		for (int v = 0; v < N; ++v) if (!visited[v] && d[v]<min){
			u = v;
			min = d[v];
		}
		if (min == INF) break;
		tw += d[u];
		visited[u] = true;
/* relax vertices leaving u */
		for (int v = 0; v < N; ++v) {
			if (!visited[v] && w[u][v] < d[v]) {
				d[v] = w[u][v];
				p[v] = u;
			}
		}
	}
#ifdef DEBUG
	fprintf(stderr, "Simple Implementation | weight:%3d\n",tw);
	for (int u = 0; u < N; ++u) {
		if (u == p[u]) continue;
		fprintf(stderr, "%-4d -- %4d\n",p[u],u);
	}
#endif
}

template<typename T, int N>
void MSTPrim(T (&w)[N], int u) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (i == j) w[i][j] = 0;
			if (w[i][j] < INF) {w[j][i] = w[i][j];}
		}
	}
	MSTPrimCore(w,u);
	MSTPrimCoreSimple(w,u);
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
	MSTPrim(simpleG,0);
}
