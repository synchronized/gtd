package main

import (
	"math"
)

const (
	Deceleration_Slow   = 3
	Deceleration_normal = 2
	Deceleration_fast   = 1
)

const (
	BehaviorType_none               = 0x00000
	BehaviorType_seek               = 0x00002
	BehaviorType_flee               = 0x00004
	BehaviorType_arrive             = 0x00008
	BehaviorType_wander             = 0x00010
	BehaviorType_cohesion           = 0x00020
	BehaviorType_separation         = 0x00040
	BehaviorType_allignment         = 0x00080
	BehaviorType_obstacle_avoidance = 0x00100
	BehaviorType_wall_avoidance     = 0x00200
	BehaviorType_follow_path        = 0x00400
	BehaviorType_pursuit            = 0x00800
	BehaviorType_evade              = 0x01000
	BehaviorType_interpose          = 0x02000
	BehaviorType_hide               = 0x04000
	BehaviorType_flock              = 0x08000
	BehaviorType_offset_pursuit     = 0x10000
)

type SteeringBehaviors struct {
	pVehicle       *Vehicle
	vSteeringForce Vector2d
	pTargetAgent1  *Vehicle
	pTargetAgent2  *Vehicle
	vTarget        Vector2d
	dBoxLength     float64

	vWanderTarget   Vector2d //一个点被限制在半径为dWanderRadius的圆圈上
	dWanderRadius   float64  //徘徊-wander圈的半径
	dWanderDistance float64  //wander圈的出现在智能体前面的距离
	dWanderTitter   float64  //每秒加到目标的随即位移的最大值

	vFeelers []int
}

func NewSteeringBehaviors() *SteeringBehaviors {

}

//靠近,返回达到目标地点需要的力
func (sb *SteeringBehaviors) Seek(target Vector2d) Vector2d {
	var desiredVelocity = target.OpMinus(sb.pVehicle.Pos()).Normalize().OpMultiply(sb.pVehicle.MaxSpeed())
	return desiredVelocity.OpMinus(sb.pVehicle.Velocity())
}

//离开,返回离开目标位置的力
func (sb *SteeringBehaviors) Flee(target Vector2d) Vector2d {
	var panicDistanceSq float64 = 100.0 * 100.0
	if sb.pVehicle.Pos().DistanceSq(target) > panicDistanceSq {
		return Vector2d{0.0, 0.0}
	}
	var desiredVelocity = sb.pVehicle.Pos().OpMinus(target).Normalize().OpMultiply(sb.pVehicle.MaxSpeed())
	return desiredVelocity.OpMinus(sb.pVehicle.Velocity())
}

//抵达
func (sb *SteeringBehaviors) Arrive(target Vector2d, deceleration int) Vector2d {
	var toTarget Vector2d = target - sb.pVehicle.Pos()
	var dist float64 = toTarget.Length()
	//if dist > toTarget.AccuracyVal() {
	if dist > 0 {
		var decelerationTweaker floaot64 = 0.3
		//给定预期的减速度
		var speed float64 = dist / flaot64(deceleration) * decelerationTweaker
		//确保不会超过最大值
		speed = math.Min(speed, sb.pVehicle.MaxSpeed())
		//处理和seek一样，除了不需要归一化ToTarget矢量
		//因为已经计算了距离(dict)
		var desiredVelocity Vector2d = toTarget.OpMultiply(speed).OpDivide(dict)
		return desiredVelocity.OpMinus(sb.pVehicle.Velocity())
	}
	return Vector2d{0.0, 0.0}
}

//追逐
func (sb *SteeringBehaviors) Pursuit(evader *Vehicle) Vector2d {
	//如果逃避者在前方,而且面对者智能体
	//那么我们可以正好靠近逃避着的当前位置
	var toEvader Vector2d = evader.Pos().OpMinus(sb.pVehicle.Pos())
	//点积在Normalize操作下就是夹角的余旋值
	var relativeHeading float64 = sb.pVehicle.Heading().Dot(evader.Heading())
	// acos(0.95) = 10 degs
	if toEvader.Dot(sb.pVehicle.Heading()) > 0 && relativeHeading < -0.95 {
		return sb.Seek(evader.Pos())
	}

	//预测逃避者的的位置
	//预测的时间正比与距离，反比于速度
	// var lookAheadTime float64 = toEvader.Length() / (sb.pVehicle.MaxSpeed() + evade.Speed())
	var lookAheadTime float64 = TrunaroundTime(sb.pVehicle, evader.Pos())
	//现在靠近逃避着的被预测位置
	return Seek(evader.Pos().OpAdd(evader.Velocity().OpMultiply(lookAheadTime)))

}

//逃避
func (sb *SteeringBehaviors) Evade(pursuer *Vehicle) Vector2d {
	var toPursuer = pursuer.Pos().OpMinus(sb.pVehicle.Pos())
	var lookAheadTime float64 = toPursuer.Length() / (sb.pVehicle.MaxSpeed() + evade.Speed())
	return sb.Flee(pursuer.Pos().OpAdd(pursuer.Velocity().OpMultiply(lookAheadTime)))
}

//徘徊
func (sb *SteeringBehaviors) Wander() Vector2d {
	//增加一个小的随即向量到目标位置上
	sb.vWanderTarget.OpAddAssign(Vector2d{
		sb.dWanderJitter * RandomClamped(),
		sb.dWanderJitter * RandomClamped(),
	})
	//投影到单位圆上
	sb.vWanderTarget.Normalize()
	//增加向量长度wangder半径，投影到wangder圆圈上
	sb.vWanderTarget.OpMultiply(sb.dWanderRadius)

	//移动目标到智能体前面的位置
	var targetLocal Vector2d = sb.vWanderTarget.OpAdd(sb.dWanderDistance, 0)
	//把目标投影到世界空间
	var targetWorld Vector2d = common.PointToWorldSpace(
		targetLocal,
		sb.pVehicle.Heading(),
		sb.pVehicle.Side(),
		sb.pVehicle.Pos(),
	)

	//移动向它
	return targetWorld.OpMinus(sb.pVehicle.Pos())
}

//避开障碍
func (sb *SteeringBehaviors) ObstracleAvoidance(obstracle []IBaseGameEntity) Vector2d {
	//检测盒长度正比于智能体的速度
	//TODO config
	sb.dBoxLength = Prm.MinDetectionBoxLength + sb.pVehicle.Speed()/sb.pVehicle.MaxSpeed()*Prm.MinDetectionBoxLength
	//标记范围内的所有障碍物
	sb.pVehicle.World().TagObstacleWithViewRange(sb.Vehicle, sb.dBoxLength)
	//跟踪最近的相交的障碍物(CIB)
	var closestIntersectingObstacle common.IBaseGameEntity
	//跟踪CIB距离
	var distToClosestIP float64 = 9999999999999 //max double
	//记录被转化的CIB局部坐标
	var localPosOfClosestObstacle Vector2d
	for _, curOb := range abstracle {
		//如果被标记在范围内
		if !curOb.IsTagged() {
			continue
		}
		//计算这个障碍物的局部坐标的位置
		var localPos Vector2d = common.PointToLocalSpace(curOb.Pos(),
			sb.pVehicle.Heading(),
			sb.pVehicle.Side(),
			sb.pVehicle.Pos(),
		)
		//如果局部空间位置x为负,那么他在智能体后面
		//(这种情况,他可以被忽略)
		if localPos.X() <= 0 {
			continue
		}
		//如果物体到x轴的距离小雨他的半径+检查盒宽度的一半时，
		//那么可能相交
		var expandedRadius float64 = curOb.BRandius() + sb.pVehicle.BRandius()
		if math.Abs(localPos.Y()) >= expandedRadius {
			continue
		}
		//现在做线/圆相交测试,圆周的中心是(cX,cY)
		//相交的公式是x=cX +/- sqrt(r^2 - cY^2) 此时y=0
		//我们只需要看x的最小正值,因为那是最近的相交点
		var cX = localPos.X()
		var cY = localPos.Y()

		//我们值需要一次计算上面等式的开方
		var sqrtPart float64 = math.Sqrt(expandedRadius*expandedRadius - cY*cY)
		var ip float64 = cX - sqrtPart
		if ip <= 0 {
			ip = cX + sqrtPart
		}

		//测试是否是目前为止最近的
		//如果是，记录这个障碍物和他的局部坐标
		if ip < distToClosestIP {
			distToClosestIP = ip
			closestIntersectingObstacle = curOb
			localPosOfClosestObstacle = localPos
		}
	}

	var steeringForce Vector2d
	if closestIntersectingObstacle != nil {
		//智能体离物体越近，操控力就应该越强
		var multiplier float64 = 1.0 + (sb.dBoxLength-localPosOfClosestObstacle.X())/sb.dBoxLength
		//计算侧向力
		steeringForce.X = (closestIntersectingObstacle.BRadius() - localPosOfClosestObstacle.Y) * multiplier
		//施加一个制动力,他正比于障碍物到交通工具的距离
		var brakingWeight = 0.2
		steeringForce.Y = (closestIntersectingObstacle.BRadius() - localPosOfClosestObstacle.X) * brakingWeight
	}

	//最后,把操控向量从局部空间转换到世界向量空间
	return common.VectorToWorldSpace(steeringForce,
		sb.pVehicle.Heading(),
		sb.pVehicle.Side(),
	)
}

//避开墙
func (sb *SteeringBehaviors) WallAvoidance(walls []Wall2d) Vector2d {
	//触须
	createFeelers()

	var distToThisIP float64 = 0.0
	var distToClosestIP float64 = 9999999999999999

	//保存walls 的向量的索引
	var closestWall int = -1

	var steeringForce Vector2d
	var point Vector2d
	var closestPoint Vector2d

	for flr, feeler := range sb.vFeelers {
		for w, wall := range walls {
			var ok bool
			ok, point, distToThisIP = LineIntersection2D(sb.pVehicle.Pos(), feeler, wall.From(), wall.To())
			if ok {
				//目前这是最近的？
				if distToThisIp < distToClosestIP {
					distToClosestIP = distToThisIp
					closestWall = w
					closestPoint = point
				}
			}
		} //下一堵墙

		//如果检测到一个相交点,那么计算出一个使其远离的力
		if closestWall >= 0 {
			//计算智能体吐出的位置会穿透墙的距离
			var overShoot Vector2d = fleer - closestPoint
			//在墙的发现方向 以overShoot 大小创建一个力
			steeringForce = wall.Normal().OpMultiply(overShoot.Length())
		}

	} //下一个触须

	return steeringForce
}

func (sb *SteeringBehaviors) createFeelers() {

}

//计算合成力
func (sb *SteeringBehaviors) Calculate() Vector2d {
	//TODO
}

func (sb *SteeringBehaviors) ForwardComponent() Vector2d {
	//TODO
}

func (sb *SteeringBehaviors) SideComponent() Vector2d {
	//TODO
}

func (sb *SteeringBehaviors) SetPath() {
	//TODO
}

func (sb *SteeringBehaviors) SetTarget(val Vector2d) {
	//TODO
}

func (sb *SteeringBehaviors) SetTargetAgent1(val *Vehicle) {
	//TODO
}
func (sb *SteeringBehaviors) SetTargetAgent2(val *Vehicle) {
	//TODO
}

func (sb *SteeringBehaviors) SeekOn() {
	sb.vSeek //TODO
}
func (sb *SteeringBehaviors) FleeOn() {
	return sb.vFlee //TODO
}
func (sb *SteeringBehaviors) ArriveOn() {
	return sb.vArrive //TODO
}
func (sb *SteeringBehaviors) SeekOff() {
	return sb.vSeek //TODO
}
func (sb *SteeringBehaviors) FleeOff() {
	return sb.vFlee //TODO
}
func (sb *SteeringBehaviors) ArriveOff() {
	return sb.vArrive //TODO
}
