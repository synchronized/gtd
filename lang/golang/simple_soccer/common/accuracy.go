package common

import "math"

type Accuracy func() float64

const (
	MinDouble = 0.00001
)

var DefaultAccuracy Accuracy

func init() {
	DefaultAccuracy = func() float64 { return MinDouble }
}

func FloatEqual(a, b float64) bool {
	return DefaultAccuracy.Equal(a, b)
}

func FloatGreater(a, b float64) bool {
	return DefaultAccuracy.Greater(a, b)
}

func FloatSmaller(a, b float64) bool {
	return DefaultAccuracy.Smaller(a, b)
}

func (this Accuracy) Equal(a, b float64) bool {
	return math.Abs(a-b) < this()
}

func (this Accuracy) Greater(a, b float64) bool {
	return math.Max(a, b) == a && math.Abs(a-b) > this()
}

func (this Accuracy) Smaller(a, b float64) bool {
	return math.Max(a, b) == b && math.Abs(a-b) > this()
}

func (this Accuracy) GreaterOrEqual(a, b float64) bool {
	return math.Max(a, b) == a || math.Abs(a-b) < this()
}

func (this Accuracy) SmallerOrEqual(a, b float64) bool {
	return math.Max(a, b) == b || math.Abs(a-b) < this()
}
