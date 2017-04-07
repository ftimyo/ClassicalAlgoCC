/*
 * Problem:
 * The convex hull of a set Q of points, denoted by CH(Q),
 * is the smallest convex polygon P for which each point in
 * Q is either on the boundary of P or in its interior. We
 * assume that all points in the set Q are unique and that Q
 * contains at least three points.
 *
 * GRAHAM-SCAN(Q)
 * 	let p0 be the point in Q with the minimum y-coordinate,
 * 		or the leftmost such point in case of a tie
 * 	let <p1,p2,...pm> be the remaining points in Q,
 * 		sorted by polar angle in counterclockwise order
 * 		around p0 (if more than one point has the same
 * 		angle, remove all but the one that is farthest from
 * 		p0)
 * 	let S be an empty stack
 * 	PUSH(p0,S)
 * 	PUSH(p1,S)
 * 	PUSH(p2,S)
 * 	for i = 3 to m
 * 		while the angle formed by points NEXT-TO-TOP(S),
 * 				TOP(S), and pi makes a nonleft turn
 * 			POP(S)
 * 		PUSH(pi,S)
 * 	return S
 *
 *  Time complexity 𝚶(n lg n)
 *
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
void ConvexHullGrahamScan(P (&V)[N]){
	using T = decltype(std::begin(V));
	T SV[N] /*sorted V*/, S[N] /*stack*/;
	auto pb = std::begin(V);
	for (auto& p : SV) p = pb++;

	auto p0 = std::min_element(std::begin(SV),std::end(SV),[](auto& p1, auto& p2){
			return p1->y < p2->y || (p1->y == p2->y && p1->x < p2->x);
			});
	std::iter_swap(std::begin(SV), p0);

	p0 = std::begin(SV);
	std::sort(std::next(std::begin(SV)), std::end(SV),[&p0](auto& p1, auto p2){
			auto cp = (*p0)->PolarAngle(*p1,*p2);
			return cp > 0 || (cp == 0 && ((*p0)->dist(*p1) < (*p0)->dist(*p2)));
			});

	auto top = size_t{0};
	for (auto p : SV) {
		while (top > 2 && S[top-2]->PolarAngle(*S[top-1],*p) <= 0) --top;
		S[top++] = p;
	}

#ifdef DEBUG
	for (decltype(top) i = 0; i < top; ++i) {
		std::cout<<"("<<S[i]->x<<","<<S[i]->y<<")\n";
	}
#endif
}

int main() {
	Point<float> p[] = {
		{0, 3}, {1, 1}, {2, 2}, {4, 4},
		{0, 0}, {1, 2}, {3, 1}, {3, 3}};
	ConvexHullGrahamScan(p);
	puts("");
	Point<int> p1[] = {
		{0, 3}, {1, 1}, {2, 2}, {4, 4},
		{0, 0}, {1, 2}, {3, 1}, {3, 3}};
	ConvexHullGrahamScan(p1);
	return 0;
}
