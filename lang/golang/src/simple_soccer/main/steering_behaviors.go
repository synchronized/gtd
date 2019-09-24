package main

import (
	"math"
	"simple_soccer/common"
)

//Arrive makes use of these to determine how quickly a vehicle
//should decelerate to its target
//到达利用这些来确定车辆应该以多快的速度减速到目标位置
type DecelerationType int //减速

const (
	Deceleration_Slow   DecelerationType = 3
	Deceleration_Normal DecelerationType = 2
	Deceleration_Fast   DecelerationType = 1
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

func NewSteeringBehaviors(agent *PlayerBase, world *SoccerPitch, ball *SoccerBall) *SteeringBehaviors {
	var sb = &SteeringBehaviors{
		pPlayer:         agent,
		iFlags:          0,
		dMultSeparation: agent.Ctx().Config().SeparationCoefficient,
		bTagged:         false,
		dViewDistance:   agent.Ctx().Config().ViewDistance,
		pBall:           ball,
		dInterposeDist:  0.0,
		aAntenna:        make([]common.Vector2d, 5),
	}
	return sb
}

//--------------------------private -------------------------------
//this behavior moves the agent towards a target position
//靠近 这个行为移动agent 到target位置
func (sb *SteeringBehaviors) Seek(target common.Vector2d) common.Vecotr2d {
	var toTarget common.Vector2d = target.OpMinus(sb.pPlayer.Pos())
	var desiredVelocity *common.Vector2d = toTarget.Normalize().OpMultiply(sb.pPlayer.MaxSpeed())
	return desiredVelocity.OpMinus(sb.pPlayer.Velocity())
}

//this behavior is similar to seek but it attempts to arrive
//at the target with a zero velocity
//抵达 这种行为类似于seek，但它试图以零速度到达目标
func (sb *SteeringBehaviors) Arrive(Vector2D target, decel DecelerationType) common.Vecotr2d {
	var toTarget common.Vector2d = target.OpMinus(sb.pPlayer.Pos)
	var dist float64 = toTarget.Length()

	if dist > 0 {
		//because Deceleration is enumerated as an int, this value is required
		//to provide fine tweaking of the deceleration..
		var DecelerationTweaker float64 = 0.3

		//calculate the speed required to reach the target given the desired
		//deceleration
		var speed float64 = dist / (float64(deceleration) * DecelerationTweaker)

		//make sure the velocity does not exceed the max
		speed = math.Min(speed, sb.pPlayer.MaxSpeed())

		//from here proceed just like Seek except we don't need to normalize
		//the ToTarget vector because we have already gone to the trouble
		//of calculating its length: dist.
		//从这里开始就像seek一样进行，只是我们不需要规范化目标向量，
		//因为我们已经陷入了计算其长度dist的麻烦。
		var desiredVelocity common.Vector2d = toTarget.OpMultiply(speed).OpDivide(dist)

		return desiredVelocity.OpMinus(sb.pPlayer.Velocity())
	}
	return common.Vector2d{0.0, 0.0}
}

//This behavior predicts where its prey will be and seeks
//to that location
//追逐 这种行为可以预测猎物的位置并寻找到那个位置
func (sb *SteeringBehaviors) Pursuit(ball *SoccerBall) common.Vecotr2d {
	var toBall common.Vector2d = ball.Pos().OpMinus(sb.pPlayer.Pos())

	//the lookahead time is proportional to the distance between the ball
	//and the pursuer;
	//向前看的时间与球和追赶者之间的距离成正比；
	var lookAheadTime float64 = 0.0
	//TODO 精度
	if ball.Speed() != 0.0 {
		lookAheadTime = toBall.Length() / ball.Speed()
	}
	//calculate where the ball will be at this time in the future
	//计算一下将来这个时候球会在哪里
	sb.vTarget = ball.FuturePosition(lookAheadTime)

	//now seek to the predicted future position of the ball
	//现在靠近预测的球的未来位置
	return sb.Arrive(sb.vTarget, Deceleration_Fast)
}

//分离
//this calculates a force repelling from the other neighbors
//这计算了一个与其他邻居排斥的力
func (sb *SteeringBehaviors) Separation() {
	//iterate through all the neighbors and calculate the vector from the
	var steeringForce *common.Vector2d

	for _, curPlyr := range sb.pPlayer.Pitch().AllMembers() {
		//make sure this agent isn't included in the calculations and that
		//the agent is close enough
		//确保agent未包含在计算中，并且agent足够接近
		if curPlyr != sb.pPlayer && curPlyr.Steering().Tagged() {
			var toAgent common.Vector2d = sb.pPlayer.Pos().OpMinus(curPlyr.Pos())

			//scale the force inversely proportional to the agents distance
			//from its neighbor.
			//将力按与代理距离成反比的方式缩放。
			steeringForce.OpAddAssign(toAgent.Normalize().OpDivide(toAgent.Length()))
		}
	}
	return steeringForce
}

//this attempts to steer the agent to a position between the opponent
//and the object
//插入
//试图引导agent到达opponent和object之间的位置
func (sb *SteeringBehaviors) Interpose(ball *SoccerBall, target common.Vector2d, distFromTarget float64) {
	var toTargetNormalize common.Vector2d = ball.Pos().OpMinus(target).Normalize()
	return sb.Arrive(target.OpAdd(toTargetNormalize.OpMultiply(distFromTarget)), Deceleration_Normal)
}

//finds any neighbours within the view radius
//找到视野范围内的任何邻居(附近目标)
func (sb *SteeringBehaviors) FindNeighbours() {
	for _, curPlyr := range sb.Pitch().AllMembers() {
		curPlyr.Steering().UnTag()

		//work in distance squared to avoid sqrts
		var to common.Vector2d = curPlyr.Pos - sb.pPlayer.Pos()
		if to.LengthSq() < (sb.dViewDistance * sb.dViewDistance) {
			curPlyr.Steering().Tag()
		}
	} //next
}

//this function tests if a specific bit of m_iFlags is set
func (sb *SteeringBehaviors) On(bt BehaviorsType) bool {
	return (sb.iFlags & bt) == bt
}

// This function calculates how much of its max steering force the
// vehicle has left to apply and then applies that amount of the
// force to add.
// 此函数计算车辆剩余要施加的最大转向力的量，然后施加要添加的力的量。
//累计“力” 注意:这里会修改sf
func (sb *SteeringBehaviors) AccumulateForce(sf *common.Vector2d, forceToAdd common.Vector2d) (ok bool) {
	//first calculate how much steering force we have left to use
	//首先计算我们还剩多少转向力
	var magnitudeSoFar float64 = sf.Length()
	var magnitudeRemaining float64 = sb.pPlayer.MaxForce() - magnitudeSoFar
	//return false if there is no more force left to use
	if magnitudeRemaining <= 0.0 {
		return false
	}

	//calculate the magnitude of the force we want to add
	//计算增加的力的大小
	var magnitudeToAdd float64 = forceToAdd.Length()

	//now calculate how much of the force we can really add
	//现在计算一下我们能加多少力
	if magnitudeToAdd > magnitudeRemaining {
		magnitudeToAdd = magnitudeRemaining
	}

	//add it to the steering force
	sf.OpAddAssign(forceToAdd.NormalizeAssign().OpMultiplyAssign(magnitudeToAdd))
	return true
}

//  this method calls each active steering behavior and acumulates their
//  forces until the max steering force magnitude is reached at which
//  time the function returns the steering force accumulated to that
//  point
// 此方法调用每个主动转向行为并累积其力，
// 直到达到最大转向力大小，此时函数返回累积到该点的转向力
func (sb *SteeringBehaviors) SumForces() common.Vector2d {
	var force *common.Vector2d

	//the soccer players must always tag their neighbors
	sb.FindNeighbours()
	if sb.On(BehaviorType_Separation) {
		force.OpAddAssign(sb.Separation().OpMultiplyAssign(sb.dMultSeparation))
		if !sb.AccumulateForce(&sb.vSteeringForce, force) {
			return sb.vSteeringForce
		}
	}
	if sb.On(BehaviorType_Seek) {
		force.OpAddAssign(sb.Seek(sb.vTarget))
		if !sb.AccumulateForce(&sb.vSteeringForce, force) {
			return sb.vSteeringForce
		}
	}
	if sb.On(BehaviorType_Arrive) {
		force.OpAddAssign(sb.Arrive(sb.vTarget, Deceleration_Fast))
		if !sb.AccumulateForce(&sb.vSteeringForce, force) {
			return sb.vSteeringForce
		}
	}
	if sb.On(BehaviorType_Pursuit) {
		force.OpAddAssign(sb.Pursuit(sb.pBall))
		if !sb.AccumulateForce(&sb.vSteeringForce, force) {
			return sb.vSteeringForce
		}
	}
	if sb.On(BehaviorType_Interpose) {
		force.OpAddAssign(sb.Interpose(sb.pBall, sb.vTarget, sb.dInterposeDist))
		if !sb.AccumulateForce(&sb.vSteeringForce, force) {
			return sb.vSteeringForce
		}
	}
	return sb.vSteeringForce
}

//--------------------------public -------------------------------
//  calculates the overall steering force based on the currently active
//  steering behaviors.
// 根据当前激活的转向行为计算总转向力。
func (sb *SteeringBehaviors) Calculate() common.Vector2d {
	//reset the force
	sb.vSteeringForce.Zero()

	//this will hold the value of each individual steering force
	sb.vSteeringForce = sb.SubForces()

	//make sure the force doesn't exceed the vehicles maximum allowable
	sb.vSteeringForce.Truncate(sb.pPlayer.MaxForce())
	return sb.vSteeringForce
}

//calculates the component of the steering force that is parallel
//with the vehicle heading
//计算与车辆航向平行的转向力分量
func (sb *SteeringBehaviors) ForwardComponent() float64 {
	return sb.pPlayer.Heading().Dot(sb.vSteeringForce)
}

//calculates the component of the steering force that is perpendicuar
//with the vehicle heading
//计算与车辆航向垂直的转向力分量
func (sb *SteeringBehaviors) SideComponent() float64 {
	return sb.pPlayer.Side().Dot(sb.vSteeringForce) * sb.pPlayer.MaxTurnRate()
}

func (sb *SteeringBehaviors) Force() common.Vector2d { return sb.vSteeringForce }

func (sb *SteeringBehaviors) Target() common.Vector2d       { return sb.vTarget }
func (sb *SteeringBehaviors) SetTarget(tar common.Vector2d) { sb.vTarget = tar }

func (sb *SteeringBehaviors) InterposeDistance() float64        { return sb.dInterposeDist }
func (sb *SteeringBehaviors) SetInterposeDistance(dist float64) { sb.dInterposeDist = dist }

func (sb *SteeringBehaviors) Tagged() bool { return sb.bTagged }
func (sb *SteeringBehaviors) Tag()         { sb.bTagged = true }
func (sb *SteeringBehaviors) UnTag()       { sb.bTagged = false }

func (sb *SteeringBehaviors) SeekOn()       { sb.iFlags |= BehaviorType_Seek }
func (sb *SteeringBehaviors) ArriveOn()     { sb.iFlags |= BehaviorType_Arrive }
func (sb *SteeringBehaviors) PursuitOn()    { sb.iFlags |= BehaviorType_Pursuit }
func (sb *SteeringBehaviors) SeparationOn() { sb.iFlags |= BehaviorType_Separation }
func (sb *SteeringBehaviors) InterposeOn(d float64) {
	sb.iFlags |= BehaviorType_Interpose
	sb.dInterposeDist = d
}

func (sb *SteeringBehaviors) SeekOff() {
	if sb.On(BehaviorType_Seek) {
		sb.iFlags ^= BehaviorType_Seek
	}
}
func (sb *SteeringBehaviors) ArriveOff() {
	if sb.On(BehaviorType_Arrive) {
		sb.iFlags ^= BehaviorType_Arrive
	}
}
func (sb *SteeringBehaviors) PursuitOff() {
	if sb.On(BehaviorType_Pursuit) {
		sb.iFlags ^= BehaviorType_Pursuit
	}
}
func (sb *SteeringBehaviors) SeparationOff() {
	if sb.On(BehaviorType_Separation) {
		sb.iFlags ^= BehaviorType_Separation
	}
}
func (sb *SteeringBehaviors) InterposeOff() {
	if sb.On(BehaviorType_Interpose) {
		sb.iFlags ^= BehaviorType_Interpose
	}
}

func (sb *SteeringBehaviors) SeekIsOn() bool       { return sb.On(BehaviorType_Seek) }
func (sb *SteeringBehaviors) ArriveIsOn() bool     { return sb.On(BehaviorType_Arrive) }
func (sb *SteeringBehaviors) PursuitIsOn() bool    { return sb.On(BehaviorType_Pursuit) }
func (sb *SteeringBehaviors) SeparationIsOn() bool { return sb.On(BehaviorType_Separation) }
func (sb *SteeringBehaviors) InterposeIsOn() bool  { return sb.On(BehaviorType_Interpose) }

//renders visual aids and info for seeing how each behavior is
//calculated
//呈现视觉帮助和信息，以查看如何计算每个行为
func (sb *SteeringBehaviors) RenderInfo() { /*TODO*/ }

//助手
func (sb *SteeringBehaviors) RenderAids() { /*TODO*/ }
