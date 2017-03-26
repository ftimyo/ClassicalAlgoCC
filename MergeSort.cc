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


#define DEBUG
template <typename Itr> /*Iterator Type*/
void Merge(Itr p, Itr q, Itr r) {
	using T = typename std::iterator_traits<Itr>::value_type;
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
		if (*i <= *j) {
			*k = *i;
			++i;
		} else {
			*k = *j;
			++j;
		}
	}
}

template <typename Itr>
void MergeSort(Itr p, Itr r) {
	if (p == r) return;
	if (std::next(p) != r) {
/* Lo, (p+r)/2 may overflow */
		auto q = p + (r - p) / 2;
		MergeSort(p,q);
		MergeSort(q,r);
		Merge(p,q,r);
	}
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
