/* Dynamic Programing (DP) Technique */
#include <cstdio>
#include <cstring>
#include <type_traits>
#define DEBUG

template<typename T, int N>
void TransitiveClosureWarshall(T (&e)[N]) {
	std::remove_extent_t<T> tc[N][N];
	memcpy(tc, e, sizeof(tc));
	for (int k = 0; k < N; ++k)
		for (int u = 0; u < N; ++u)
			for (int v = 0; v < N; ++v)
				if (tc[u][k] && tc[k][v]) tc[u][v] = true;
#ifdef DEBUG
	fprintf(stderr, "\n");
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) printf("%3d", tc[i][j]);
		fprintf(stderr, "\n");
	}
#endif
}

int main() {
	bool closure[][4] = {
		{1, 1, 0, 1},
		{0, 1, 1, 0},
		{0, 0, 1, 1},
		{0, 0, 0, 1}
	};
	TransitiveClosureWarshall(closure);
}
