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
	X float64
	Y float64
}

func NewVector2d(X, Y float64) *Vector2d {
	return &Vector2d{X, Y}
}

//X, Y 都设置为0
func (v *Vector2d) Zero() {
	v.X = 0.0
	v.Y = 0.0
}

//如果X，Y都为0返回True
func (v *Vector2d) IsZero() bool {
	return accuracy.Equal(v.X, 0.0) && accuracy.Equal(v.Y, 0.0)
}

//返回矢量的长度
func (v *Vector2d) Length() float64 {
	return math.Sqrt(v.LengthSq())
}

func (v *Vector2d) LengthSq() float64 {
	return v.X*v.X + v.Y*v.Y
}

//矢量归一化
func (v *Vector2d) Normalize() *Vecotr2d {
	var result = *v
	result.NormalizeAssign()
	return &result
}

//矢量归一化并赋值
func (v *Vector2d) NormalizeAssign() {
	var length = v.Length()
	if accuracy.Greater(length, 0.0) {
		v.X /= length
		v.Y /= length
	}
}

//返回矢量的点积
func (v *Vector2d) Dot(v2 *Vector2d) float64 {
	return v.X*v2.X + v.Y*v2.Y
}

//如果在逆时针方向返回负值(假设Y轴的箭头向下,X轴箭头向右)
func (v *Vector2d) Sign(v2 *Vector2d) int {
	//TODO 写反了?
	if v.Y*v2.X > v.X*v2.Y {
		return anticlockwise
	} else {
		return clockwise
	}
}

//返回与v的正交矢量(垂直，点积为0)
func (v *Vector2d) Perp() *Vector2d {
	return NewVector2d(-v.Y, v.X)
}

//调整X,Y的值使矢量长度不会超过最大值
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
	var ySeparation = v2.Y - v.Y
	var xSeparation = v2.X - v.X
	return ySeparation*ySeparation + xSeparation*xSeparation
}

//返回相反的矢量
func (v *Vector2d) Reverse() *Vector2d {
	return NewVector2d(-v.X, -v.Y)
}

//反射
func (v *Vector2d) Reflect(normalize *Vector2d) *Vector2d {
	var result = *v
	result.ReflectAssign(normalize)
	return &result
}

func (v *Vector2d) ReflectAssign(normalize *Vector2d) *Vector2d {
	//- normalize * v dot normalize * 2
	return v.OpAddAssign(normalize.Reverse().OpMultiplyAssign(v.Dot(normalize)).OpMultiplyAssign(2))
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
func (v *Vector2d) OpAddAssign(v2 *Vector2d) *Vector2d {
	v.X += v2.X
	v.Y += v2.Y
	return v
}

//操作-=
func (v *Vector2d) OpMinusAssign(v2 *Vector2d) *Vector2d {
	v.X -= v2.X
	v.Y -= v2.Y
	return v
}

//操作*=
func (v *Vector2d) OpMultiplyAssign(v2 float64) *Vector2d {
	v.X *= v2
	v.Y *= v2
	return v
}

//操作/=
func (v *Vector2d) OpDivideAssign(v2 float64) *Vector2d {
	v.X /= v2
	v.Y /= v2
	return v
}

//操作==
func (v *Vector2d) OpEqual(v2 *Vector2d) bool {
	return accuracy.Equal(v.X, v2.X) && accuracy.Equal(v.Y, v2.Y)
}

//操作!=
func (v *Vector2d) OpNotEqual(v2 *Vector2d) bool {
	return !v.OpEqual(v2)
}

func (v *Vector2d) Accuracy() Accuracy {
	return accuracy
}

func (v *Vector2d) AccuracyVal() float64 {
	return accuracy()
}

func (v *Vector2d) X() float64 {
	return v.X
}

func (v *Vector2d) Y() float64 {
	return v.Y
}
