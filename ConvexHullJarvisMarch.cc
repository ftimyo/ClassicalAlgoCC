/*
 * Problem:
 * The convex hull of a set Q of points, denoted by CH(Q),
 * is the smallest convex polygon P for which each point in
 * Q is either on the boundary of P or in its interior. We
 * assume that all points in the set Q are unique and that Q
 * contains at least three points.
 *
 * The idea of Jarvis’s Algorithm is simple, we start from
 * the leftmost point (or point with minimum x coordinate
 * value) and we keep wrapping points in counterclockwise
 * direction.
 * Next point is selected as the point that beats all other
 * points at counterclockwise orientation.
 *
 * Time complexity 𝚶(nh), where h is the number of vertices
 * of the convex hull.
 */
#include <algorithm>
#include <iterator>
#include <cmath>
#include <iostream>
#define DEBUG
template <typename T>
struct Point {
	T x,y;
	Point(T x0, T y0):x{x0},y{y0}{}
	template <typename P>
	auto operator-(P&& p) {
		return Point(x-p.x,y-p.y);
	}
	template <typename P>
	auto operator*(P&& p) {
		return x*p.y - p.x*y;
	}
	template <typename P>
	auto PolarAngle(P&& p1, P&& p2) {
		return (p1-*this)*(p2-*this);
	}
	template <typename P>
	auto dist(P&& p) {
		auto tmp = p-*this;
		return std::sqrt(std::pow(tmp.x,2)+std::pow(tmp.y,2));
	}
};
template <typename P, int N>
void ConvexHullJarvisMarch(P (&V)[N]){
	auto p0 = std::min_element(std::begin(V),std::end(V),[](auto& p1, auto& p2){
			return p1.y < p2.y || (p1.y == p2.y && p1.x < p2.x);
			});

	decltype(p0) HV[N] /*Hull vertex*/;

	auto p = p0;
	auto n = size_t{0};
	do {
		HV[n++] = p;
		p = std::min_element(std::begin(V),std::end(V),[p](auto& p1, auto& p2){
				auto cp = p->PolarAngle(p1,p2);
				return cp > 0 || (cp == 0 && (p->dist(p1) > p->dist(p2)));
				});
	} while (p != p0);
#ifdef DEBUG
	for (decltype(n) i = 0; i < n; ++i) {
		std::cout<<"("<<HV[i]->x<<","<<HV[i]->y<<")\n";
	}
#endif
}

//test
int main() {
	Point<float> p[] = {
		{0, 3}, {1, 1}, {2, 2}, {4, 4},
		{0, 0}, {1, 2}, {3, 1}, {3, 3}};
	ConvexHullJarvisMarch(p);
	puts("");
	Point<int> p1[] = {
		{0, 3}, {1, 1}, {2, 2}, {4, 4},
		{0, 0}, {1, 2}, {3, 1}, {3, 3}};
	ConvexHullJarvisMarch(p1);
	puts("");
	Point<int> p3[] = {
		{0, 3}, {2, 2}, {1, 1}, {2, 1},
		{3, 0}, {0, 0}, {3, 3}};
	ConvexHullJarvisMarch(p3);
	return 0;
}
