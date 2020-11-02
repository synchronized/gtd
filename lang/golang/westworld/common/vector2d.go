package common

import "math"

const (
	clockwise     = 1
	anticlockwise = -1
)

const (
	MinDouble = 0.00001
)

var accuracy Accuracy

func init() {
	accuracy = func() float64 { return MinDouble }
}

type Vector2d struct {
	x float64
	y float64
}

func NewVector2d(x, y float64) *Vector2d {
	return &Vector2d{x, y}
}

//x, y 都设置为0
func (v *Vector2d) Zero() {
	v.x = 0.0
	v.y = 0.0
}

//如果x，y都为0返回True
func (v *Vector2d) IsZero() bool {
	return accuracy.Equal(v.x, 0.0) && accuracy.Equal(v.y, 0.0)
}

//返回矢量的长度
func (v *Vector2d) Length() float64 {
	return math.Sqrt(v.LengthSq())
}

func (v *Vector2d) LengthSq() float64 {
	return v.x*v.x + v.y*v.y
}

//矢量归一化
func (v *Vector2d) Normalize() {
	var length = v.Length()
	if accuracy.Greater(length, 0.0) {
		v.x /= length
		v.y /= length
	}
}

//返回矢量的点积
func (v *Vector2d) Dot(v2 *Vector2d) float64 {
	return v.x*v2.x + v.y*v2.y
}

//如果在逆时针方向返回负值(假设y轴的箭头向下,x轴箭头向右)
func (v *Vector2d) Sign(v2 *Vector2d) int {
	//TODO 写反了?
	if v.y*v2.x > v.x*v2.y {
		return anticlockwise
	} else {
		return clockwise
	}
}

//返回与v的正交矢量(垂直，点积为0)
func (v *Vector2d) Perp() *Vector2d {
	return NewVector2d(-v.y, v.x)
}

//调整x,y的值使矢量长度不会超过最大值
func (v *Vector2d) Truncate(max float64) {
	if v.Length() > max {
		v.Normalize()
		v.OpMultiply(max)
	}
}

//返回矢量之间的距离
func (v *Vector2d) Distance(v2 *Vector2d) float64 {
	return math.Sqrt(v.DistanceSq(v2))
}

//距离的平方
func (v *Vector2d) DistanceSq(v2 *Vector2d) float64 {
	var ySeparation = v2.y - v.y
	var xSeparation = v2.x - v.x
	return ySeparation*ySeparation + xSeparation*xSeparation
}

//返回相反的矢量
func (v *Vector2d) Reverse() *Vector2d {
	return NewVector2d(-v.x, -v.y)
}

//操作+
func (v *Vector2d) OpAdd(v2 *Vector2d) *Vector2d {
	var result Vector2d = *v
	result.OpAddAssign(v2)
	return &result
}

//操作-
func (v *Vector2d) OpMinus(v2 *Vector2d) *Vector2d {
	var result Vector2d = *v
	result.OpMinusAssign(v2)
	return &result
}

//操作*
func (v *Vector2d) OpMultiply(v2 float64) *Vector2d {
	var result Vector2d = *v
	result.OpMultiplyAssign(v2)
	return &result
}

//操作/
func (v *Vector2d) OpDivide(v2 float64) *Vector2d {
	var result Vector2d = *v
	result.OpDivideAssign(v2)
	return &result
}

//操作+=
func (v *Vector2d) OpAddAssign(v2 *Vector2d) {
	v.x += v2.x
	v.y += v2.y
}

//操作-=
func (v *Vector2d) OpMinusAssign(v2 *Vector2d) {
	v.x -= v2.x
	v.y -= v2.y
}

//操作*=
func (v *Vector2d) OpMultiplyAssign(v2 float64) {
	v.x *= v2
	v.y *= v2
}

//操作/=
func (v *Vector2d) OpDivideAssign(v2 float64) {
	v.x /= v2
	v.y /= v2
}

//操作==
func (v *Vector2d) OpEqual(v2 *Vector2d) bool {
	return accuracy.Equal(v.x, v2.x) && accuracy.Equal(v.y, v2.y)
}

//操作!=
func (v *Vector2d) OpNotEqual(v2 *Vector2d) bool {
	return !v.OpEqual(v2)
}
