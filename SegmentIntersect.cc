/* Determine if segment p1p2 and p3p4 intersect
 * Define Clockwise and CounterClockwise orientation.
 *
 * sequence p0->p1->p2, vector p0p1, p0p2
 * (p1-p0)×(p2-p0) = (x1-x0)(y2-y0) - (x2-x0)(y1-y0)
 * If this cross product is positive, p0->p1->p2 is
 * counterclockwise, if negative, it is clockwise.
 *
 * The Right-hand rule comes to my mind, so I wrote it down
 *
 * The right-hand rule states that the orientation of the
 * vectors' cross product is determined by placing u and v
 * tail-to-tail, flattening the right hand, extending it in
 * the direction of u, and then curling the fingers in the
 * direction that the angle v makes with u. The thumb then
 * points in the direction of u×v.
 * 
 * SEGMENTS-INTERSECT(p1,p2,p3,p4)
 * 	d1 = DIRECTION(p3,p4,p1)
 * 	d2 = DIRECTION(p3,p4,p2)
 * 	d3 = DIRECTION(p1,p2,p3)
 * 	d4 = DIRECTION(p1,p2,p4)
 * 	if ((d1 > 0 and d2 <0) or (d1 < 0 and d2 > 0)) and
 * 		((d3 > 0 and d4 < 0) or (d3 < 0 and d4 > 0))
 * 		return TRUE
 * 	elseif d1 == 0 and ON-SEGMENT(p3,p4,p1)
 * 		return TRUE
 * 	elseif d2 == 0 and ON-SEGMENT(p3,p4,p2)
 * 		return TRUE
 * 	elseif d3 == 0 and ON-SEGMENT(p1,p2,p3)
 * 		return TRUE
 * 	elseif d4 == 0 and ON-SEGMENT(p1,p2,p4)
 * 		return TRUE
 * 	else
 * 		return FALSE
 *
 * DIRECTION(pi,pj,pk)
 * 	return (pk-pi)×(pj-pi)
 *
 * ON-SEGMENT(pi,pj,pk)
 * 	if (min(xi,xj) <= xk <= max(xi,xj) and
 * 		min(yi,yj) <= yk <= max(yi,yj)
 * 		return TRUE
 * 	else return FALSE
 *
 */

#include <algorithm>

template <typename T>
struct Point {
	using value_type = T;
	T x,y;
	Point(T x0, T y0):x{x0},y{y0}{}
	auto operator-(const Point& p) {
		return Point(x-p.x,y-p.y);
	}
	auto operator*(const Point& p) {
		return x*p.y - p.x*y;
	}
};
template <typename P>
auto Direction(P& pi, P& pj, P& pk) {
	return (pj - pi)*(pk - pi);
}
template <typename P>
auto OnSegment(P& pi, P& pj, P& pk) {
	if (std::min(pi.x,pj.x) <= pk.x &&
		std::max(pi.x,pj.x) >= pk.x &&
		std::min(pi.y,pj.y) <= pk.y &&
		std::max(pi.y,pj.y) >= pk.y)
		return true;
	else return false;
}
template <typename P>
auto SegmentIntersect(P& p1, P& p2, P& p3, P& p4) {
	auto d1 = Direction(p3,p4,p1);
	auto d2 = Direction(p3,p4,p2);
	auto d3 = Direction(p1,p2,p3);
	auto d4 = Direction(p1,p2,p4);
	if (((d1<0&&d2>0)||(d1>0&&d2<0)) && ((d3<0&&d4>0)||(d3>0&&d4<0))) return true;
	else if (d1 == 0 && OnSegment(p3,p4,p1)) return true;
	else if (d2 == 0 && OnSegment(p3,p4,p2)) return true;
	else if (d3 == 0 && OnSegment(p1,p2,p3)) return true;
	else if (d4 == 0 && OnSegment(p1,p2,p4)) return true;
	else return false;
}

/*less coding way*/
template <typename T>
auto SegmentIntersect1D(T p1, T p2, T p3, T p4) {
	if (p1 > p2) std::swap(p1,p2);
	if (p3 > p4) std::swap(p3,p4);
	return std::max(p1,p3) <= std::min(p2,p4);
}
template <typename P>
auto SegmentIntersect2D(P& p1, P& p2, P& p3, P& p4) {
	auto d1 = Direction(p3,p4,p1);
	auto d2 = Direction(p3,p4,p2);
	auto d3 = Direction(p1,p2,p3);
	auto d4 = Direction(p1,p2,p4);
	return SegmentIntersect1D(p1.x,p2.x,p3.x,p3.x) &&
			SegmentIntersect1D(p1.y,p2.y,p3.y,p3.y) &&
			((d1<0&&d2>0)||(d1>0&&d2<0)) &&
		 	((d3<0&&d4>0)||(d3>0&&d4<0));
}

//test
#include <cstdio>
int main() {
	Point<float> p1 = {1, 1}, q1 = {10, 1};
    Point<float> p2 = {1, 2}, q2 = {10, 2};
	printf("%d\n",SegmentIntersect(p1,q1,p2,q2));
	printf("%d\n",SegmentIntersect2D(p1,q1,p2,q2));
    p1 = {10, 0}, q1 = {0, 10};
    p2 = {0, 0}, q2 = {10, 10};
	printf("%d\n",SegmentIntersect(p1,q1,p2,q2));
	printf("%d\n",SegmentIntersect2D(p1,q1,p2,q2));
    p1 = {-5, -5}, q1 = {0, 0};
    p2 = {1, 1}, q2 = {10, 10};
	printf("%d\n",SegmentIntersect(p1,q1,p2,q2));
	printf("%d\n",SegmentIntersect2D(p1,q1,p2,q2));
}
