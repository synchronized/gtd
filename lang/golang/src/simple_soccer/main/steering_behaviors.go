package main

import (
	"math"
)

//Arrive makes use of these to determine how quickly a vehicle
//should decelerate to its target
//到达利用这些来确定车辆应该以多快的速度减速到目标位置
const (
	Deceleration_Slow   = 3
	Deceleration_Normal = 2
	Deceleration_Fast   = 1
)

type BehaviorType int

const (
	BehaviorType_None       BehaviorType = 0x0000
	BehaviorType_Seek       BehaviorType = 0x0001
	BehaviorType_Arrive     BehaviorType = 0x0002
	BehaviorType_Separation BehaviorType = 0x0004
	BehaviorType_Pursuit    BehaviorType = 0x0008
	BehaviorType_Interpose  BehaviorType = 0x0010
)

type SteeringBehaviors struct {
	pPlayer *PlayerBase
	pBall   *SoccerBakk
	//the steering force created by the combined effect of all
	//the selected behaviors
	vSteeringForce common.Vector2d
	//the current target (usually the ball or predicted ball position)
	vTarget common.Vector2d
	//the distance the player tries to interpose from the target
	//玩家试图插入目标的距离
	dInterposeDist float64
	//multipliers.
	dMultSeparation float64
	//how far it can 'see'
	dViewDistance float64
	//binary flags to indicate whether or not a behavior should be active
	iFlags int
	//used by group behaviors to tag neighbours
	bTagged bool

	//a vertex buffer to contain the feelers rqd for dribbling
	//一个顶点缓冲区，用于包含用于运球的触角rqd
	aAntenna []common.Vector2d
}

func NewSteeringBehaviors(player *PlayerBase, pitch *SoccerPitch, ball *SoccerBall) *SteeringBehaviors {
	//TODO
	return &SteeringBehaviors{}
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
	var lookAheadTime float64 = TurnaroundTime(sb.pVehicle, evader.Pos())
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
	var distToClosestIP float64 = common.MaxFloat64 //max double
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
	var distToClosestIP float64 = common.MaxFloat64

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
	sb.bSeek = true
}
func (sb *SteeringBehaviors) SeekOff() {
	sb.bSeek = false
}
func (sb *SteeringBehaviors) FleeOn() {
	sb.bFlee = true
}
func (sb *SteeringBehaviors) FleeOff() {
	sb.bFlee = false
}
func (sb *SteeringBehaviors) ArriveOn() {
	sb.bArrive = true
}
func (sb *SteeringBehaviors) ArriveOff() {
	sb.bArrive = false
}

func (sb *SteeringBehaviors) SeparationOn() {
	sb.bSeparation = true
}

func (sb *SteeringBehaviors) SeparationOff() {
	sb.bSeparation = false
}
