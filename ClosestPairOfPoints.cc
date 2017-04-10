/*
 * Problem:
 * Finding the closest pair of points in a set Q of n >= 2
 * points. "Closet" refers to the usual euclidean distance.
 *
 * Divide-and-Conquer algorithm run time 𝚶 (n lg n)
 *
 */
#include <iterator>
#include <limits>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
#include <type_traits>
#include <cstdio>
constexpr auto INF = std::numeric_limits<double>::max();
template <typename T>
struct Point {
	T x,y;
	Point(T x0, T y0):x{x0},y{y0}{}
	auto dist(Point& p) {
		auto tmp = Point{p.x-this->x,p.y-this->y};
		return std::sqrt(tmp.x*tmp.x+tmp.y*tmp.y);
	}
};
template <typename It, typename T =
			typename std::iterator_traits<It>::value_type>
auto ClosestPair(It l, It h) {
	auto r = std::distance(l,h);
	auto d = INF;
	if(r <= 3) {
		for (auto i = l; i < std::prev(h); ++i) {
			for (auto j = std::next(i); j < h;++j) {
				d = std::min(d,(*i)->dist(**j));
			}
		}
		return d;
	}
	auto m = std::next(l,r/2);
	d = std::min(ClosestPair(l,m),ClosestPair(m,h));
	std::vector<T> t;
	for (auto i = std::prev(m);
			i >= l && (**m).x-(**i).x < d; --i) {
		t.push_back(*i);
	}
	for (auto i = m; i < h && (**i).x-(**m).x < d; ++i) {
		t.push_back(*i);
	}

	std::sort(std::begin(t), std::end(t),[](auto& p1, auto& p2){
			return p1->y < p2->y;
			});
	for (auto i = std::begin(t); i < std::prev(std::end(t));++i){
		for (auto j = std::next(i);
				j < std::end(t) && (**j).y-(**i).y<d; ++j) {
			d = std::min(d,(*i)->dist(**j));
		}
	}
	return d;
}
template <typename P, int N>
void ClosestPairOfPoints(P (&V)[N]) {
	auto p0 = std::begin(V);
	using It = decltype(p0);
	It SV[N];
	for (auto& p : SV) p = p0++;
	std::sort(std::begin(SV), std::end(SV),[](auto& p1,auto& p2){
			return p1->x < p2->x;
			});
	auto d = ClosestPair(std::begin(SV), std::end(SV));
	std::cout << "dist = "<<d<<std::endl;
}
//test
int main() {
	Point<int> P[] = {{2,3},{12,30},{40,50},{5,1},{12,10},{3,4}};
	ClosestPairOfPoints(P);
	return 0;
}
