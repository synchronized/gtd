package main

import (
	"fmt"
	"simple_soccer/common"
)

var StateWait common.IState
var StateChaseBall common.IState
var StateDribble common.IState
var StateReturnToHomeRegion common.IState
var StateWait common.IState
var StateKickBall common.IState
var StateReceiveBall common.IState
var StateSupportAttacker common.IState

func init() {
	StateWait = NewPlayerStateWait()
	StateChaseBall = NewPlayerStateChaseBall()
	StateDribble = NewPlayerStateDribble()
	StateReturnToHomeRegion = NewPlayerStateReturnToHomeRegion()
	StateWait = NewPlayerStateWait()
	StateKickBall = NewPlayerStateKickBall()
	StateReceiveBall = NewPlayerStateReceiveBall()
	StateSupportAttacker = NewPlayerStateSupportAttacker()
}

//----------------------------------------------------
//角色等待
type PlayerStateWait struct {
	common.State
}

func NewPlayerStateWait() *PlayerStateWait {
	return &PlayerStateWait{}
}

func (psw *PlayerStateWait) Execute(entity interface{}) {
	var player = entity.(*FieldPlayer)
	if player.BallWithinReceivingRange() && player.IsControllingPlayer() {
		player.SetMaxSpeed(player.Ctx().Config().PlayerMaxSpeedWithBall)
	} else {
		player.SetMaxSpeed(player.Ctx().Config().PlayerMaxSpeedWithoutBall)
	}
}

func (psw *PlayerStateWait) OnMessage(entity interface{}, msg *common.Telegram) {
	var player = entity.(*FieldPlayer)
	switch msg.Msg {
	case Msg_ReceiveBall:
		//设置目标
		var target = msg.ExtraInfo(*Vector2d)
		player.Steering().SetTarget(*target)
		//改变状态
		player.GetFSM().ChangeState(StateReceiveBall)
		return true
	case Msg_SupportAttacker:
		//如果已经是助攻状态
		if player.GetFSM().IsInState(StateSupportAttacker) {
			return true
		}
		//设置目标到最佳助攻位置
		player.Steering().SetTarget(player.Team().GetSupportSpot())
		//改变状态
		player.GetFSM().ChangeState(StateSupportAttacker)
		return true
	case Msg_Wait:
		player.GetFSM().ChangeState(StateWait)
		return true
	case Msg_GoHome:
		player.GetFSM().ChangeState(StateReturnToHomeRegion)
		return true
	case Msg_PassToMe:
		var receiver = msg.ExtraInfo.(*FieldPlayer)
		Debug_Message(fmt.Sprintf(
			"Player [%d] received request form [%d] to make pass", player.Id(), receiver.Id()))

		//如果球不在射程内或已经是接球球员，则该球员不能将球传给提出请求的球员。
		if player.Team().Receiver() != nil || !player.BallWithinKickingRange() {
			Debug_Message(fmt.Sprintf(
				"Player [%d] cannot make requested pass <cannot kick ball>", player.Id()))
			return true
		}
		//传球
		player.Ball().Kick(receiver.Pos().OpMinus(player.Ball().Pos()),
			player.Ctx().Config().MaxPassingForce)

		Debug_Message(fmt.Sprintf("Player [%d] Passed ball to requesting player", player.Id()))

		player.Ctx().Dispatcher().DispatchMsg(SEND_MSG_IMMEDIATELY,
			player.Id(),
			receiver.Id(),
			Msg_ReceiveBall,
			&receiver.Pos())

		player.GetFSM().ChangeState(StateWait)
		player.FindSupport()
		return true
	}
	return false
}

//----------------------------------------------------
//追逐球
type PlayerStateChaseBall struct {
	common.State
}

func NewPlayerStateChaseBall() *PlayerStateChaseBall {
	return &PlayerStateChaseBall{}
}

func (psc *PlayerStateChaseBall) Enter(entity interface{}) {
	var player = entity.(*FieldPlayer)
	player.Steering().SeekOn()
	Debug_State("Player [%d] enters [追逐球]")
}

func (psc *PlayerStateChaseBall) Execute(entity interface{}) {
	var player = entity.(*FieldPlayer)
	//如果球在踢球范围内，球员将状态更改为踢球(StateKickBall)。
	if player.BallWithinKickingRange() {
		player.GetFSM().ChangeState(StateKickBall)
		return
	}

	//如果球员是离球最近的球员，他应该继续追球
	if player.IsClosestTeamMemberToBall() {
		player.Steering().SetTarget(player.Ball().Pos())
		return
	}

	//如果球员不再离球最近，他应该回到自己的homeRegion，等待另一个机会
	player.GetFSM().ChangeState(StateReturnToHomeRegion)
}

func (psc *PlayerStateChaseBall) Exit(entity interface{}) {
	var player = entity.(*FieldPlayer)
	player.Steering().SeekOff()
}

//----------------------------------------------------
//Dribble 运球
type PlayerStateDribble struct {
	common.State
}

func NewPlayerStateDribble() *PlayerStateDribble {
	return &PlayerStateDribble{}
}

//----------------------------------------------------
//返回默认位置
type PlayerStateReturnToHomeRegion struct {
	common.State
}

func NewPlayerStateReturnToHomeRegion() *PlayerStateReturnToHomeRegion {
	return &PlayerStateReturnToHomeRegion{}
}

func (psr *PlayerStateReturnToHomeRegion) Enter(entity interface{}) {
	var player = entity.(*FieldPlayer)
	player.Steering().ArriveOn()
	if player.HomeRegion().Inside(player.Steering().Target(), Region_Halfsize) {
		player.Steering().SetTarget(player.HomeRegion().Center())
	}

	Debug_State("Player [%d] enters [返回HomeRegion]", player.Id())
}

func (psr *PlayerStateReturnToHomeRegion) Execute(entity interface{}) {
	var player = entity.(*FieldPlayer)
	if player.Pitch().GameOn() {
		//if the ball is nearer this player than any other team member  &&
		//there is not an assigned receiver && the goalkeeper does not gave
		//the ball, go chase it
		//如果球比其他队员更接近这个队员&&
		//没有指定的接球手&&守门员没有给球，去追它
		if player.IsClosestTeamMemberToBall() &&
			player.Team().Receiver() == nil &&
			!player.Pitch().GoalKeeperHasBall() {
			player.GetFSM().ChangeState(StateChseBall)
			return
		}
	}

	//if game is on and close enough to home, change state to wait and set the
	//player target to his current position.(so that if he gets jostled out of
	//position he can move back to it)
	//如果游戏接近并接近主场，改变状态以等待并将球员目标设定到他的当前位置。
	if player.Pitch().GameOn() && player.HomeRegion().Inside(Player.Pos(), Region_Halfsize) {
		player.Steering().SetTarget(player.Pos())
		player.GetFSM().ChangeState(StateWait)
	} else if !player.Pitch().GameOn() && player.AtTarget() {
		//if game is not on the player must return much closer to the center of his
		//home region
		//如果游戏不在游戏中，玩家必须回到离他homeRegion中心更近的地方
		player.GetFSM().ChangeState(StateWait)
	}

}

func (psr *PlayerStateReturnToHomeRegion) Exit(entity interface{}) {
	var player = entity.(*FieldPlayer)
	player.Steering().ArriveOff()
}

//----------------------------------------------------
//等待
type PlayerStateWait struct {
	common.State
}

func NewPlayerStateWait() *PlayerStateWait {
	return &PlayerStateWait{}
}

func (psw *PlayerStateWait) Enter(entity interface{}) {
	var player = entity.(*FieldPlayer)
	Debug_State("Player [%d] enters wait state[等待]", player.Id())
	if !player.Patch().GameOn() {
		player.Steering().SetTarget(player.HomeRegion().Center())
	}
}

func (psw *PlayerStateWait) Execute(entity interface{}) {
	var player = entity.(*FieldPlayer)
	if player.AtTarget() {
		player.Steering().ArriveOn()
		return
	} else {
		player.Steering().ArriveOff()
		player.SetVelocity(Vector2d{0, 0})
		//运动员应该注意球！
		player.TrackBall()
	}

	//if this player's team is controlling AND this player is not the attacker
	//AND is further up the field than the attacker he should request a pass.
	//如果这名球员的球队正在控制，而这名球员不是进攻者，并且比进攻者更高，他应该请求传球。
	if player.Team().InControl() &&
		!player.IsControllingPlayer() &&
		player.IsAheadofAttacker() {
		player.Team().RequestPass(player)
		return
	}

	if player.Patch().GameOn() {
		//if the ball is nearer this player than any other team member  AND
		//there is not an assigned receiver AND neither goalkeeper has
		//the ball, go chase it
		//如果球比其他队员近，而且没有指定的接球手，守门员也没有球，就追它
		if player.IsClosestTeamMemberToBall() &&
			player.Team().Receiver() == nil &&
			!player.Patch().GoalKeeperHasBall() {
			player.GetFSM().ChangeState(StateChaseBall)
		}
	}
}

func (psw *PlayerStateWait) Exit(entity interface{}) {}

//----------------------------------------------------
//踢球
type PlayerStateKickBall struct {
	common.State
}

func NewPlayerStateKickBall() *PlayerStateKickBall {
	return &PlayerStateKickBall{}
}

func (psk *PlayerStateKickBall) Enter(entity interface{}) {
	var player = entity.(*FieldPlayer)
	//let the team know this player is controlling
	player.Team().SetControllingPlayer(player)

	//the player can only make so many kick attempts per second.
	if !player.IsReadyForNextKick() {
		player.GetFSM().ChangeState(StateChaseBall)
	}

	Debug_State("Player [%d] enters kick state[踢球]", player.Id())
}

func (psk *PlayerStateKickBall) Enter(entity interface{}) {
	var player = entity.(*FieldPlayer)
	//calculate the dot product of the vector pointing to the ball
	//and the player's heading
	var toBall Vector2d = player.Pos().OpMinus(player.Ball().Pos())
	var dot float64 = player.Heading().Dot(*toBall.Normalize())
}

//----------------------------------------------------
//接球
type PlayerStateReceiveBall struct {
	common.State
}

func NewPlayerStateReceiveBall() *PlayerStateReceiveBall {
	return &PlayerStateReceiveBall{}
}

//----------------------------------------------------
//助攻
type PlayerStateSupportAttacker struct {
	common.State
}

func NewPlayerStateSupportAttacker() *PlayerStateSupportAttacker {
	return &PlayerStateSupportAttacker{}
}

func (pss *PlayerStateSupportAttacker) Enter(entity interface{}) {
	var player = entity.(*FieldPlayer)
	player.Steering().ArriveOn()
	player.Steering().SetTarget(player.Team().GetSupportSpot())

	Debug_State("Player [%d] enters [助攻]", player.Id())
}

func (pss *PlayerStateSupportAttacker) Execute(entity interface{}) {
	//if his team loses control go back home
	var player = entity.(*FieldPlayer)
	if !player.Team().InControl() {
		player.GetFSM().ChangeState(StateReturnToHomeRegion)
	}

	//if the best supporting spot changes, change the steering target
	if player.Team().GetSupportSpot() != player.Steering().Target() {
		player.Steering().SetTarget(player.Team().GetSupportSpot())
		player.Steering().ArriveOn()
	}

	//if this player has a shot at the goal AND the attacker can pass
	//the ball to him the attacker should pass the ball to this player
	//如果这个球员可以射门得分，攻击者也可以把球传给他，
	//攻击者就应该把球传给这个球员。
	if player.Team().CanShoot(player.Pos(), player.Ctx().Config().MaxShootingForce) {
		player.Team().RequestPass(player)
	}

	//if this player is located at the support spot and his team still have
	//possession, he should remain still and turn to face the ball
	//如果这名球员位于支撑点，他的球队仍然拥有控球权，他应该保持静止并转身面对球
	if player.AtTarget() {
		player.Steering().ArriveOff()
		//the player should keep his eyes on the ball!
		//运动员应该注意球！,把球的脸指向球
		player.TrackBack()
		oplayer.SetVelocity(Vector2d{0, 0})

		//if not threatened by another player request a pass
		//如果没有受到其他玩家的威胁，请求传球
		if player.IsThreatened() {
			player.Team().RequestPass(player)
		}
	}
}

func (pss *PlayerStateSupportAttacker) Exit(entity interface{}) {
	//set supporting player to null so that the team knows it has to
	//determine a new one.
	//将辅助玩家设置为空，以便团队知道必须确定新的玩家。
	var player = entity.(*FieldPlayer)
	player.Team().SetSupportingPlayer(nil)
	player.Steering().ArriveOff()
}
