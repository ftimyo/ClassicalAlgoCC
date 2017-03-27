/*
 * Worst-case running time 𝚯(n²), Average-case running time 𝚯(n²)
 * Insertion sort is a fast in-place sorting algorithm for small
 * input size due to its tight inner loops.
 */
/*
 * INSERTION-SORT(A)
 * 	for j = 2 to A.length
 * 		key = A[j]
 *  	// Insert A[j] into the sorted sequence A[1..j-1].
 *		i = j - 1
 *		while i > 0 and A[i] > key
 *			A[i+1] = A[i]
 *			i = i - 1
 *		A[i+1] = key
 */

#include <iterator>
#include <vector> //for test case
#include <string> //for test case
#include <cstdio>
#include <functional>
#define DEBUG
template <typename Itr, typename Cmp>
void InsertionSort(Itr b, Itr e, Cmp cmp) {
	if (b == e) return;
	for (auto i = std::next(b); i != e; ++i) {
		auto key = *i;
		auto j = std::prev(i);
		for (; (j >= b && cmp(key,*j)); --j) {
			*std::next(j) = *j;
		}
		*std::next(j) = key;
	}
}
template <typename Itr>
void InsertionSort(Itr b, Itr e) {
	InsertionSort(b,e,std::less<typename std::iterator_traits<Itr>::value_type>());
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
	InsertionSort(begin(a1),end(a1));
	InsertionSort(begin(a2),end(a2));
	InsertionSort(begin(a3),end(a3));
	InsertionSort(begin(a5),end(a5));
	InsertionSort(begin(a6),end(a6));
	InsertionSort(begin(s1),end(s1));
	InsertionSort(begin(a7),end(a7));
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
