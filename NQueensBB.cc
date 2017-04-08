/*
 * Branch and Bound
 * The N queens puzzle is the problem of placing N chess
 * queens on an N×N chessboard so that no two queens
 * threaten each other. Thus, a solution requires that no
 * two queens share the same row, column, or diagonal.
 */
#include <vector>
#include <list>
#include <string>
#include <cstdio>
#define DEBUG
template <typename C, typename V, typename B>
void PlaceQueen(C& b, V& sol, int r,
		B& c, B& d, B& ad) {
	int N = std::size(b);
	if (r == N) {
		sol.push_back(b);
	}
	for (int p = 0; p < N; ++p) {
		int di = r - p + N;
		int adi = r + p;
		if (c[p] || d[di] || ad[adi]) continue;
		c[p] = d[di] = ad[adi] = true;
		b[r] = p;/*place queen at col p in row r*/
		PlaceQueen(b,sol,r+1,c,d,ad);
		c[p] = d[di] = ad[adi] = false;
	}
}

void NQueens(int N) {
	using C = std::vector<int>;
	using B = std::vector<bool>;
	std::list<C> sol;
	C b(N);
	B c(N,false),d(N*2,false),ad(N*2,false);
	PlaceQueen(b,sol,0,c,d,ad);
#ifdef DEBUG
	for (auto& x : sol) {
		for (auto p : x) {
			std::string row(N,'+');
			row[p] = 'Q';
			printf("%s\n",row.c_str());
		}
		puts("");
	}
#endif
	printf("%-5lu sols\n",std::size(sol));
}

int main() {
	NQueens(5);
	return 0;
}
