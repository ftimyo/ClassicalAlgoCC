/*
 * GCD recursion theorem
 * for any nonnegative integer a and any positive integer b,
 * gcd(a,b) = gcd(b,a mod b)
 *
 * Euclid's algorithm
 * EUCLID(a,b)
 * 	if b == 0
 * 		return a
 * 	else return EUCLID(b,a mod b)
 *
 * The extended form of Euclid's algorithm
 * d = gcd(a,b) = ax + by, where x,y may be zero or negative
 *
 * EXTENDED-EUCLID(a,b)
 * 	if b == 0
 * 		return (a,1,0)
 * 	else
 * 		(d1,x1,y1) = EXTENDED-EUCLID(b,a mod b)
 * 		(d,x,y) = (d1,y1,x1 - ⎣ a/b⎦ y1)
 * 		return (d,x,y)
 */

#include <type_traits>
#include <cstdio>

template <typename N,
    typename = std::enable_if_t<std::is_integral<N>::value>>
auto EuclidGCD(N a, N b) {
	if (a < b) std::swap(a,b);
	if (b == 0) return a;
	else return EuclidGCD(b, a%b);
}
/*nonrecursion version*/
template <typename N,
    typename = std::enable_if_t<std::is_integral<N>::value>>
auto EuclidGCDNR(N a, N b) {
	if (a < b) std::swap(a,b);
	while (b!=0) {
		auto t = a % b;
		a = b; b = t;
	}
	return a;
}
//test
int main() {
	int a = 120, b = 96;
	printf("gcd(%d,%d) = %d\n",a,b,EuclidGCD(a,b));
	printf("gcdnr(%d,%d) = %d\n",a,b,EuclidGCDNR(a,b));
}
