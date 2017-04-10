/*
 * FIND-MAX-CROSSING-SUBARRAY(A,low,mid,high)
 * 	left-sum = -∞
 * 	sum = 0
 * 	for i = mid downto low
 * 		sum = sum + A[i]
 * 		if sum > left-sum
 * 			left-sum = sum
 * 			max-left = i
 * 	right-sum = -∞
 * 	sum = 0
 * 	for j = mid + 1 to high
 * 		sum = sum + A[j]
 * 		if sum > right-sum
 * 			right-sum = sum
 * 			max-right = j
 * 	return (max-left, max-right, left-sum + right-sum)
 *
 * 	FIND-MAXIMUM-SUBARRAY(A,low,high)
 * 		if high = low
 * 			return (low,high,A[low])//base case: only one element
 * 		else mid = ⎣ (low + high) / 2⎦
 * 			(left-low,left-high,left-sum) =
 * 				FIND-MAXIMUM-SUBARRAY(A,low,mid)
 * 			(right-low,right-high,right-sum) =
 * 				FIND-MAXIMUM-SUBARRAY(A,mid+1,right)
 * 			(cross-low,cross-high,cross-sum) =
 * 				FIND-MAX-CROSSING-SUBARRAY(A,low,mid,high)
 * 			if left-sum ≥ right-sum and left-sum ≥ cross-sum
 * 				return (left-low,left-high,left-sum)
 * 			elseif right-sum ≥ left-sum and right-sum ≥ cross-sum
 * 				return (right-low,right-high,right-sum)
 * 			else return (cross-low,cross-high,cross-sum)
 */

#include <iterator>
#include <limits>
template <typename Itr>
auto FindMaxCrossingSubarray(Itr p, Itr q, Itr r,
                             Itr& maxl, Itr& maxr) {
	using T = typename std::iterator_traits<Itr>::value_type;
	auto lsum = std::numeric_limits<T>::min();
	T sum = 0;
	maxl = std::prev(q);
	for (auto i = maxl; i >= p; --i) {
		sum += *i;
		if (sum > lsum) {
			lsum = sum;
			maxl = i;
		}
	}
	auto rsum = std::numeric_limits<T>::min();
	sum = 0;
	maxr = q;
	for (auto i = maxr; i < r; ++i) {
		sum += *i;
		if (sum > rsum) {
			rsum = sum;
			maxr = i;
		}
	}
	++maxr;
	return lsum + rsum;
}

template <typename Itr>
auto FindMaximumSubarray(Itr p, Itr r, Itr& subl, Itr& subr) {
	subl = p; subr = r;
	if (p == r) return 0;
	auto diff = std::distance(p,r);
	if (diff < 2) return *p;
	auto q = std::next(p,diff / 2);
	Itr llow, lhigh, rlow, rhigh, clow, chigh;
	auto lsum = FindMaximumSubarray(p,q,llow,lhigh);
	auto rsum = FindMaximumSubarray(q,r,rlow,rhigh);
	auto csum = FindMaxCrossingSubarray(p,q,r,clow,chigh);
	if (lsum > rsum && lsum > csum) {
		subl = llow; subr = lhigh;
		return lsum;
	} else if (rsum > lsum && rsum > csum) {
		subl = rlow; subr = rhigh;
		return rsum;
	} else {
		subl = clow; subr = chigh;
		return csum;
	}
}

//test
using namespace std;
#include <vector>
int main () {
	int a[]={13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
	for (auto x : a) printf("%-4d",x);
	puts("");
	decltype(begin(a)) l, r;
	auto s = FindMaximumSubarray(begin(a),end(a),l,r);
	printf("MaxSum: %4d\n",s);
	for (auto i = l; i < r; ++i) {
		printf("%-4d",*i);
	}
	puts("");
	std::vector<int> b = {};
	decltype(begin(b)) lb,rb;
	s = FindMaximumSubarray(begin(b),end(b),lb,rb);
	for (auto x : b) printf("%-4d",x);
	puts("");
	printf("MaxSum: %4d\n",s);
	for (auto i = lb; i < rb; ++i) {
		printf("%-4d",*i);
	}
	puts("");
}
