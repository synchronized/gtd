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

func (gks *GlobalKeeperState) OnMessage(entity interface{}, msg *Telegram) {
	var keeper = entity.(*GoalKeeper)
	switch msg.Msg {
	case Msg_GoHome:
		keeper.SetDefaultHomeRegion()
		keeper.GetFSM().ChangeState(StateReturnHome)
	case Msg_ReceiveBall:
		keeper.GetFSM().ChangeState(StateInterceptBall)
	}
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
	var keeper = entity.(*GoalKeeper)
}

//---------------------------------------------------------
//守门员拦截球
type KeeperStateInterceptBall struct {
	common.IState
}

func NewKeeperStateInterceptBall() *KeeperStateInterceptBall {
	return &KeeperStateInterceptBall{}
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
