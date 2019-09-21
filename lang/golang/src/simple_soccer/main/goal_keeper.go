package main

import "simple_soccer/common"

//守门员
type GoalKeeper struct {
	*PlayerBase
	pStateMachine *StateMachine
	vLookAt       Vector2d
}

func NewGoalKeeper(
	ctx *ScooerContext,
	homeTeam *SoccerTeam,
	homeRegion int,
	startState common.IState,
	heading, velocity Vectory2d,
	mass, maxForce, maxSpeed, maxTurnRate, scale float64,
) *GoalKeeper {
	var gk = &GoalKeeper{
		PlayerBase: NewPlayerBase(
			ctx,
			homeTeam,
			homeRegion,
			heading, velocity,
			mass, maxForce, maxSpeed, maxTurnRate, scale,
			RoleType_Keeper,
		),
	}
	gk.pStateMachine = NewStateMachine(gk)
	gk.pStateMachine.SetCurrentState(startState)
	gk.pStateMachine.SetPreviousState(startState)
	gk.pStateMachine.SetGlobalState(GlobalKeeperState)

	gk.pStateMachine.CurrentState().Enter(gk)
	return gk
}

func (gk *GoalKeeper) LookAt() Vector2d {
	return gk.vLookAt
}

func (gk *GoalKeeper) SetLookAt(v Vector2d) {
	gk.vLookAt = v
}

func (gk *GoalKeeper) GetFSM() *StateMachine {
	return gk.pStateMachine
}

//returns true if the ball comes close enough for the keeper to
//consider intercepting
//如果球接近守门员考虑拦截，则返回true
func (gk *GoalKeeper) BallWithinRangeForIntercept() bool {
	var distBetweenBallAndGoal = gk.Team().HomeGoal().Center().DistanceSq(gk.Ball().Pos)
	return distBetweenBallAndGoal <= gk.Ctx().Config().GoalKeeperInterceptRangeSq
}

//returns true if the keeper has ventured too far away from the goalmouth
//如果守门员冒险离开球门太远，返回真值
func (gk *GoalKeeper) TooFarFromGoalMouth() bool {
	var distBetweenKeeperAndGoal = gk.Pos().DistanceSq(gk.Team().HomeGoal().Center())
	return distBetweenKeeperAndGoal >= gk.Ctx().Config().GoalKeeperInterceptRangeSq
}

//this method is called by the Intercept state to determine the spot
//along the goalmouth which will act as one of the interpose targets
//(the other is the ball).
//the specific point at the goal line that the keeper is trying to cover
//is flexible and can move depending on where the ball is on the field.
//To achieve this we just scale the ball's y value by the ratio of the
//goal width to playingfield width
// 这种方法被截获状态调用，以确定沿球门的位置，该位置将作为中间目标之一。
// （另一个是球）。
// 守门员试图覆盖的球门线上的特定点是灵活的，可以根据球在场地上的位置移动。
// 为了达到这个目的，我们只需通过球门宽度与球场宽度之比来缩放球的y值
func (gk *GoalKeeper) GetRearInterposeTarget() Vector2d {
	var xPosTarget float64 = gk.Team().HomeGoal().Center().X
	var goalWidth float64 = gk.Ctx().Config().GoalWidth
	var yPosTarget float64 = gk.Pitch().PlayingArea().Center().Y -
		goalWidth*0.5 + (gk.Ball().Pos().Y*goalWidth)/gk.Pitch().PlayingArea().Height()

	return Vector2d{xPosTarget, yPosTarget}
}
