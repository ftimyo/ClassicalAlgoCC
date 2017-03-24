/*
 * MST-KRUSKAL(G, w)
 * 	A = ∅
 * 	for each vertex v ∈ G.V
 * 		MAKE-SET(v)
 * 	sort the edges of G.E into nondecreasing order by weight w
 * 	for each edge (u,v) ∈ G.E, take in nondecreasing order by weight
 * 		if FIND-SET(u) ≠ FIND-SET(v)
 * 			A = A ∪ {(u,v)}
 * 			UNION(u,v)
 * 	return A
 */
#include <cstdio>
#include <algorithm>
#include <iterator>

#define DEBUG

struct Edge {
	int u, v, w;
};

int FindSet(int u, int s[]) {
	return u == s[u] ? u : s[u] = FindSet(s[u], s);
}
void Union(int u, int v, int s[] ,int sc[]) {
	auto ur = FindSet(u,s), vr = FindSet(v,s);
	if (sc[ur] < sc[vr]) std::swap(ur,vr);
	s[vr] = ur;
	sc[ur] += sc[vr];
}

template<typename T, int N>
void MSTKruskalCore(T (&edges)[N], int V /*# of Vertices*/) {
	int s[V]; /*disjoint Sets*/
	/*disjoint Set Cardinality*/
	int sc[V]; /*No Need, but it boosts perf of union-find*/
	for (int u = 0; u < V; ++u) {s[u] = u; sc[u] = 1;}
	/*sort the edges by weight*/
	std::sort(std::begin(edges), std::end(edges),
			[](auto e1, auto e2){return e1->w < e2->w;});
	T mst[N];
	auto i = mst; /*inserter*/
	for (auto e : edges) {
		if (FindSet(e->u,s) == FindSet(e->v,s)) continue;
		*i = e; ++i;
		Union(e->u, e->v, s, sc);
	}

#ifdef DEBUG
	for (auto e = mst; e < i; ++e) {
		fprintf(stderr, "(%-4d -- %4d) : %4d\n",
				(*e)->u, (*e)->v, (*e)->w);
	}
#endif
}

template<typename T, int N>
void MSTKruskal(T (&E)[N], int V /*# of Vertices*/) {
	using ET = std::remove_extent_t<T>;
	ET* se[N];
	std::transform(std::begin(E), std::end(E), std::begin(se),
			[](auto& uv){return &uv;});
	MSTKruskalCore(se, V);
}


int main() {
	Edge e[] = {
		{0,1,4},{0,7,8},
		{1,2,8},{1,7,11},
		{2,3,7},{2,5,4},{2,8,2},
		{3,4,9},{3,5,14},
		{4,5,10},
		{5,6,2},
		{6,7,1},{6,8,6},
		{7,8,7}
	};
	MSTKruskal(e, 9);
	return 0;
}
