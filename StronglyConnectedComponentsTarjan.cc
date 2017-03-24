#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>
#define DEBUG

template<typename T, int N>
void DFSVisit(T (&e)[N], int u, int& time, int visited[],
		bool instack[], int low[], int bcc[], std::stack<int>& ss) {
	low[u] = visited[u] = ++time;
	ss.push(u);
	instack[u] = true;
	for (int v = 0; v < N; ++v) {
/* prevent selfloop */
		if (!e[u][v] || u == v) continue;
		if (0 == visited[v]) {
			DFSVisit(e, v, time, visited, instack, low, bcc, ss);
			low[u] = std::min(low[u], low[v]);
/* prevent revisit vertices through cross edge */
		} else if (instack[v]){
			low[u] = std::min(low[u], visited[v]);
		}
	}
/* if u is the highest ancester its descendants can reach, p-u
 * becomes the bridge between u-rooted subtree and u's ancester */
	int i;
	if (low[u] == visited[u]) {
		do {
			i = ss.top();
			bcc[i] = u;
			ss.pop();
			instack[i] = false;
		} while (i != u);
	}
}

template<typename T, int N>
void StronglyConnectedComponentsTarjan(T (&e)[N]) {
	int visited[N], low[N];
	int bcc[N];
	bool instack[N];
	std::stack<int> ss;
	memset(visited, 0, sizeof(visited));
	memset(bcc, ~0u, sizeof(bcc));
	memset(instack, 0, sizeof(instack));
	int time = 0;
	for (int u = 0; u < N; ++u) {
		if (visited[u]) continue;
		DFSVisit(e, u, time, visited, instack, low, bcc, ss);
	}
#ifdef DEBUG
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (bcc[j] == i) fprintf(stderr, "%4d:%4d\n",i,j);
		}
	}
#endif
}

/*test*/
int main() {
	int graph[][16] = {
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,1,1,0,0,0,1,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
		{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
		{0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,0,1,0,0,1,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,0}
	};
	StronglyConnectedComponentsTarjan(graph);
	return 0;
}
