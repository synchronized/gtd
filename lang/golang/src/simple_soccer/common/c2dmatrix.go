package common

import "math"

type Matrix struct {
	m11, m12, m13 float64
	m21, m22, m23 float64
	m31, m32, m33 float64
}

type C2DMatrix struct {
	matrix Matrix
}

func NewC2DMatrix() *C2DMatrix {
	var c2dmatrix = &C2DMatrix{}
	c2dmatrix.Identity()
	return c2dmatrix
}

//accessors to the matrix elements
func (c2d *C2DMatrix) M11() float64 { return c2d.matrix.m11 }
func (c2d *C2DMatrix) M12() float64 { return c2d.matrix.m12 }
func (c2d *C2DMatrix) M13() float64 { return c2d.matrix.m13 }

func (c2d *C2DMatrix) M21() float64 { return c2d.matrix.m21 }
func (c2d *C2DMatrix) M22() float64 { return c2d.matrix.m22 }
func (c2d *C2DMatrix) M23() float64 { return c2d.matrix.m23 }

func (c2d *C2DMatrix) M31() float64 { return c2d.matrix.m31 }
func (c2d *C2DMatrix) M32() float64 { return c2d.matrix.m32 }
func (c2d *C2DMatrix) M33() float64 { return c2d.matrix.m33 }

func (c2d *C2DMatrix) SetM11(val float64) { c2d.matrix.m11 = val }
func (c2d *C2DMatrix) SetM12(val float64) { c2d.matrix.m12 = val }
func (c2d *C2DMatrix) SetM13(val float64) { c2d.matrix.m13 = val }

func (c2d *C2DMatrix) SetM21(val float64) { c2d.matrix.m21 = val }
func (c2d *C2DMatrix) SetM22(val float64) { c2d.matrix.m22 = val }
func (c2d *C2DMatrix) SetM23(val float64) { c2d.matrix.m23 = val }

func (c2d *C2DMatrix) SetM31(val float64) { c2d.matrix.m31 = val }
func (c2d *C2DMatrix) SetM32(val float64) { c2d.matrix.m32 = val }
func (c2d *C2DMatrix) SetM33(val float64) { c2d.matrix.m33 = val }

//multiply two matrices together
//两个矩阵的乘法
func (c2d *C2DMatrix) MatrixMultiply(mIn Matrix) {
	var mat_temp Matrix

	//first row
	mat_temp.m11 = (c2d.matrix.m11 * mIn.m11) + (c2d.matrix.m12 * mIn.m21) + (c2d.matrix.m13 * mIn.m31)
	mat_temp.m12 = (c2d.matrix.m11 * mIn.m12) + (c2d.matrix.m12 * mIn.m22) + (c2d.matrix.m13 * mIn.m32)
	mat_temp.m13 = (c2d.matrix.m11 * mIn.m13) + (c2d.matrix.m12 * mIn.m23) + (c2d.matrix.m13 * mIn.m33)

	//second
	mat_temp.m21 = (c2d.matrix.m21 * mIn.m11) + (c2d.matrix.m22 * mIn.m21) + (c2d.matrix.m23 * mIn.m31)
	mat_temp.m22 = (c2d.matrix.m21 * mIn.m12) + (c2d.matrix.m22 * mIn.m22) + (c2d.matrix.m23 * mIn.m32)
	mat_temp.m23 = (c2d.matrix.m21 * mIn.m13) + (c2d.matrix.m22 * mIn.m23) + (c2d.matrix.m23 * mIn.m33)

	//third
	mat_temp.m31 = (c2d.matrix.m31 * mIn.m11) + (c2d.matrix.m32 * mIn.m21) + (c2d.matrix.m33 * mIn.m31)
	mat_temp.m32 = (c2d.matrix.m31 * mIn.m12) + (c2d.matrix.m32 * mIn.m22) + (c2d.matrix.m33 * mIn.m32)
	mat_temp.m33 = (c2d.matrix.m31 * mIn.m13) + (c2d.matrix.m32 * mIn.m23) + (c2d.matrix.m33 * mIn.m33)

	c2d.matrix = mat_temp
}

//applies a 2D transformation matrix to a Array of Vector2Ds
//将二维变换矩阵应用于2D矢量数组
//注意： 这将改变vPoint
func (c2d *C2DMatrix) TransformVector2Ds(vPoint []Vector2d) {
	for i := 0; i < len(vPoint); i++ {
		var tempX flaot64 = (c2d.matrix.m11 * vPoint[i].X) + (c2d.matrix.m21 * vPoint[i].Y) + (c2d.matrix.m31)
		var tempY float64 = (c2d.matrix.m12 * vPoint[i].X) + (c2d.matrix.m22 * vPoint[i].Y) + (c2d.matrix.m32)

		vPoint[i].X = tempX
		vPoint[i].Y = tempY
	}
}

//applies a 2D transformation matrix to a single Vector2D
//将二维变换矩阵应用于单个矢量
//注意： 这将改变vPoint
func (c2d *C2DMatrix) TransformVector2D(vPoint *Vector2D) {

	var tempX float64 = (c2d.matrix.m11 * vPoint.X) + (c2d.matrix.m21 * vPoint.Y) + (c2d.matrix.m31)
	var tempY float64 = (c2d.matrix.m12 * vPoint.X) + (c2d.matrix.m22 * vPoint.Y) + (c2d.matrix.m32)

	vPoint.X = tempX
	vPoint.Y = tempY
}

//create an identity matrix
func (c2d *C2DMatrix) Identity() {
	c2d.matrix.m11 = 1
	c2d.matrix.m12 = 0
	c2d.matrix.m13 = 0

	c2d.matrix.m21 = 0
	c2d.matrix.m22 = 1
	c2d.matrix.m23 = 0

	c2d.matrix.m31 = 0
	c2d.matrix.m32 = 0
	c2d.matrix.m33 = 1
}

//create a transformation matrix
func (c2d *C2DMatrix) Translate(x, y float64) {
	var mat Matrix

	mat.m11 = 1
	mat.m12 = 0
	mat.m13 = 0

	mat.m21 = 0
	mat.m22 = 1
	mat.m23 = 0

	mat.m31 = x
	mat.m32 = y
	mat.m33 = 1

	//and multiply
	c2d.MatrixMultiply(mat)
}

//create a scale matrix
func (c2d *C2DMatrix) Scale(xScale, yScale float64) {
	var mat Matrix

	mat.m11 = xScale
	mat.m12 = 0
	mat.m13 = 0

	mat.m21 = 0
	mat.m22 = yScale
	mat.m23 = 0

	mat.m31 = 0
	mat.m32 = 0
	mat.m33 = 1

	//and multiply
	c2d.MatrixMultiply(mat)
}

//create a rotation matrix
func (c2d *C2DMatrix) Rotate(rot float64) {
	var mat Matrix

	var Sin float64 = math.Sin(rot)
	var Cos float64 = math.Cos(rot)

	mat.m11 = Cos
	mat.m12 = Sin
	mat.m13 = 0

	mat.m21 = -Sin
	mat.m22 = Cos
	mat.m23 = 0

	mat.m31 = 0
	mat.m32 = 0
	mat.m33 = 1

	//and multiply
	c2d.MatrixMultiply(mat)
}

//create a rotation matrix from a 2D vector
func (c2d *C2DMatrix) Rotate(fwd, side Vector2d) {
	var mat Matrix

	mat.m11 = fwd.X
	mat.m12 = fwd.Y
	mat.m13 = 0

	mat.m21 = side.X
	mat.m22 = side.Y
	mat.m23 = 0

	mat.m31 = 0
	mat.m32 = 0
	mat.m33 = 1

	//and multiply
	c2d.MatrixMultiply(mat)
}
