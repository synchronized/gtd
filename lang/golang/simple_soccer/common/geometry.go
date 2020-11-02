package common

import "math"

const pi float64 = 3.14159

//给定一个平面和一条射线，这个函数返回沿射线的距离。如果射线平行，则返回负数
func DistanceToRayPlaneIntersection(
	RayOrigin,
	RayHeading,
	PlanePoint, //any point on the plane
	PlaneNormal Vector2d) float64 {

	var d float64 = -PlaneNormal.Dot(&PlanePoint)
	var numer float64 = PlaneNormal.Dot(&RayOrigin) + d
	var denom float64 = PlaneNormal.Dot(&RayHeading)

	// normal is parallel to vector
	if (denom < 0.000001) && (denom > -0.000001) {
		return (-1.0)
	}

	return -(numer / denom)
}

//------------------------- WhereIsPoint --------------------------------------
type Plane_Span_Type int

const (
	Plane_backside Plane_Span_Type = 1 //背面
	Plane_front    Plane_Span_Type = 2 //前面
	On_plane       Plane_Span_Type = 3 //在平面上
)

/**
 * 点和平面的位置关系
 * @param point 目标点
 * @param PointOnPlane any point on the plane
 * @param PlaneNormal 平面的法向量(???)
 */
func WhereIsPoint(point, PointOnPlane, PlaneNormal Vector2d) Plane_Span_Type {
	var dir Vector2d = *PointOnPlane.OpMinus(&point)
	var d float64 = dir.Dot(&PlaneNormal)

	//TODO 精度
	if d < -0.000001 {
		return Plane_front
	} else if d > 0.000001 {
		return Plane_backside
	}

	return On_plane
}

//-------------------------- GetRayCircleIntersec -----------------------------
/*
 * 射线和圆相交
 * @param RayOrigin 射线原点
 * @param RayHeading 射线方向(归一化)
 * @param CircleOrigin 圆心的坐标
 * @param radius float64 圆的半径
 * @return 最近的交点的距离
 */
func GetRayCircleIntersect(RayOrigin, RayHeading, CircleOrigin Vector2d, radius float64) float64 {

	var ToCircle Vector2d = *CircleOrigin.OpMinus(&RayOrigin)
	var length float64 = ToCircle.Length()
	var v float64 = ToCircle.Dot(&RayHeading)
	var d float64 = radius*radius - (length*length - v*v)

	// If there was no intersection, return -1
	if d < 0.0 {
		return (-1.0)
	}

	// Return the distance to the [first] intersecting point
	return (v - math.Sqrt(d))
}

//----------------------------- DoRayCircleIntersect --------------------------
/*
 * 判断射线和圆相交
 * @param RayOrigin 射线原点
 * @param RayHeading 射线方向(归一化)
 * @param CircleOrigin 圆心的坐标
 * @param radius float64 圆的半径
 * @return 是否相交
 */
func DoRayCircleIntersect(RayOrigin, RayHeading, CircleOrigin Vector2d, radius float64) bool {

	var ToCircle Vector2d = *CircleOrigin.OpMinus(&RayOrigin)
	var length float64 = ToCircle.Length()
	var v float64 = ToCircle.Dot(&RayHeading)
	var d float64 = radius*radius - (length*length - v*v)

	// If there was no intersection, return -1
	return (d < 0.0)
}

//------------------------------------------------------------------------
//  Given a point P and a circle of radius R centered at C this function
//  determines the two points on the circle that intersect with the
//  tangents from P to the circle. Returns false if P is within the circle.
//
//  thanks to Dave Eberly for this one.
//------------------------------------------------------------------------
/*
 * 给定一个点p和一个以c为中心的半径r的圆，
 * 此函数确定圆上与从p到圆的两条切线与员的两个切点。如果p在圆内，则返回false。
 * @param C 圆心
 * @param R 半径
 * @param P 点
 * @return ok 是否相交
 * @return T1 第一个焦点
 * @return T2 第二个焦点
 */
func GetTangentPoints(C Vector2d, R float64, P Vector2d) (ok bool, T1, T2 Vector2d) {
	var PmC Vector2d = *P.OpMinus(&C)
	var SqrLen float64 = PmC.LengthSq()
	var RSqr float64 = R * R
	if SqrLen <= RSqr {
		// P is inside or on the circle
		//p 点在圆内
		return
	}

	var InvSqrLen float64 = 1 / SqrLen
	var Root float64 = math.Sqrt(math.Abs(SqrLen - RSqr))

	T1.X = C.X + R*(R*PmC.X-PmC.Y*Root)*InvSqrLen
	T1.Y = C.Y + R*(R*PmC.Y+PmC.X*Root)*InvSqrLen
	T2.X = C.X + R*(R*PmC.X+PmC.Y*Root)*InvSqrLen
	T2.Y = C.Y + R*(R*PmC.Y-PmC.X*Root)*InvSqrLen

	ok = true
	return
}

//------------------------- DistToLineSegment ----------------------------
//
//  given a line segment AB and a point P, this function calculates the
//  perpendicular distance between them
//------------------------------------------------------------------------
//点到线段的距离(垂直距离)
func DistToLineSegment(A, B, P Vector2d) float64 {
	//if the angle is obtuse between PA and AB is obtuse then the closest
	//vertex must be A
	//如果PA和AB之间的角度是钝角，则最近的顶点必须是A
	var dotA float64 = (P.X-A.X)*(B.X-A.X) + (P.Y-A.Y)*(B.Y-A.Y)

	if dotA <= 0 {
		return A.Distance(&P)
	}

	//if the angle is obtuse between PB and AB is obtuse then the closest
	//vertex must be B
	var dotB float64 = (P.X-B.X)*(A.X-B.X) + (P.Y-B.Y)*(A.Y-B.Y)

	if dotB <= 0 {
		return B.Distance(&P)
	}

	//calculate the point along AB that is the closest to P
	var Point Vector2d = *A.OpAdd(B.OpMinus(&A).OpMultiply(dotA).OpDivide(dotA + dotB))

	//calculate the distance P-Point
	return P.Distance(&Point)
}

//------------------------- DistToLineSegmentSq ----------------------------
//
//  as above, but avoiding sqrt
//------------------------------------------------------------------------
//同上,不开方
func DistToLineSegmentSq(A, B, P Vector2d) float64 {
	//if the angle is obtuse between PA and AB is obtuse then the closest
	//vertex must be A
	var dotA float64 = (P.X-A.X)*(B.X-A.X) + (P.Y-A.Y)*(B.Y-A.Y)

	if dotA <= 0 {
		return A.DistanceSq(&P)
	}

	//if the angle is obtuse between PB and AB is obtuse then the closest
	//vertex must be B
	var dotB float64 = (P.X-B.X)*(A.X-B.X) + (P.Y-B.Y)*(A.Y-B.Y)

	if dotB <= 0 {
		return B.DistanceSq(&P)
	}

	//calculate the point along AB that is the closest to P
	var Point *Vector2d = A.OpAdd(B.OpMinus(&A).OpMultiply(dotA).OpDivide(dotA + dotB))

	//calculate the distance P-Point
	return P.DistanceSq(Point)
}

//--------------------LineIntersection2D-------------------------
//
//	Given 2 lines in 2D space AB, CD this returns true if an
//	intersection occurs.
//
//-----------------------------------------------------------------
//给定2d空间ab，cd中的两条线，如果相交，则返回true
func LineIntersection2D(A, B, C, D Vector2d) bool {
	var rTop float64 = (A.Y-C.Y)*(D.X-C.X) - (A.X-C.X)*(D.Y-C.Y)
	var sTop float64 = (A.Y-C.Y)*(B.X-A.X) - (A.X-C.X)*(B.Y-A.Y)

	var Bot float64 = (B.X-A.X)*(D.Y-C.Y) - (B.Y-A.Y)*(D.X-C.X)

	//平行
	if Bot == 0 {
		return false
	}

	var invBot float64 = 1.0 / Bot
	var r float64 = rTop * invBot
	var s float64 = sTop * invBot

	if (r > 0) && (r < 1) && (s > 0) && (s < 1) {
		//lines intersect
		return true
	}

	//lines do not intersect
	return false
}

//--------------------LineIntersection2D-------------------------
//
//	Given 2 lines in 2D space AB, CD this returns true if an
//	intersection occurs and sets dist to the distance the intersection
//  occurs along AB
//
//-----------------------------------------------------------------
//将dist设置为交叉点沿ab发生的距离
func LineIntersection2D1(A, B, C, D Vector2d) (intersection bool, dist float64) {

	var rTop float64 = (A.Y-C.Y)*(D.X-C.X) - (A.X-C.X)*(D.Y-C.Y)
	var sTop float64 = (A.Y-C.Y)*(B.X-A.X) - (A.X-C.X)*(B.Y-A.Y)
	var Bot float64 = (B.X-A.X)*(D.Y-C.Y) - (B.Y-A.Y)*(D.X-C.X)

	//平行
	if Bot == 0 {
		if FloatEqual(rTop, 0) && FloatEqual(sTop, 0) {
			return true, 0
		}
		return false, 0
	}

	var r float64 = rTop / Bot
	var s float64 = sTop / Bot

	if (r > 0) && (r < 1) && (s > 0) && (s < 1) {
		dist = A.Distance(&B) * r
		return true, dist
	} else {
		return false, 0
	}
}

//-------------------- LineIntersection2D-------------------------
//
//	Given 2 lines in 2D space AB, CD this returns true if an
//	intersection occurs and sets dist to the distance the intersection
//  occurs along AB. Also sets the 2d vector point to the point of
//  intersection
//-----------------------------------------------------------------
func LineIntersection2D2(A, B, C, D Vector2d) (intersection bool, dist float64, point Vector2d) {

	var rTop float64 = (A.Y-C.Y)*(D.X-C.X) - (A.X-C.X)*(D.Y-C.Y)
	var rBot float64 = (B.X-A.X)*(D.Y-C.Y) - (B.Y-A.Y)*(D.X-C.X)

	var sTop float64 = (A.Y-C.Y)*(B.X-A.X) - (A.X-C.X)*(B.Y-A.Y)
	var sBot float64 = (B.X-A.X)*(D.Y-C.Y) - (B.Y-A.Y)*(D.X-C.X)

	//lines are parallel
	if (rBot == 0) || (sBot == 0) {
		return
	}

	var r float64 = rTop / rBot
	var s float64 = sTop / sBot

	if (r > 0) && (r < 1) && (s > 0) && (s < 1) {
		intersection = true
		dist = A.Distance(&B) * r
		point = *A.OpAdd(B.OpMinus(&A).OpMultiply(r))
		intersection = true
		return
	} else {
		return
	}
}

//----------------------- ObjectIntersection2D ---------------------------
//
//  tests two polygons for intersection. *Does not check for enclosure*
//------------------------------------------------------------------------
//多边形碰撞判断*不检查是否包含*
func ObjectIntersection2D(object1, object2 []Vector2d) bool {
	//test each line segment of object1 against each segment of object2
	for r := 0; r < len(object1)-1; r++ {
		for t := 0; t < len(object2)-1; t++ {
			if LineIntersection2D(object2[t], object2[t+1], object1[r], object1[r+1]) {
				return true
			}
		}
	}

	return false
}

//----------------------- SegmentObjectIntersection2D --------------------
//
//  tests a line segment against a polygon for intersection
//  *Does not check for enclosure*
//------------------------------------------------------------------------
//对多边形测试线段是否相交*不检查是否包含*
func SegmentObjectIntersection2D(A, B Vector2d, object []Vector2d) bool {
	//test AB against each segment of object
	for r := 0; r < len(object)-1; r++ {
		if LineIntersection2D(A, B, object[r], object[r+1]) {
			return true
		}
	}

	return false
}

//----------------------------- TwoCirclesOverlapped ---------------------
//
//  Returns true if the two circles overlap
//------------------------------------------------------------------------
//判断员是否重叠
func TwoCirclesOverlapped(x1, y1, r1, x2, y2, r2 float64) bool {
	var DistBetweenCenters float64 = math.Sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2))

	if (DistBetweenCenters < (r1 + r2)) || (DistBetweenCenters < math.Abs(r1-r2)) {
		return true
	}

	return false
}

//----------------------------- TwoCirclesOverlapped ---------------------
//
//  Returns true if the two circles overlap
//------------------------------------------------------------------------
func TwoCirclesOverlapped2(c1 Vector2d, r1 float64, c2 Vector2d, r2 float64) bool {
	var DistBetweenCenters float64 = math.Sqrt((c1.X-c2.X)*(c1.X-c2.X) + (c1.Y-c2.Y)*(c1.Y-c2.Y))

	if (DistBetweenCenters < (r1 + r2)) || (DistBetweenCenters < math.Abs(r1-r2)) {
		return true
	}

	return false
}

//--------------------------- TwoCirclesEnclosed ---------------------------
//
//  returns true if one circle encloses the other
//-------------------------------------------------------------------------
//判断员是否是包含另一个
func TwoCirclesEnclosed(x1, y1, r1, x2, y2, r2 float64) bool {
	var DistBetweenCenters float64 = math.Sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2))

	if DistBetweenCenters < math.Abs(r1-r2) {
		return true
	}

	return false
}

//------------------------ TwoCirclesIntersectionPoints ------------------
//
//  Given two circles this function calculates the intersection points
//  of any overlap.
//
//  returns false if no overlap found
//
// see http://astronomy.swin.edu.au/~pbourke/geometry/2circle/
//------------------------------------------------------------------------
//
//求员的交点
func TwoCirclesIntersectionPoints(x1, y1, r1, x2, y2, r2 float64) (intersection bool, p3X, p3Y, p4X, p4Y float64) {
	//first check to see if they overlap
	if !TwoCirclesOverlapped(x1, y1, r1, x2, y2, r2) {
		return false, 0, 0, 0, 0
	}

	//calculate the distance between the circle centers
	var d float64 = math.Sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2))

	//Now calculate the distance from the center of each circle to the center
	//of the line which connects the intersection points.
	//现在计算从每个圆的中心到连接交点的线的中心的距离。
	var a float64 = (r1 - r2 + (d * d)) / (2 * d)
	// var b float64 = (r2 - r1 + (d * d)) / (2 * d)

	//MAYBE A TEST FOR EXACT OVERLAP?

	//calculate the point P2 which is the center of the line which
	//connects the intersection points
	var p2X, p2Y float64

	p2X = x1 + a*(x2-x1)/d
	p2Y = y1 + a*(y2-y1)/d

	//calculate first point
	var h1 float64 = math.Sqrt((r1 * r1) - (a * a))

	p3X = p2X - h1*(y2-y1)/d
	p3Y = p2Y + h1*(x2-x1)/d

	//calculate second point
	var h2 float64 = math.Sqrt((r2 * r2) - (a * a))

	p4X = p2X + h2*(y2-y1)/d
	p4Y = p2Y - h2*(x2-x1)/d

	return true, p3X, p3Y, p4X, p4Y
}

//------------------------ TwoCirclesIntersectionArea --------------------
//
//  Tests to see if two circles overlap and if so calculates the area
//  defined by the union
//
// see http://mathforum.org/library/drmath/view/54785.html
//-----------------------------------------------------------------------
//求员相交的区域
func TwoCirclesIntersectionArea(x1, y1, r1, x2, y2, r2 float64) float64 {
	//first calculate the intersection points
	var intersection, _, _, _, _ = TwoCirclesIntersectionPoints(x1, y1, r1, x2, y2, r2)

	if !intersection {
		return 0.0 //no overlap
	}

	//calculate the distance between the circle centers
	var d float64 = math.Sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2))

	//find the angles given that A and B are the two circle centers
	//and C and D are the intersection points
	var CBD float64 = 2 * math.Acos((r2*r2+d*d-r1*r1)/(r2*d*2))

	var CAD float64 = 2 * math.Acos((r1*r1+d*d-r2*r2)/(r1*d*2))

	//Then we find the segment of each of the circles cut off by the
	//chord CD, by taking the area of the sector of the circle BCD and
	//subtracting the area of triangle BCD. Similarly we find the area
	//of the sector ACD and subtract the area of triangle ACD.

	var area float64 = 0.5*CBD*r2*r2 -
		0.5*r2*r2*math.Sin(CBD) +
		0.5*CAD*r1*r1 -
		0.5*r1*r1*math.Sin(CAD)

	return area
}

//-------------------------------- CircleArea ---------------------------
//
//  given the radius, calculates the area of a circle
//-----------------------------------------------------------------------
//圆的面积
func CircleArea(radius float64) float64 {
	return pi * radius * radius
}

//----------------------- PointInCircle ----------------------------------
//
//  returns true if the point p is within the radius of the given circle
//------------------------------------------------------------------------
//判断点是否 在圆里面
func PointInCircle(Pos Vector2d, radius float64, p Vector2d) bool {
	var DistFromCenterSquared float64 = p.OpMinus(&Pos).LengthSq()

	if DistFromCenterSquared < (radius * radius) {
		return true
	}

	return false
}

//--------------------- LineSegmentCircleIntersection ---------------------------
//
//  returns true if the line segemnt AB intersects with a circle at
//  position P with radius radius
//------------------------------------------------------------------------
//判断线段和员相交
func LineSegmentCircleIntersection(A, B Vector2d, P Vector2d, radius float64) bool {
	//first determine the distance from the center of the circle to
	//the line segment (working in distance squared space)
	var DistToLineSq float64 = DistToLineSegmentSq(A, B, P)

	if DistToLineSq < radius*radius {
		return true
	} else {
		return false
	}
}

//------------------- GetLineSegmentCircleClosestIntersectionPoint ------------
//
//  given a line segment AB and a circle position and radius, this function
//  determines if there is an intersection and stores the position of the
//  closest intersection in the reference IntersectionPoint
//
//  returns false if no intersection point is found
//-----------------------------------------------------------------------------
// 给定线段AB和圆的位置和半径，
// 此函数用于确定是否存在交点，和最近交点的位置
// 如果未找到交点，则返回false
func GetLineSegmentCircleClosestIntersectionPoint(
	A, B, pos Vector2d, radius float64) (ipFound bool, intersectionPoint Vector2d) {
	var toBNorm Vector2d = *B.OpMinus(&A).Normalize()

	//move the circle into the local space defined by the vector B-A with origin
	//at A
	var LocalPos Vector2d = PointToLocalSpace(pos, toBNorm, *toBNorm.Perp(), A)

	//if the local position + the radius is negative then the circle lays behind
	//point A so there is no intersection possible. If the local x pos minus the
	//radius is greater than length A-B then the circle cannot intersect the
	//line segment
	if (LocalPos.X+radius >= 0) &&
		((LocalPos.X-radius)*(LocalPos.X-radius) <= B.DistanceSq(&A)) {

		//if the distance from the x axis to the object's position is less
		//than its radius then there is a potential intersection.
		if math.Abs(LocalPos.Y) < radius {
			//now to do a line/circle intersection test. The center of the
			//circle is represented by A, B. The intersection points are
			//given by the formulae x = A +/-sqrt(r^2-B^2), y=0. We only
			//need to look at the smallest positive value of x.
			var a float64 = LocalPos.X
			var b float64 = LocalPos.Y

			var ip float64 = a - math.Sqrt(radius*radius-b*b)

			if ip <= 0 {
				ip = a + math.Sqrt(radius*radius-b*b)
			}

			ipFound = true

			intersectionPoint = *A.OpAdd(&toBNorm).OpMultiply(ip)
		}
	}

	return ipFound, intersectionPoint
}
