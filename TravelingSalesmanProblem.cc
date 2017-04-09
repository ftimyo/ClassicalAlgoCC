/* NP Hard
 * TravelingSalemanProblem is
 * Minimum Weight Hamiltonian Circuit
 * An optimal tour in a weighted, directed graph is such a
 * path of minimum length. The Traveling Salesperson problem
 * is to find an optimal tour in a weighted, directed graph
 * when at least one tour exists.
 */

#include <cctype>
#include <vector>
#include <limits>
#include <queue>
#define DEBUG
#define STAT

#ifdef STAT
static size_t __vs__;
#define RESET()\
	do{\
		__vs__ = 0;\
	}while(0)
#define COUNT()\
	do{\
		++__vs__;\
	}while(0)
#define PRINT()\
	do{\
		fprintf(stderr,"NODE EXPAND %lu\n",__vs__);\
	}while(0)
#endif
constexpr int NE = std::numeric_limits<int>::max();

template <typename T, int N, typename P>
void FindPath(T (&e)[N][N], P& path, P& sol,
		bool visited[], size_t len, T w, T& mw) {
#ifdef STAT
	COUNT();
#endif
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
#ifdef STAT
	RESET();
#endif
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
#ifdef STAT
	PRINT();
#endif
#endif
}

/*Best first search*/
template <typename W, typename I>
struct Node {
	W b;
	W w;
	std::vector<I> p;
	Node(Node&& n):b{n.b},w{n.w},p{std::move(n.p)}{}
	Node(const Node& n):b{n.b},w{n.w},p{n.p}{}
	Node& operator=(Node&& n){
		b=n.b;w=n.w;p=std::move(n.p); return *this;}
	Node& operator=(const Node& n){
		b=n.b;w=n.w;p=n.p;return *this;}
	Node(W weight, W bound):
		b{bound},w{weight},p{}{}
	/*for comparison for minheap*/
	bool operator<(const Node& n) const {return b > n.b;}
};
template <typename W, size_t N,  typename ND, typename B>
auto Bound(W (&e)[N][N], const ND& n, B& visited) {
	decltype(n.b) b = n.w;
	for (size_t u = 0; u < N; ++u) {
		if (visited[u]) continue;
		auto d = NE;
		for (size_t v = 0; v < N; ++v) {
			if (visited[v] || u == v) continue;
			d = std::min(e[u][v],d);
		}
		if (d == NE) return NE;
		else b += d;
	}
	return b;
}
template <typename W, size_t N>
void TSPBestFirstSearch(W (&e)[N][N], size_t s) {
#ifdef STAT
	RESET();
#endif
	using NODE = Node<W,size_t>;
	W mw = NE;
	std::vector<size_t> best;
	std::vector<bool> visited(N, false);
	std::priority_queue<NODE> minheap;
	auto n = NODE{0,0}; n.p.push_back(s);
	n.b = Bound(e,n,visited);
	minheap.emplace(std::move(n));
	while (!std::empty(minheap)) {
#ifdef STAT
		COUNT();
#endif
		n = minheap.top(); minheap.pop();
		std::fill_n(std::begin(visited),N,false);
		for (auto i : n.p)visited[i] = true;
		auto u = n.p.back();
		for (size_t v = 0; v < N; ++v) {
			if (visited[v] || e[u][v] == NE) continue;
			auto next = n;
			next.w += e[u][v];
			next.p.push_back(v);
			/*Update Optimal Tour*/
			if (std::size(next.p) == N - 1) {
				size_t t = 0;
				/*find the only vertex left to visit*/
				for (;t < N;++t)if(!visited[t]&&t!=v)break;
				/*check it leads to the starting vertex*/
				if (e[v][t] == NE || e[t][s] == NE)continue;
				next.w += e[v][t] + e[t][s];
				if (next.w < mw) {
					next.p.push_back(t);
					mw = next.w;
					best.swap(next.p);
				}
				continue;
			}
			visited[v] = true;
			next.b = Bound(e,next,visited);
			visited[v] = false;
			if (next.b < mw) {
				minheap.emplace(next);
			}
		}
	}
#ifdef DEBUG
	printf("weight%5d\n",mw);
	for (auto v : best) printf("%4lu",v);
	printf("%4lu",s);
	puts("");
#ifdef STAT
	PRINT();
#endif
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
	TSPBestFirstSearch(graph,0);
	return 0;
}
