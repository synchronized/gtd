package main

import (
	"math"
	"simple_soccer/common"
)

//这可以用来改变球员的踢腿精度。
//在踢球之前，用球的位置和球的目标作为参数来调用它。
func AddNoiseToKick(ctx *SoccerContext, ballPos, ballTarget common.Vector2d) common.Vector2d {

	//TODO
	var displacement float64 = (common.Pi - common.Pi*ctx.Config().PlayerKickingAccuracy) * RandFloat64Range(-1, 1)

	var toTarget common.Vector2d = *ballTarget.OpMinus(&ballPos)

	toTarget = common.Vec2DRotateAroundOrigin(toTarget, displacement)

	return *toTarget.OpAdd(&ballPos)
}

//足球
type SoccerBall struct {
	*common.MovingEntity
	ctx           *SoccerContext   //上下文
	oldPos        common.Vector2d  //上次记录的位置
	pOwner        IPlayerBase      //控球人员(或者守门员)
	pitchBoundary []*common.Wall2d //球场边界
}

func NewSoccerBall(
	ctx *SoccerContext,
	pos common.Vector2d,
	ballSize, mass float64,
	walls []*common.Wall2d,
) *SoccerBall {
	return &SoccerBall{
		MovingEntity: common.NewMovingEntity(
			0, "球",
			pos,
			ballSize,
			common.Vector2d{0, 0},
			-1.0, //max speed unused
			common.Vector2d{0, 1},
			mass,
			common.Vector2d{1.0, 1.0}, //scale unused
			0, //max turn rate unused
			0, //max force unused
		),
		ctx:           ctx,
		pOwner:        nil,
		pitchBoundary: walls,
	}
}

//检测球与边界的碰撞
func (sb *SoccerBall) TestCollisionWithWalls(walls []*common.Wall2d) {
	var idxClosest = -1
	var velNormal common.Vector2d = *sb.Velocity().Normalize()
	var intersectionPoint common.Vector2d
	//var collisionPoint common.Vector2d
	var distToIntersection float64 = common.MaxFloat

	//遍历每面墙并计算球是否相交。
	//如果是，则将索引存储到最近的相交墙中
	for w := 0; w < len(walls); w++ {
		//假设发生碰撞，如果球继续其当前航向，则计算球上会撞到墙的点。
		//这只是墙的法向（反方向）乘以球的半径，再加上球的中心（它的位置）
		var thisCollisionPoint = sb.Pos().OpMinus(walls[w].Normal().OpMultiply(sb.BRadius()))
		var side = common.WhereIsPoint(*thisCollisionPoint, *walls[w].From(), *walls[w].Normal())
		if side == common.Plane_backside {
			var distToWall float64 = common.DistanceToRayPlaneIntersection(
				*thisCollisionPoint,
				*walls[w].Normal(),
				*walls[w].From(),
				*walls[w].Normal(),
			)
			intersectionPoint = *thisCollisionPoint.OpAdd(walls[w].Normal().OpMultiply(distToWall))
		} else {
			var distToWall float64 = common.DistanceToRayPlaneIntersection(
				*thisCollisionPoint,
				velNormal,
				*walls[w].From(),
				*walls[w].Normal(),
			)
			intersectionPoint = *thisCollisionPoint.OpAdd(velNormal.OpMultiply(distToWall))
		}

		//检查以确保交点实际位于线段上
		var onLineSegment = false
		if common.LineIntersection2D(
			*walls[w].From(),
			*walls[w].To(),
			*thisCollisionPoint.OpMinus(walls[w].Normal().OpMultiply(20.0)),
			*thisCollisionPoint.OpAdd(walls[w].Normal().OpMultiply(20.0)),
		) {
			onLineSegment = true
		}

		//注意，现在没有测试与线段末端的碰撞，请检查碰撞点是否在速度向量的范围内。
		//[以距离平方计算以避免sqrt]如果这是迄今为止发现的最接近的命中。
		//如果是这样的话，意味着在这个时间步和下一个时间步之间的某个时候，球会与墙碰撞。
		var distSq float64 = thisCollisionPoint.DistanceSq(&intersectionPoint)
		if distSq <= sb.Velocity().LengthSq() && distSq < distToIntersection && onLineSegment {
			distToIntersection = distSq
			idxClosest = w
			//collisionPoint = IntersectionPoint
		}
	} //next wall

	//为了避免计算精确的碰撞时间，我们可以在反射之前检查速度是否与壁面法向相反。
	//这样可以防止出现过冲，球在完全重新进入比赛区域之前被反射回底线。
	if idxClosest >= 0 && velNormal.Dot(walls[idxClosest].Normal()) < 0 {
		sb.SetVelocity(*sb.Velocity().Reflect(walls[idxClosest].Normal()))
	}
}

//踢球
func (sb *SoccerBall) Kick(direction common.Vector2d, force float64) {
	direction.NormalizeAssign()
	var acceleration common.Vector2d = *direction.OpMultiply(force).OpDivide(sb.Mass())
	sb.SetVelocity(acceleration)
}

//给定一个力和通过的起点和重点定义的移动距离
//该方法计算球经过这段距离需要花多久
func (sb *SoccerBall) TimeToCoverDistance(from, to common.Vector2d, force float64) float64 {
	//如果传球了，那么这将是球的下一步速度
	//这里其实是瞬间加速度，在模型中认为球在受力时速度为0
	var speed float64 = force / sb.Mass()

	//使用公式计算to的速度
	//v^2 = t^2 + 2ax a是摩擦力加速度
	//先计算x(两点之间的距离)
	var distance float64 = from.Distance(&to)
	var term float64 = speed*speed + 2*sb.Ctx().Config().Friction*distance
	if term < 0 {
		return -1.0
	}

	var toVelocity float64 = math.Sqrt(term)
	//使用公式 t = (v - u)/a
	return (toVelocity - speed) / sb.Ctx().Config().Friction
}

//计算给定时间后球的位置
func (sb *SoccerBall) FuturePosition(time float64) common.Vector2d {
	//使用公式: x = ut + 1/2at^2, x 是距离，a是摩擦力加速度, u为初始速度
	//计算ut 项，这是向量
	var ut common.Vector2d = *sb.Velocity().OpMultiply(time)

	//计算1/2at^2,这个是标量
	var half_a_t_squared float64 = 0.5 * sb.Ctx().Config().Friction * time * time

	//通过乘上速度的标准化向量(因为有方向),把标量转变为向量
	var scalarToVector common.Vector2d = *sb.Velocity().Normalize().OpMultiply(half_a_t_squared)

	//预测位置为球的位置加上这两项
	return *sb.Pos().OpAdd(&ut).OpAdd(&scalarToVector)
}

//被场上的球员或者守门员停球(控球)
func (sb *SoccerBall) Trap() {
	sb.Velocity().Zero()
}

func (sb *SoccerBall) OldPos() *common.Vector2d {
	return &sb.oldPos
}

func (sb *SoccerBall) Ctx() *SoccerContext {
	return sb.ctx
}

//设置球的位置,并且设置速度为0
func (sb *SoccerBall) PlaceAtPosition(newPos common.Vector2d) {
	sb.SetPos(newPos)
	sb.oldPos = *sb.Pos()
	sb.Velocity().Zero()
}

func (sb *SoccerBall) Update() {
	sb.oldPos = *sb.Pos()
	//Test for collisions
	//碰撞检测(球和边界), 后面这里要改成出
	sb.TestCollisionWithWalls(sb.pitchBoundary)

	var velocity = sb.Velocity()
	if velocity.LengthSq() > sb.Ctx().Config().Friction*sb.Ctx().Config().Friction {
		var velocity = velocity.OpAdd(velocity.Normalize().OpMultiply(sb.Ctx().Config().Friction))
		sb.SetVelocity(*velocity)
		sb.SetPos(*sb.Pos().OpAdd(velocity))
		sb.SetHeading(*sb.Velocity().Normalize())
	}
}

func (sb *SoccerBall) Render() {
	//TODO
}
