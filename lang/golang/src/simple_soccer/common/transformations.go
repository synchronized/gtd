package common

//--------------------------- WorldTransform -----------------------------
//
//  given a std::vector of 2D vectors, a position, orientation and scale,
//  this function transforms the 2D vectors into the object's world space
//------------------------------------------------------------------------
/*
 * 给定一个二维的向量，位置、方向和尺度，
 * 此函数将二维向量转换为对象的世界空间
 */
func WorldTransform2(points []Vector2d, pos, forward, side, scale Vector2d) []Vector2d {
	//copy the original vertices into the buffer about to be transformed
	var TranVector2Ds = make([]Vector2d, len(points))
	copy(TranVector2Ds, points)

	//create a transformation matrix
	var matTransform C2DMatrix

	//scale
	if (scale.X != 1.0) || (scale.Y != 1.0) {
		matTransform.Scale(scale.X, scale.Y)
	}

	//rotate
	matTransform.Rotate2(forward, side)

	//and translate
	matTransform.Translate(pos.X, pos.Y)

	//now transform the object's vertices
	matTransform.TransformVector2Ds(TranVector2Ds)

	return TranVector2Ds
}

//--------------------------- WorldTransform -----------------------------
//
//  given a std::vector of 2D vectors, a position and  orientation
//  this function transforms the 2D vectors into the object's world space
//------------------------------------------------------------------------
func WorldTransform(points []Vector2d, pos, forward, side Vector2d) []Vector2d {
	//copy the original vertices into the buffer about to be transformed
	var TranVector2Ds = make([]Vector2d, len(points))
	copy(TranVector2Ds, points)

	//create a transformation matrix
	var matTransform C2DMatrix

	//rotate
	matTransform.Rotate2(forward, side)

	//and translate
	matTransform.Translate(pos.X, pos.Y)

	//now transform the object's vertices
	matTransform.TransformVector2Ds(TranVector2Ds)

	return TranVector2Ds
}

//--------------------- PointToWorldSpace --------------------------------
//
//  Transforms a point from the agent's local space into world space
//------------------------------------------------------------------------
func PointToWorldSpace(point, AgentHeading, AgentSide, AgentPosition Vector2d) Vector2d {
	//make a copy of the point
	var TransPoint Vector2d = point

	//create a transformation matrix
	var matTransform C2DMatrix

	//rotate
	matTransform.Rotate2(AgentHeading, AgentSide)

	//and translate
	matTransform.Translate(AgentPosition.X, AgentPosition.Y)

	//now transform the vertices
	matTransform.TransformVector2D(&TransPoint)

	return TransPoint
}

//--------------------- VectorToWorldSpace --------------------------------
//
//  Transforms a vector from the agent's local space into world space
//------------------------------------------------------------------------
func VectorToWorldSpace(vec, AgentHeading, AgentSide Vector2d) Vector2d {
	//make a copy of the point
	var TransVec Vector2d = vec

	//create a transformation matrix
	var matTransform C2DMatrix

	//rotate
	matTransform.Rotate2(AgentHeading, AgentSide)

	//now transform the vertices
	matTransform.TransformVector2D(&TransVec)

	return TransVec
}

//--------------------- PointToLocalSpace --------------------------------
//
//------------------------------------------------------------------------
func PointToLocalSpace(point, AgentHeading, AgentSide, AgentPosition Vector2d) Vector2d {

	//make a copy of the point
	var TransPoint Vector2d = point

	//create a transformation matrix
	var matTransform C2DMatrix

	var Tx float64 = -AgentPosition.Dot(&AgentHeading)
	var Ty float64 = -AgentPosition.Dot(&AgentSide)

	//create the transformation matrix
	matTransform.SetM11(AgentHeading.X)
	matTransform.SetM12(AgentSide.X)
	matTransform.SetM21(AgentHeading.Y)
	matTransform.SetM22(AgentSide.Y)
	matTransform.SetM31(Tx)
	matTransform.SetM32(Ty)

	//now transform the vertices
	matTransform.TransformVector2D(&TransPoint)

	return TransPoint
}

//--------------------- VectorToLocalSpace --------------------------------
//
//------------------------------------------------------------------------
func VectorToLocalSpace(vec, AgentHeading, AgentSide Vector2d) Vector2d {

	//make a copy of the point
	var TransPoint Vector2d = vec

	//create a transformation matrix
	var matTransform C2DMatrix

	//create the transformation matrix
	matTransform.SetM11(AgentHeading.X)
	matTransform.SetM12(AgentSide.X)
	matTransform.SetM21(AgentHeading.Y)
	matTransform.SetM22(AgentSide.Y)

	//now transform the vertices
	matTransform.TransformVector2D(&TransPoint)

	return TransPoint
}

//-------------------------- Vec2DRotateAroundOrigin --------------------------
//
//  rotates a vector ang rads around the origin
//-----------------------------------------------------------------------------
//根据半径绕原点旋转矢量v
func Vec2DRotateAroundOrigin(v Vector2d, ang float64) Vector2d {
	//create a transformation matrix
	var result Vector2d = v
	var mat C2DMatrix

	//rotate
	mat.Rotate(ang)

	//now transform the object's vertices
	mat.TransformVector2D(&result)
	return result
}

//------------------------ CreateWhiskers ------------------------------------
//
//  given an origin, a facing direction, a 'field of view' describing the
//  limit of the outer whiskers, a whisker length and the number of whiskers
//  this method returns a vector containing the end positions of a series
//  of whiskers radiating away from the origin and with equal distance between
//  them. (like the spokes of a wheel clipped to a specific segment size)
//----------------------------------------------------------------------------
func CreateWhiskers(NumWhiskers int, WhiskerLength, fov float64, facing, origin Vector2d) []Vector2d {
	//this is the magnitude of the angle separating each whisker
	var SectorSize float64 = fov / float64(NumWhiskers-1)

	var whiskers = make([]Vector2d, NumWhiskers)
	var temp Vector2d
	var angle float64 = -fov * 0.5

	for w := 0; w < NumWhiskers; w++ {
		//create the whisker extending outwards at this angle
		temp = Vec2DRotateAroundOrigin(facing, angle)
		whiskers[w] = *origin.OpAdd(temp.OpMultiply(WhiskerLength))

		angle += SectorSize
	}

	return whiskers
}
