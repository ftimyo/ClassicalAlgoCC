/*
 * Worst-case running time 𝚯(n²), average-case 𝚯(n lg n)
 * Divide:
 * Partition (rearrange) the array A[p..r] into two (possibly
 * empty) subarrays A[p..q-1] and A[q+1..r] such that each
 * element of A[p..q-1] is less than or equal to A[q], which is,
 * in turn, less than or equal to each element of A[q+1..r].
 * Compute the index q as part of this partitioning procedure.
 * Conquer:
 * Sort the two subarrays A[p..q-1] and A[q+1..r] by recursive
 * calls to quicksort.
 * Combine:
 * Because the subarrays are already sorted, no work is needed to
 * combine them: the entire array A[p..r] is now sorted.
 *
 * QUICKSORT(A,p,r)
 * 	if p < r
 * 		q = PARTITION(A,p,r)
 * 		QUICKSORT(A,p,q-1)
 * 		QUICKSORT(A,q+1,r)
 *
 * PARTITION(A,p,r)
 * 	x = A[r]
 * 	i = p - 1
 * 	for j = p to r - 1
 * 		if A[j] ≤ x
 * 			i = i + 1
 * 			exchange A[i] with A[j]
 * 	exchange A[i+1] with A[r]
 * 	return i + 1
 *
 * HOARE-PARTITION(A,p,r)
 * 	x = A[p]
 * 	i = p - 1
 * 	j = r + 1
 * 	while TRUE
 * 		repeat
 * 			j = j - 1
 * 		until A[j] ≤ x
 * 		repeat
 * 			i = i + 1
 * 		until A[i] ≥ x
 * 		if i < j
 * 			exchange A[i] with A[j]
 * 		else return j
 *
 */

#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include <functional>
#define DEBUG
template <typename Itr, typename Cmp>
auto PartitionHoare(Itr p, Itr r, Cmp cmp) {
	if (std::distance(p,r) < 2) return p;
	auto i = p, j = r;
	auto x = *p;
	while (true) {
		while (++i < r && !cmp(x, *i));
		while (p < --j && cmp(x, *j));
		if (i < j) std::iter_swap(i,j);
		else {
			std::iter_swap(p,j);
			return j;
		}
	}
}
template <typename Itr, typename Cmp>
void QuickSortHoare(Itr p, Itr r, Cmp cmp) {
	if (std::distance(p,r) < 2) return;
	if (p != r) {
		auto q = PartitionHoare(p,r, cmp);
		QuickSortHoare(p,q,cmp);
		QuickSortHoare(q+1,r,cmp);
	}
}

template <typename Itr>
void QuickSortHoare(Itr p, Itr r) {
	QuickSortHoare(p,r,
			std::less<typename std::iterator_traits<Itr>::value_type>());
}
template <typename Itr, typename Cmp>
auto Partition(Itr p, Itr r, Cmp cmp) {
	auto x = *std::prev(r);
	auto i = std::prev(p);
	for (auto j = p; j < r; ++j) {
		if (!cmp(x,*j)) {
			++i;
			std::iter_swap(i,j);
		}
	}
	return i;
}

template <typename Itr, typename Cmp>
void QuickSort(Itr p, Itr r, Cmp cmp) {
	if (std::distance(p,r) < 2) return;
	if (p != r) {
		auto q = Partition(p,r, cmp);
		QuickSort(p,q,cmp);
		QuickSort(q+1,r,cmp);
	}
}

template <typename Itr>
void QuickSort(Itr p, Itr r) {
	QuickSort(p,r,std::less<typename std::iterator_traits<Itr>::value_type>());
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
	int a3[] = {0,1,0,4,0,3,0,1,7,11,2,1,1,2};
	int a5[] = {1};
	std::vector<int> a6 = {7,6,5,4,3,2,1};
	std::vector<int> a7 = {};
	std::string s1{"What a wonderful day!"};
#ifdef DEBUGQUICKSORT
	QuickSort(begin(a1),end(a1));
	QuickSort(begin(a2),end(a2));
	QuickSort(begin(a3),end(a3));
	QuickSort(begin(a5),end(a5));
	QuickSort(begin(a6),end(a6));
	QuickSort(begin(s1),end(s1));
	QuickSort(begin(a7),end(a7));
	fprintf(stderr, "Correctness %d\n",
			Test(QuickSort<decltype(begin(a1)),decltype(std::less<int>())>,std::less<int>()));
#else
	QuickSortHoare(begin(a1),end(a1));
	QuickSortHoare(begin(a2),end(a2));
	QuickSortHoare(begin(a3),end(a3));
	QuickSortHoare(begin(a5),end(a5));
	QuickSortHoare(begin(a6),end(a6));
	QuickSortHoare(begin(s1),end(s1));
	QuickSortHoare(begin(a7),end(a7));
	fprintf(stderr, "Correctness %d\n",
			Test(QuickSortHoare<decltype(begin(a1)),decltype(std::less<int>())>,std::less<int>()));
#endif
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
