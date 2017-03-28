/*
 * Worst-case running time 𝚯(n lg n), Average-case 𝚯(n lg n)
 * Merge sort has a better asymptotic running time, but it does
 * not operate in place
 */
/*
 * MERGE(A,p,q,r)
 * 	n₁ = q - p + 1
 * 	n₂ = r - q
 * 	let L[1..n₁+1] and R[1..n₂+1] be new arrays
 * 	for i = 1 to n₁
 * 		L[i] = A[p+i-1]
 * 	for j = 1 to n₂
 * 		R[j] = A[q+j]
 * 	L[n₁+1] = ∞
 * 	R[n₂+1] = ∞
 * 	i = 1
 * 	j = 1
 * 	for k = p to r
 * 		if L[i] ≤ R[j]
 * 			A[k] = L[i]
 * 			i = i + 1
 * 		else A[k] = R[j]
 * 			j = j + 1
 *
 * MERGE-SORT(A,p,r)
 * 	if p < r
 * 		q = ⎣ (p+r)/2 ⎦
 * 		MERGE-SORT(A,p,q)
 * 		MERGE-SORT(A,q+1,r)
 * 		MERGE(A,p,q,r)
 */
#include <iterator>
#include <limits>
#include <vector>	//test case
#include <string> //test case
#include <iostream>
#include <cstdio>
#include <functional>


#define DEBUG
template <typename Itr, typename Cmp>
void Merge(Itr p, Itr q, Itr r, Cmp cmp) {
	using T = typename std::iterator_traits<Itr>::value_type; /*Iterator Type*/
	auto n1 = q - p + 1;
	auto n2 = r - q + 1;
	T L[n1], R[n2];
	auto j = L;
	for (auto i = p; i != q; ++i, ++j) *j = *i;
	j = R;
	for (auto i = q; i != r; ++i, ++j) *j = *i;
	L[n1-1] = std::numeric_limits<T>::max();
	R[n2-1] = std::numeric_limits<T>::max();
	auto i = L; j = R;
	for (auto k = p; k != r; ++k) {
		if (cmp(*i,*j)) {
			*k = *i;
			++i;
		} else {
			*k = *j;
			++j;
		}
	}
}

template <typename Itr, typename Cmp>
void MergeSort(Itr p, Itr r, Cmp cmp) {
	if (p == r) return;
	if (std::next(p) != r) {
/* Lo, (p+r)/2 may overflow */
		auto q = p + (r - p) / 2;
		MergeSort(p,q,cmp);
		MergeSort(q,r,cmp);
		Merge(p,q,r,cmp);
	}
}
template <typename Itr>
void MergeSort(Itr p, Itr r) {
	MergeSort(p,r,std::less<typename std::iterator_traits<Itr>::value_type>());
}

#ifdef DEBUG
template <typename It>
void printIA(It b, It e) {
	for (;b != e; ++b) fprintf(stderr,"%-4d",*b);
	fprintf(stderr,"\n");
}
template <typename It>
void printS(It b, It e) {
	for (;b != e; ++b) fprintf(stderr,"%c",*b);
	fprintf(stderr,"\n");
}
#endif
//Heavy test for correctness
#include <cstdlib>
#include <ctime>
#include <algorithm>
template <typename Func, typename Cmp>
bool Test(Func func, Cmp cmp, int n = 10000) {
	using namespace std;
	srand(time(NULL));
	int a[100];
	for (int i = 0; i < n; ++i) {
		for (auto& x : a) {
			x = rand() % 10 * (((rand()%2)<<1)-1);
		}
		func(begin(a),end(a),cmp);
		if (!std::is_sorted(begin(a),end(a),cmp)) return false;
	}
	return true;
}
//test
using namespace std;
int main() {
	int a1[] = {7,6,5,4,3,2,1,0,9,8};
	int a2[] = {0,0,0,0,0,0,0};
	int a3[] = {0,0,0,0,0,0,0,1,1,1,1,2,2,2,2};
	int a5[] = {1};
	std::vector<int> a6 = {7,6,5,4,3,2,1};
	std::vector<int> a7 = {};
	std::string s1{"What a wonderful day!"};
	MergeSort(begin(a1),end(a1));
	MergeSort(begin(a2),end(a2));
	MergeSort(begin(a3),end(a3));
	MergeSort(begin(a5),end(a5));
	MergeSort(begin(a6),end(a6));
	MergeSort(begin(s1),end(s1));
	MergeSort(begin(a7),end(a7));
	fprintf(stderr, "Correctness %d\n",
			Test(MergeSort<decltype(begin(a1)),decltype(std::less<int>())>,std::less<int>()));
#ifdef DEBUG
	printIA(begin(a1),end(a1));
	printIA(begin(a2),end(a2));
	printIA(begin(a3),end(a3));
	printIA(begin(a5),end(a5));
	printIA(begin(a6),end(a6));
	printS(begin(s1),end(s1));
	printIA(begin(a7),end(a7));
#endif
}
