package main

import (
	"math"
	"simple_soccer/common"
)

type FieldPlayer struct {
	*PlayerBase
	pStateMachine *StateMachine

	//限制玩家每秒可以踢的次数
	pKickLimiter *Regulator
}

func NewFieldPlayer(
	ctx *ScooerContext,
	homeTeam *SoccerTeam,
	homeRegion int,
	startState common.IState,
	heading, velocity common.Vector2d,
	mass, maxForce, maxSpeed, maxTurnRate, scale float64,
	role RoleType,
) *FieldPlayer {
	var fp = &NewFieldPlayer{
		PlayerBase: NewPlayerBase(
			ctx,
			homeTeam,
			homeRegion,
			heading, velocity,
			mass, maxForce, maxSpeed, maxTurnRate, scale,
			role,
		),
	}
	fp.pStateMachine = NewStateMachine(fp) //TODO

	if startState != nil {
		fp.pStateMachine.SetCurrentState(startSTate)
		fp.pStateMachine.SetPreviousState(startSTate)
		fp.pStateMachine.SetGlobalState(StateGlobalPlayerState)

		fp.pStateMachine.CurrentState().Enter(fp)
	}

	fp.pSteering.SeparationOn()
	fp.pKickLimiter = NewRegulator(fp.Ctx().Config().PlayerKickFrequency)
	return fp
}

func (fp *FieldPlayer) GetFSM() *StateMachine {
	return fp.pStateMachine
}

func (fp *FieldPlayer) IsReadyForNextKick() bool {
	return fp.pKickLimiter.IsReady()
}

func (fp *FieldPlayer) Update() {
	fp.pStateMachine.Update()
	fp.pSteering.Calculate()

	if fp.pSteering.Force().IsZero() {
		var breakingRate float64 = 0.8
		fp.SetVelocity(fp.Velocity().OpMultiply(breakingRate))
	}

	//转向力的侧边部分是一个力，它使球员绕其轴旋转。我们必须限制旋转角度，
	//这样玩家每次更新只能旋转最大PlayerMaxTurnRate
	var turningForce float64 = fp.pSteering.SideComponent()
	turningForce = math.Max(turningForce, -fp.Ctx().Config().PlayerMaxTurnRate)
	turningForce = math.Min(turningForce, fp.Ctx().Config().PlayerMaxTurnRate)
	//旋转heading向量
	fp.SetHeading(common.Vec2DRotateAroundOrigin(fp.Heading(), turningForce))

	fp.SetVelocity(fp.Heading().OpMultiply(fp.Velocity().Length()))

	//现在要计算由于转向力的前向分量在玩家前进方向上施加的力而产生的加速度
	var accel Vector2d = fp.Heading().OpMultiply(fp.pSteering.ForwardComponent() / fp.Mass())
	fp.SetVelocity(fp.Velocity().OpAdd(accel))
	fp.SetVelocity(fp.Velocity().Truncate(fp.MaxSpeed()))
	fp.SetPos(fp.Pos().OpAdd(fp.Velocity()))

	//如果需要，强制执行非穿透约束
	if fp.Ctx().Config().BNonPenetrationConstraint {
		var players = fp.Pitch().AllMembers()
		EnforceNonPenetrationContraint(this, players)
	}
}

func (fp *FieldPlayer) HandeMessage(msg *Telegram) {
	return fp.pStateMachine.HandleMessage(msg)
}

func (fp *FieldPlayer) Render() {
	/*TODO*/
}
