/*
 * Worst-case running time O(n lg n)
 * min-heap property:	A[PARENT(i)] ≤ A[i]
 * max-heap property: A[PARENT(i)] ≥ A[i]
 * PARENT(i)
 * 	return ⎣ i/2 ⎦
 *
 * LEFT(i)
 * 	return 2i
 *
 * RIGHT(i)
 * 	return 2i + 1
 *
 * MAX-HEAPIFY(A,i)
 *	//lets the value at A[i] float down, subtree rooted at i
 *	//obeys the max-heap property
 * 	l = LEFT(i)
 * 	r = RIGHT(i)
 * 	if l ≤ A.heap-size and A[l] > A[i]
 * 		largest = l
 * 	else largest = i
 * 	if r ≤ A.heap-size and A[r] > A[largest]
 * 		largest = r
 * 	if largest ≠ i
 * 		exchange A[i] with A[largest]
 * 		MAX-HEAPIFY(A,largest)
 *
 * BUILD-MAX-HEAP(A)
 * 	A.heap-size = A.length
 * 	for i = ⎣ A.length/2 ⎦ down to 1
 * 		MAX-HEAPIFY(A,i)
 *
 * HEAPSORT(A)
 * 	BUILD-MAX-HEAP(A)
 * 	for i = A.length downto 2
 * 		exchange A[1] with A[i]
 * 		A.heap-size = A.heap-size - 1
 * 		MAX-HEAPIFY(A,1)
 *
 * HEAP-MAXIMUM(A)
 * 	return A[1]
 *
 * HEAP-EXTRACT-MAX(A)
 * 	if A.heap-size < 1
 * 		error "heap underflow"
 * 	max = A[1]
 * 	A[1] = A[A.heap-size - 1]
 * 	MAX-HEAPIFY(A,1)
 * 	return max
 *
 * HEAP-INCREASE-KEY(A,i,key)
 * 	if key < A[i]
 * 		error "new key is smaller than current key"
 * 	A[i] = key
 * 	while i > 1 and A[PARENT(i)] < A[i]
 * 		exchange A[i] with A[PARENT(i)]
 * 		i = PARENT(i)
 *
 * MAX-HEAP-INSERT(A,key)
 * 	A.heap-size = A.heap-size + 1
 * 	A[A.heap-size] = -∞
 * 	HEAP-INCREASE-KEY(A,A.heap-size,key)
 *
 */

#include <iterator>
#include <functional>

#define DEBUG
#ifdef DEBUG
#include <vector>
#include <string>
#include <cstdio>
#endif
template <typename Itr>
auto Parent(Itr p, Itr i) {
	return std::next(p,std::distance(p,std::prev(i))>>1);
}
template <typename Itr>
auto Left (Itr p, Itr i) {
	return std::next(p,(std::distance(p,i)<<1) + 1);
}
template <typename Itr>
auto Right (Itr p, Itr i) {
	return std::next(p,(std::distance(p,i)<<1) + 2);
}

template <typename Itr, typename Cmp>
void HeapifyUp(Itr p, Itr i, Cmp cmp) {
	while (i > p && cmp(*Parent(p,i),*i)) {
		std::iter_swap(Parent(p,i),i);
		i = Parent(p,i);
	}
}

template <typename Itr, typename Cmp>
void HeapifyDown(Itr p, Itr q, Itr i, Cmp cmp) {
	auto l = Left(p,i);
	auto r = Right(p,i);
	auto t = i;
	if (l < q && cmp(*i,*l)) {
		t = l;
	}
	if (r < q && cmp(*t,*r)) {
		t = r;
	}
	if (t != i) {
		std::iter_swap(t,i);
		HeapifyDown(p,q,t,cmp);
	}
}

template <typename Itr, typename Cmp>
void BuildHeap(Itr p, Itr q, Cmp cmp) {
	if (std::distance(p,q) < 2) return;
	for (auto i = Parent(p,std::prev(q)); i >= p; --i) {
		HeapifyDown(p,q,i,cmp);
	}
}

template <typename Itr, typename Cmp>
void SortHeap(Itr p, Itr q, Cmp cmp) {
	if (std::distance(p,q) < 2) return;
	for (auto i = std::prev(q); i > p; --i) {
		std::iter_swap(i,p);
		HeapifyDown(p,i,p,cmp);
	}
}

template <typename Itr, typename Cmp>
void HeapSort(Itr p, Itr q, Cmp cmp) {
	BuildHeap(p,q,cmp);
	SortHeap(p,q,cmp);
}
template <typename Itr>
void HeapSort(Itr p, Itr q) {
	HeapSort(p,q,
        std::less<
            typename std::iterator_traits<Itr>::value_type>());
}

template <typename Itr>
auto HeapTop(Itr p) {
	return *p;
}

template <typename Itr, typename Cmp>
void HeapPop(Itr p, Itr q, Cmp cmp) {
	if (p == q) return;
	--q;
	std::iter_swap(p,q);
	HeapifyDown(p,q,p,cmp);
}

template <typename Itr, typename Cmp>
void HeapPush(Itr p, Itr q, Cmp cmp) {
	--q;
	HeapifyUp(p,q,cmp);
}

//test
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

void testHeap() {
	int a1[] = {1,6,2,9,4,3,7,5};
	std::vector<int> h;
	printf("Heap Push\n");
	for (auto x : a1) {
		h.push_back(x);
		printf("%-4d",x);
		HeapPush(std::begin(h),std::end(h),std::less<int>());
	}
	printf("\nHeap Pop\n");
	while (!h.empty()) {
		HeapPop(std::begin(h),std::end(h),std::less<int>());
		printf("%-4d",h.back());
		h.pop_back();
	}
	printf("\n");
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
using namespace std;
int main() {
#ifdef DEBUG
	int a1[] = {7,6,5,4,3,2,1,0,9,8};
	int a2[] = {0,0,0,0,0,0,0};
	int a3[] = {0,0,0,0,0,0,0,1,1,1,1,2,2,2,2};
	int a5[] = {1};
	std::vector<int> a6 = {7,6,5,4,3,2,1};
	std::vector<int> a7 = {};
	std::string s1{"What a wonderful day!"};
	HeapSort(begin(a1),end(a1));
	HeapSort(begin(a2),end(a2));
	HeapSort(begin(a3),end(a3));
	HeapSort(begin(a5),end(a5));
	HeapSort(begin(a6),end(a6));
	HeapSort(begin(s1),end(s1));
	HeapSort(begin(a7),end(a7));
	fprintf(stderr, "Correctness %d\n",
        Test(HeapSort<decltype(begin(a1)),
             decltype(std::less<int>())>,std::less<int>()));
	printIA(begin(a1),end(a1));
	printIA(begin(a2),end(a2));
	printIA(begin(a3),end(a3));
	printIA(begin(a5),end(a5));
	printIA(begin(a6),end(a6));
	printS(begin(s1),end(s1));
	printIA(begin(a7),end(a7));
	testHeap();
#endif
}
