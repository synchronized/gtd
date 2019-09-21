package main

import (
	"math"
	"simple_soccer/common"
)

type RoleType int

const (
	RoleType_GoalKeeper RoleType = 1
	RoleType_Attacker   RoleType = 2
	RoleType_Defender   RoleType = 3
)

const NumberPlayerVerts = 4
const playerVerts []Vector2d = [NumberPlayerVerts]Vector2d{
	Vector2d{-3, 8},
	Vector2d{3, 10},
	Vector2d{3, -10},
	Vector2d{-3, -8},
}

type IPlayerBase interface {
	IsThreatened() bool
	TrackBall()
	TrackTarget()
	FindSupport()
	BallWithinKeeperRange() bool
	BallWithinKickingRange() bool
	BallWithinReceivingRange() bool
	InHomeRegion() bool //
	IsAheadOfAttacker() bool
	AtTarget() bool
	IsClosestTeamMemberToBall() bool
	PositionInFrontOfPlayer(position Vector2d) bool
	IsClosestPlayerOnPitchToBall() bool
	IsControllingPlayer() bool
	InHotRegion() bool
	Role() RoleType
	DistSqToBall() float64
	SetDistSqToBall(val float64)
	DisttoOppGoal() float64
	DistToHomeGoal() float64
	SetDefaultHomeRegion()
	HomeRegion() *Region
	SetHomeRegion()
	Ball() *SoccerBall
	Pitch() *SoccerPitch
	Steering() *SteeringBehaviors
	Team() *SoccerTeam
	GetBaseSupportingSpot() Vector2d
}

type PlayerBase struct {
	IPlayerBase
	*common.MovingEntity
	ctx           *SoccerContext     //上下文
	role          RoleType           //角色
	team          *SoccerTeam        //队伍
	steering      *SteeringBehaviors //行为
	homeRegion    int
	defaultRegion int
	distSqToBall  float64 //和球的距离

	playerVB      []*Vector2d //顶点
	playerVBTrans []*Vector2d //顶点
}

func NewPlayerBase(
	ctx *SoccerTeam,
	homeTeam *SoccerTeam,
	homeRegion int,
	heading, velocity Vector2d,
	mass, maxForce, maxSpeed, maxTurnRate, scale float64,
	role RoleType,
) *PlayerBase {
	var pb = &PlayerBase{
		MovingEntity: common.NewMovingEntity(
			homeTeam.Pitch().GetRegionFromIndex(homeRegion).Center(),
			scale*10.0,
			velocity,
			maxSpeed,
			heading,
			mass,
			Vector2d{scale, sclae},
			maxTurnRate,
			maxForce,
		),
		ctx:           ctx,
		role:          role,
		team:          homeTeam,
		homeRegion:    homeRegion,
		defaultRegion: homeRegion,
		distSqToBall:  common.MaxFloat,
	}

	for vtx, vertex := range playerVerts {
		pb.playerVB = append(pb.playerVB, vertex)
		//
		if math.Abs(vertex.X) > pb.BRadius() {
			pb.SetBRadius(math.Abs(vertex.X))
		}
		if math.Abs(vertex.Y) > pb.BRadius() {
			pb.SetBRadius(math.Abs(vertex.Y))
		}
	}

	pb.steering = NewSteeringBehaviors(pb, team.Pitch(), pb.Ball())
	pb.Steering().SetTarget(team.Pitch().GetRegionFromIndex(homeRegion).Center())
	return pb
}

//如果在该玩家的舒适区内有对手，则返回true
func (pb *PlayerBase) IsThreatened() bool {
	for _, opp := range pb.Team().Opponents().Members() {
		if pb.PositionInFrontOfPlayer(opp.Pos()) &&
			pb.Pos().Distance(opp.Pos()) < pb.ctx.Config().PlayerComfortZoneSq {
			return true
		}
	}
	return false
}

//设置球员的头球指向球
func (pb *PlayerBase) TrackBall() {
	pb.RotateHeadingToFacePosition(pb.Ball().Pos())
}

func (pb *PlayerBase) TrackTarget() {
	pb.SetHeading(pb.Steering().Target().OpMinus(pb.Pos()))
}

//确定离支持点最近的玩家，并向他发送消息，告诉他将状态更改为supportattacker
func (pb *PlayerBase) FindSupport() {
	if pb.Team().SupportingPlayer() == nil {
		var bastSupportPly *PlayerBase = pb.Team().DetermineBestSupportingAttacker()
		pb.Team().SetSupportingPlayer(bastSupportPly)
		pb.ctx.Dispatcher.DispatchMsg(SEND_MSG_IMMEDIATELY,
			ID(),
			pb.Team().SupportingPlayer().Id(),
			Msg_SupportAttacker,
			nil)
	}

	var bastSupportPly *PlayerBase = pb.Team().DetermineBestSupportingAttacker()

	if bastSupportPly != nil && bastSupportPly != pb.Team().SupportingPlayer() {
		if pb.Team().SupportingPlayer() != nil {
			pb.ctx.Dispatcher.DispatchMsg(SEND_MSG_IMMEDIATELY,
				pb.Id(),
				Team().SupportingPlayer().Id(),
				Msg_GoHome,
				nil)
		}

		pb.Team().SetSupportingPlayer(bestSupportPly)

		pb.ctx.Dispatcher.DispatchMsg(SEND_MSG_IMMEDIATELY,
			pb.Id(),
			pb.Team().SupportingPlayer().Id(),
			Msg_SupportAttacker,
			nil)
	}
}

func (pb *PlayerBase) BallWithinKeeperRange() bool {
	return pb.Pos().DistanceSq(pb.Ball().Pos()) < pb.ctx.Config().KeeperInBallRangeSq
}
func (pb *PlayerBase) BallWithinKickingRange() bool {
	return pb.Pos().DistanceSq(pb.Ball().Pos()) < pb.ctx.Config().PlayerKickingDistanceSq
}
func (pb *PlayerBase) BallWithinReceivingRange() bool {
	return pb.Pos().DistanceSq(pb.Ball().Pos()) < pb.ctx.Config().BallWithinReceivingRangeSq
}
func (pb *PlayerBase) InHomeRegion() bool {
	if pb.Role() == RoleType_Keeper {
		return pb.Pitch().GetRegionFormIndex(pb.homeRegion).Inside(pb.Pos, Region_Normal)
	} else {
		return pb.Pitch().GetRegionFormIndex(pb.homeRegion).Inside(pb.Pos, Region_Halfsize)
	}
}
func (pb *PlayerBase) IsAheadOfAttacker() bool {
	return math.Abs(pb.Pos().X-pb.Team().OpponentsGoal().Center().X) <
		math.Abs(pb.Team().ControllingPlayer().Pos().X-pb.Team().OpponentsGoal().Center().X)

}
func (pb *PlayerBase) AtTarget() bool {
	return pb.Pos().DistanceSq(pb.Steering().Target()) < pb.ctx.Config().PlayerInTargetRangeSq
}
func (pb *PlayerBase) IsClosestTeamMemberToBall() bool {
	return pb.Team().PlayerClosestToBall() == pb
}

//如果position在该玩家的视野范围内，则返回true
func (pb *PlayerBase) PositionInFrontOfPlayer(position Vector2d) bool {
	var toSubject Vector2d = position.OpMinus(pb.Pos())
	if toSubject.Dot(pb.Heading()) > 0 {
		return true
	}
	return false
}
func (pb *PlayerBase) IsClosestPlayerOnPitchToBall() bool {
	return pb.IsClosestTeamMemberToBall() &&
		pb.DistSqToBall() < pb.Team().OpponentsTeam().ClosestDistToBallSq()
}
func (pb *PlayerBase) IsControllingPlayer() bool {
	return pb.Team().GetControllingPlayer() == pb
}
func (pb *PlayerBase) InHotRegion() bool {
	return math.Abs(pb.Pos().Y-pb.Team().OpponentsGoal().Center().y) <
		pb.Pitch().PlayingArea().Length()/3.0
}
func (pb *PlayerBase) Role() RoleType {
	return pb.role
}
func (pb *PlayerBase) DistSqToBall() float64 {
	return pb.distSqToBall
}
func (pb *PlayerBase) SetDistSqToBall(val float64) {
	pb.distSqToBall = val
}
func (pb *PlayerBase) DistToOppGoal() float64 {
	return math.Abs(pb.Pos().X - pb.Team().OpponentsGoal().Center().X)
}
func (pb *PlayerBase) DistToHomeGoal() float64 {
	return math.Abs(pb.Pos().X - pb.Team().HomeGoal().Center().X)
}
func (pb *PlayerBase) SetDefaultHomeRegion() {
	pb.homeRegion = pb.defaultRegion
}
func (pb *PlayerBase) HomeRegion() *Region {
}
func (pb *PlayerBase) SetHomeRegion(val int) {
	pb.homeRegion = val
}
func (pb *PlayerBase) Ball() *SoccerBall {
	return pb.Patch().Ball()
}
func (pb *PlayerBase) Pitch() *SoccerPitch {
	return pb.Team().Patch()
}
func (pb *PlayerBase) Steering() *SteeringBehaviors {
	return pb.steering
}
func (pb *PlayerBase) Team() *SoccerTeam {
	return team
}

func (pb *PlayerBase) Ctx() *SoccerContext {
	return pb.ctx
}
