package main

import "simple_soccer/common"

var StateGlobalKeeper common.IState
var StateTendGoal common.IState
var StateInterceptBall common.IState
var StateReturnHome common.IState
var StatePutBallBackInPlay common.IState

func init() {
	StateGlobalKeeper = NewGlobalKeeperState()
	StateTendGoal = NewKeeperStateTendGoal()
	StateInterceptBall = NewKeeperStateInterceptBall()
	StateReturnHome = NewKeeperStateReturnHome()
	StatePutBallBackInPlay = NewKeeperStatePutBallBackInPlay()
}

//---------------------------------------------------------
//守门员全局状态
type GlobalKeeperState struct {
	common.IState
}

func NewGlobalKeeperState() *GlobalKeeperState {
	return &GlobalKeeperState{}
}

func (gks *GlobalKeeperState) Enter(entity interface{})   {}
func (gks *GlobalKeeperState) Execute(entity interface{}) {}
func (gks *GlobalKeeperState) Exit(entity interface{})    {}

func (gks *GlobalKeeperState) OnMessage(entity interface{}, msg *common.Telegram) bool {
	var keeper = entity.(*GoalKeeper)
	switch msg.Msg {
	case Msg_GoHome:
		keeper.SetDefaultHomeRegion()
		keeper.GetFSM().ChangeState(StateReturnHome)
		return true
	case Msg_ReceiveBall:
		keeper.GetFSM().ChangeState(StateInterceptBall)
		return true
	}
	return false
}

//---------------------------------------------------------
//守门员,前往目标(对方进攻队员靠近球门)
type KeeperStateTendGoal struct {
	common.IState
}

func NewKeeperStateTendGoal() *KeeperStateTendGoal {
	return &KeeperStateTendGoal{}
}

func (kst *KeeperStateTendGoal) Enter(entity interface{}) {
	var keeper = entity.(*GoalKeeper)
	keeper.Steering().InterposeOn(keeper.Ctx().Config().GoalKeeperTendingDistance)
	//中间人将把探员定位在球位和目标之间
	//位于球门口的位置。此调用设置目标
	keeper.Steering().SetTarget(keeper.GetRearInterposeTarget())
}

func (kst *KeeperStateTendGoal) Execute(entity interface{}) {
	//var keeper = entity.(*GoalKeeper)
}

//---------------------------------------------------------
//守门员拦截球
type KeeperStateInterceptBall struct {
	common.IState
}

func NewKeeperStateInterceptBall() *KeeperStateInterceptBall {
	return &KeeperStateInterceptBall{}
}

func (ksi *KeeperStateInterceptBall) Enter(entity interface{}) {
	var keeper *GoalKeeper = entity.(*GoalKeeper)
	keeper.Steering().PursuitOn()

	Debug_State(keeper.Ctx(), "Goaly [%d] enters InterceptBall", keeper.Id())
}

func (ksi *KeeperStateInterceptBall) Execute(entity interface{}) {
	var keeper *GoalKeeper = entity.(*GoalKeeper)

	//if the goalkeeper moves to far away from the goal he should return to his
	//home region UNLESS he is the closest player to the ball, in which case,
	//he should keep trying to intercept it.
	//如果守门员移动到远离球门的地方，他应该回到自己的主场，
	//除非他是离球最近的球员，在这种情况下，他应该继续尝试拦截球。
	if keeper.TooFarFromGoalMouth() && !keeper.IsClosestPlayerOnPitchToBall() {
		keeper.GetFSM().ChangeState(StateReturnHome)
	}

	//if the ball becomes in range of the goalkeeper's hands he traps the
	//ball and puts it back in play
	//如果球落在守门员的手的射程内，他就把球截住，放回原处
	if keeper.BallWithinKeeperRange() {
		keeper.Ball().Trap()
		keeper.Pitch().SetGoalKeeperHasBall(true)
		keeper.GetFSM().ChangeState(StatePutBallBackInPlay)
		return
	}
}

func (ksi *KeeperStateInterceptBall) Exit(entity interface{}) {
	var keeper *GoalKeeper = entity.(*GoalKeeper)
	keeper.Steering().PursuitOff()
}

//---------------------------------------------------------
//返回球门
type KeeperStateReturnHome struct {
	common.IState
}

func NewKeeperStateReturnHome() *KeeperStateReturnHome {
	return &KeeperStateReturnHome{}
}

//---------------------------------------------------------
//守门员-发球
type KeeperStatePutBallBackInPlay struct {
	common.IState
}

func NewKeeperStatePutBallBackInPlay() *KeeperStatePutBallBackInPlay {
	return &KeeperStatePutBallBackInPlay{}
}

func (ksp *KeeperStatePutBallBackInPlay) Enter(entity interface{}) {
	var keeper *GoalKeeper = entity.(*GoalKeeper)

	//let the team know that the keeper is in control
	//让Team知道守门员控制了球
	keeper.Team().SetControllingPlayer(keeper)
	keeper.Team().Opponents().ReturnAllFieldPlayersToHome()
	keeper.Team().ReturnAllFieldPlayersToHome()
}

func (ksp *KeeperStatePutBallBackInPlay) Execute(entity interface{}) {
	var keeper *GoalKeeper = entity.(*GoalKeeper)
	var receiver IPlayerBase
	var ballTarget common.Vector2d

	//test if there are players further forward on the field we might
	//be able to pass to. If so, make a pass.
	//测试是否有球员在球场上更进一步，我们可能可以通过。如果是的话，传球。
	var ok bool
	ok, receiver, ballTarget = keeper.Team().FindPass(
		keeper,
		keeper.Ctx().Config().MaxPassingForce,
		keeper.Ctx().Config().GoalkeeperMinPassDist,
	)
	if ok {
		//传球
		keeper.Ball().Kick(*ballTarget.OpMinus(keeper.Ball().Pos()).Normalize(),
			keeper.Ctx().Config().MaxPassingForce)

		//goalkeeper no longer has ball
		//守门员
		keeper.Pitch().SetGoalKeeperHasBall(false)

		//let the receiving player know the ball's comin' at him
		//通知接球球员
		keeper.Ctx().Dispatcher().DispatchMsg(SEND_MSG_IMMEDIATELY,
			keeper.Id(),
			receiver.Id(),
			Msg_ReceiveBall,
			&ballTarget)

		//go back to tending the goal
		//返回tending状态
		keeper.GetFSM().ChangeState(StateTendGoal)
		return

	}
	keeper.SetVelocity(common.Vector2d{0, 0})
}
