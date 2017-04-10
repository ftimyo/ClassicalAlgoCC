/*
 * Suprise: Fast MinMax implementation
 * def MinMax(A,n)
 * 	for i = 2 to n:
 * 		r = A[i]
 * 		l = A[i-1]
 * 		if l < r:
 * 			min = Min(l,min)
 * 			max = Max(r,max)
 * 		else:
 * 			min = Min(r,min)
 * 			max = Max(l,max)
 * 	return min,max
 *
 * As in quicksort, we partition the input array recursively. But
 * unlike quicksort, which recursively process both sides of the
 * partition. RANDOMIZED-SELECT works on only one side of the
 * partition. This difference shows up in the analysis: whereas
 * quicksort has an expected running time of 𝚯(n lg n), the
 * expected running time of RANDOMIZED-SELECT is 𝚯(n), assuming
 * that the elements are distinct.
 *
 * RANDOMIZED-SELECT(A,p,r,i)
 * 	if p == r
 * 		return A[p]
 * 	q = RANDOMIZED-PARTITION(A,p,r)
 * 	k = q - p + 1
 * 	if i == k			//the pivot value is the answer
 * 		return A[q]
 * 	elseif i < k
 * 		return RANDOMIZED-SELECT(A,p,q-1,i)
 * 	else return RANDOMIZED-SELECT(A,q+1,r,i-k)
 *
 * RANDOMIZED-PARTITION(A,p,r)
 * 	i = RANDOM(p,r)
 * 	exchange A[r] with A[i]
 * 	return PARTITION(A,p,r)
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
*/

#include <iterator>
#include <cstdlib>
#include <ctime>
#include <cstdio>
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

template <typename Itr>
auto Random(Itr p, Itr r) {
	return std::next(p, rand() % std::distance(p,r));
}

template <typename Itr, typename Cmp>
auto RandomizedPartition(Itr p, Itr r, Cmp cmp) {
	auto q = Random(p, r);
	std::iter_swap(q, std::prev(r));
	return Partition(p,r,cmp);
}

template <typename Itr, typename Cmp>
auto KthSelect(Itr p, Itr r, long k, Cmp cmp) {
	if (p == r) return r;
	auto length = std::distance(p,r);
	if (length == 1 || k > length) return p;
	auto q = Partition(p,r,cmp);
	auto i = std::distance(p,q);
	if (k == i) return std::prev(q); /*assume k start from 1*/
	else if (k < i) return KthSelect(p,q,k,cmp);
	else return KthSelect(q,r,k-i,cmp);
}

template <typename Itr>
auto KthSelect(Itr p, Itr r, size_t k) {
	return KthSelect(p,r,k,
            std::less<
            typename std::iterator_traits<Itr>::value_type>());
}

template <typename Itr, typename Cmp>
auto RandomizedKthSelect(Itr p, Itr r, long k, Cmp cmp) {
	if (p == r) return r;
	auto length = std::distance(p,r);
	if (length == 1 || k > length) return p;
	srand(time(NULL)); /*init random generator*/
	auto q = RandomizedPartition(p,r,cmp);
	auto i = std::distance(p,q);
	if (k == i) return std::prev(q); /*assume k start from 1*/
	else if (k < i) return RandomizedKthSelect(p,q,k,cmp);
	else return RandomizedKthSelect(q,r,k-i,cmp);
}

template <typename Itr>
auto RandomizedKthSelect(Itr p, Itr r, size_t k) {
	return RandomizedKthSelect(p,r,k,
			std::less<
            typename std::iterator_traits<Itr>::value_type>());
}

//test
template <typename It>
void printIA(It b, It e) {
	for (;b != e; ++b) fprintf(stderr,"%-4d",*b);
	fprintf(stderr,"\n");
}
#include <vector>
int main() {
	using namespace std;
	int a[] = {4,9,1,14,5,10,11,6,13,2,8,12,3,7};
	auto p = begin(a), r= end(a);
	printIA(p,r);
	puts("normal partition");
	for (int k = 1; k <= distance(p,r); ++k) {
		auto q = KthSelect(p,r,k);
		if (q != end(a))
			printf("%-3d Smallest is %4d\n",k,*q);
	}
	puts("random partition");
	for (int k = 1; k <= distance(p,r); ++k) {
		auto q = RandomizedKthSelect(p,r,k);
		if (q != end(a))
			printf("%-3d Smallest is %4d\n",k,*q);
	}
	std::vector<int> b = {};
	auto q = KthSelect(begin(b),end(b),0);
	if (q == end(b)) printf("True\n");
	return 0;
}
