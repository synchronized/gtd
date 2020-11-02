package main

import (
	"fmt"
	"math/rand"
	"simple_soccer/common"
)

var (
	StateGlobalPlayerState  common.IState
	StateChaseBall          common.IState
	StateDribble            common.IState
	StateReturnToHomeRegion common.IState
	StateWait               common.IState
	StateKickBall           common.IState
	StateReceiveBall        common.IState
	StateSupportAttacker    common.IState
)

func init() {
	StateGlobalPlayerState = NewGlobalPlayerState()
	StateChaseBall = NewPlayerStateChaseBall()
	StateDribble = NewPlayerStateDribble()
	StateReturnToHomeRegion = NewPlayerStateReturnToHomeRegion()
	StateWait = NewPlayerStateWait()
	StateKickBall = NewPlayerStateKickBall()
	StateReceiveBall = NewPlayerStateReceiveBall()
	StateSupportAttacker = NewPlayerStateSupportAttacker()
}

//----------------------------------------------------
//全局状态
type GlobalPlayerState struct {
	common.State
}

func NewGlobalPlayerState() *GlobalPlayerState {
	return &GlobalPlayerState{}
}

func (psg *GlobalPlayerState) Enter(entity interface{}) {}

func (psg *GlobalPlayerState) Execute(entity interface{}) {
	var player = entity.(*FieldPlayer)
	if player.BallWithinReceivingRange() && player.IsControllingPlayer() {
		player.SetMaxSpeed(player.Ctx().Config().PlayerMaxSpeedWithBall)
	} else {
		player.SetMaxSpeed(player.Ctx().Config().PlayerMaxSpeedWithoutBall)
	}
}

func (psg *GlobalPlayerState) Exit(entity interface{}) {}

func (psg *GlobalPlayerState) OnMessage(entity interface{}, msg *common.Telegram) bool {
	var player = entity.(*FieldPlayer)
	switch msg.Msg {
	case Msg_ReceiveBall:
		//设置目标
		var target = msg.ExtraInfo.(*common.Vector2d)
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
		Debug_Message(player.Ctx(), fmt.Sprintf(
			"Player [%d] received request form [%d] to make pass", player.Id(), receiver.Id()))

		//如果球不在射程内或已经是接球球员，则该球员不能将球传给提出请求的球员。
		if player.Team().Receiving() != nil || !player.BallWithinKickingRange() {
			Debug_Message(player.Ctx(), fmt.Sprintf(
				"Player [%d] cannot make requested pass <cannot kick ball>", player.Id()))
			return true
		}
		//传球
		player.Ball().Kick(*receiver.Pos().OpMinus(player.Ball().Pos()),
			player.Ctx().Config().MaxPassingForce)

		Debug_Message(player.Ctx(), fmt.Sprintf("Player [%d] Passed ball to requesting player", player.Id()))

		player.Ctx().Dispatcher().DispatchMsg(SEND_MSG_IMMEDIATELY,
			player.Id(),
			receiver.Id(),
			Msg_ReceiveBall,
			receiver.Pos())

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
	Debug_State(player.Ctx(), "Player [%d] enters [追逐球]")
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
		player.Steering().SetTarget(*player.Ball().Pos())
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

func (psd *PlayerStateDribble) Enter(entity interface{}) {
	var player = entity.(*FieldPlayer)
	//let the team know this player is controlling
	//让team知道当前球员是控球者
	player.Team().SetControllingPlayer(player)
	Debug_State(player.Ctx(), "Player [%d] enters dribble state[运球]", player.Id())
}

func (psd *PlayerStateDribble) Execute(entity interface{}) {
	var player = entity.(*FieldPlayer)
	var dot float64 = player.Team().HomeGoal().Facing().Dot(player.Heading())
	//if the ball is between the player and the home goal, it needs to swivel
	// the ball around by doing multiple small kicks and turns until the player
	//is facing in the correct direction
	//如果球在球员和主球之间，
	//它需要通过多次小踢和转身来旋转球，
	//直到球员朝向正确的方向
	if dot < 0 {
		//the player's heading is going to be rotated by a small amount (Pi/4)
		//and then the ball will be kicked in that direction
		//球员的头球将被旋转一小部分（π/4），然后球将被踢向那个方向
		var direction common.Vector2d = *player.Heading()

		//calculate the sign (+/-) of the angle between the player heading and the
		//facing direction of the goal so that the player rotates around in the
		//correct direction
		//计算球员头球和球门朝向之间角度的符号（+/-），使球员以正确的方向旋转
		var angle float64 = common.QuarterPi * -1 *
			float64(player.Team().HomeGoal().Facing().Sign(player.Heading()))

		common.Vec2DRotateAroundOrigin(direction, angle)

		//this value works well whjen the player is attempting to control the
		//ball and turn at the same time
		//当球员试图控制球并同时转身时，这个值很有效
		var KickingForce float64 = 0.8

		player.Ball().Kick(direction, KickingForce)
	} else {
		//kick the ball down the field
		player.Ball().Kick(*player.Team().HomeGoal().Facing(),
			player.Ctx().Config().MaxDribbleForce)
	}

	//the player has kicked the ball so he must now change state to follow it
	//球员踢了球，所以现在必须改变状态才能跟上
	player.GetFSM().ChangeState(StateChaseBall)

	return
}

func (psd *PlayerStateDribble) Exit(entity interface{}) {}

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
	if player.HomeRegion().Inside(*player.Steering().Target(), Region_Halfsize) {
		player.Steering().SetTarget(*player.HomeRegion().Center())
	}

	Debug_State(player.Ctx(), "Player [%d] enters [返回HomeRegion]", player.Id())
}

func (psr *PlayerStateReturnToHomeRegion) Execute(entity interface{}) {
	var player = entity.(*FieldPlayer)
	if player.Pitch().IsGameOn() {
		//if the ball is nearer this player than any other team member  &&
		//there is not an assigned receiver && the goalkeeper does not gave
		//the ball, go chase it
		//如果球比其他队员更接近这个队员&&
		//没有指定的接球手&&守门员没有给球，去追它
		if player.IsClosestTeamMemberToBall() &&
			player.Team().Receiving() == nil &&
			!player.Pitch().IsGoalKeeperHasBall() {
			player.GetFSM().ChangeState(StateChaseBall)
			return
		}
	}

	//if game is on and close enough to home, change state to wait and set the
	//player target to his current position.(so that if he gets jostled out of
	//position he can move back to it)
	//如果游戏接近并接近主场，改变状态以等待并将球员目标设定到他的当前位置。
	if player.Pitch().IsGameOn() && player.HomeRegion().Inside(*player.Pos(), Region_Halfsize) {
		player.Steering().SetTarget(*player.Pos())
		player.GetFSM().ChangeState(StateWait)
	} else if !player.Pitch().IsGameOn() && player.AtTarget() {
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
	Debug_State(player.Ctx(), "Player [%d] enters wait state[等待]", player.Id())
	if !player.Pitch().IsGameOn() {
		player.Steering().SetTarget(*player.HomeRegion().Center())
	}
}

func (psw *PlayerStateWait) Execute(entity interface{}) {
	var player = entity.(*FieldPlayer)
	if player.AtTarget() {
		player.Steering().ArriveOn()
		return
	} else {
		player.Steering().ArriveOff()
		player.SetVelocity(common.Vector2d{0, 0})
		//运动员应该注意球！
		player.TrackBall()
	}

	//if this player's team is controlling AND this player is not the attacker
	//AND is further up the field than the attacker he should request a pass.
	//如果这名球员的球队正在控制，而这名球员不是进攻者，并且比进攻者更高，他应该请求传球。
	if player.Team().InControl() &&
		!player.IsControllingPlayer() &&
		player.IsAheadOfAttacker() {
		player.Team().RequestPass(player)
		return
	}

	if player.Pitch().IsGameOn() {
		//if the ball is nearer this player than any other team member  AND
		//there is not an assigned receiver AND neither goalkeeper has
		//the ball, go chase it
		//如果球比其他队员近，而且没有指定的接球手，守门员也没有球，就追它
		if player.IsClosestTeamMemberToBall() &&
			player.Team().Receiving() == nil &&
			!player.Pitch().IsGoalKeeperHasBall() {
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

	Debug_State(player.Ctx(), "Player [%d] enters kick state[踢球]", player.Id())
}

func (psk *PlayerStateKickBall) Execute(entity interface{}) {
	var player = entity.(*FieldPlayer)
	//calculate the dot product of the vector pointing to the ball
	//and the player's heading
	//计算玩家与球位置的点和玩家朝向的点积
	var toBall common.Vector2d = *player.Pos().OpMinus(player.Ball().Pos())
	var dot float64 = player.Heading().Dot(toBall.Normalize())

	//cannot kick the ball if the goalkeeper is in possession or if it is
	//behind the player or if there is already an assigned receiver. So just
	//continue chasing the ball
	//如果守门员控球，或者球在球员身后，
	//或者已经有指定的接球员，则不能踢球。所以继续追球
	if player.Team().Receiving() != nil ||
		player.Pitch().IsGoalKeeperHasBall() ||
		dot < 0 {
		Debug_State(player.Ctx(), "Goaly has ball / ball behind player")
		player.GetFSM().ChangeState(StateChaseBall)
		return
	}
	/* 尝试射门 */

	//if a shot is possible, this vector will hold the position along the
	//opponent's goal line the player should aim for.
	//如果一次射门是可能的，这个向量将保持球员应该瞄准的对手的球门线上的位置
	var ballTarget common.Vector2d

	//the dot product is used to adjust the shooting force. The more
	//directly the ball is ahead, the more forceful the kick
	//点积用于调整射击力。球越直，踢得越有力
	var power float64 = dot * player.Ctx().Config().MaxShootingForce

	//if it is determined that the player could score a goal from this position
	//OR if he should just kick the ball anyway, the player will attempt
	//to make the shot
	//如果确定球员可以从这个位置进一球，或者他应该踢这个球，那么球员将尝试射门
	var ok bool
	ok, ballTarget = player.Team().CanShoot(*player.Ball().Pos(), power)
	if ok || rand.Float64() < player.Ctx().Config().ChancePlayerAttemptsPotShot {
		Debug_State(player.Ctx(), "player [%d] attempts a shot at [%d, %d]",
			player.Id(), ballTarget.X, ballTarget.Y)

		//add some noise to the kick. We don't want players who are
		//too accurate! The amount of noise can be adjusted by altering
		//Prm.PlayerKickingAccuracy
		//给踢腿加些噪音。我们不想要太精确的球员！可以通过改变 config.PlayerKickingAccuracy来调节噪声量。
		ballTarget = AddNoiseToKick(player.Ctx(), *player.Ball().Pos(), ballTarget)

		//this is the direction the ball will be kicked in
		//这是踢球的方向
		var kickDirection common.Vector2d = *ballTarget.OpMinus(player.Ball().Pos())
		player.Ball().Kick(kickDirection, power)

		//change state
		player.GetFSM().ChangeState(StateWait)
		player.FindSupport()
		return
	}

	/* Attempt a pass to a player */
	/* 传球 */

	//if a receiver is found this will point to it
	//这个记录找到的传球 球员
	var receiver IPlayerBase
	power = player.Ctx().Config().MaxPassingForce * dot

	//test if there are any potential candidates available to receive a pass
	//测试是否有任何潜在候选球员可以接受传球
	var isFind bool
	isFind, receiver, ballTarget = player.Team().FindPass(player, power, player.Ctx().Config().MinPassDist)
	if player.IsThreatened() && isFind {
		//添加一些噪声
		ballTarget = AddNoiseToKick(player.Ctx(), *player.Ball().Pos(), ballTarget)
		var kickDirection common.Vector2d = *ballTarget.OpMinus(player.Ball().Pos())

		player.Ball().Kick(kickDirection, power)

		Debug_State(player.Ctx(), "Player [%d] passes the ball with force [%f] to player [%d] Target is [%f, %f]",
			player.Id(), power, receiver.Id(), ballTarget.X, ballTarget.Y)

		//let the receiver know a pass is coming
		//让传球者知道
		player.Ctx().Dispatcher().DispatchMsg(SEND_MSG_IMMEDIATELY,
			player.Id(),
			receiver.Id(),
			Msg_ReceiveBall,
			&ballTarget)

		//the player should wait at his current position unless instruced
		//otherwise
		//球员应该等待在当前的位置,除非移动了
		player.GetFSM().ChangeState(StateWait)
		player.FindSupport()
		return
	} else {
		//cannot shoot or pass, so dribble the ball upfield
		//不能射门,就向对方球门运球
		player.FindSupport()

		player.GetFSM().ChangeState(StateDribble)
	}
}

func (psk *PlayerStateKickBall) Exit(entity interface{}) {}

//----------------------------------------------------
//接球
type PlayerStateReceiveBall struct {
	common.State
}

func NewPlayerStateReceiveBall() *PlayerStateReceiveBall {
	return &PlayerStateReceiveBall{}
}

func (psk *PlayerStateReceiveBall) Enter(entity interface{}) {
	var player = entity.(*FieldPlayer)
	//let the team know this player is receiving the ball
	//通知Team 当前球员开始 接球
	player.Team().SetReceiving(player)
	//this player is also now the controlling player
	//同时当前球员也是控球员
	player.Team().SetControllingPlayer(player)

	//there are two types of receive behavior. One uses arrive to direct
	//the receiver to the position sent by the passer in its telegram. The
	//other uses the pursuit behavior to pursue the ball.
	//This statement selects between them dependent on the probability
	//ChanceOfUsingArriveTypeReceiveBehavior, whether or not an opposing
	//player is close to the receiving player, and whether or not the receiving
	//player is in the opponents 'hot region' (the third of the pitch closest
	//to the opponent's goal
	//有两种类型的接收行为。
	//一种方法 是直接吧接收者的位置通过传球消息发送。
	//另一种是利用追球行为来追球。
	//这句话根据不同的概率来选择他们之间的关系。
	//无论对方球员是否靠近对方球员，
	//以及接球球员是否在对方的“热区”（距离对方球门最近的球场的三分之一)
	var passThreatRadius float64 = 70.0

	if player.InHotRegion() ||
		rand.Float64() < player.Ctx().Config().ChanceOfUsingArriveTypeReceiveBehavior &&
			!player.Team().IsOpponentWithinRadius(*player.Pos(), passThreatRadius) {
		player.Steering().ArriveOn()

		Debug_State(player.Ctx(), "Player [%d] enters receive state (Using Arrive)", player.Id())

	} else {
		player.Steering().PursuitOn()
		Debug_State(player.Ctx(), "Player [%d] enters receive state (Using Pursuit)", player.Id())
	}
}

func (psk *PlayerStateReceiveBall) Execute(entity interface{}) {
	var player = entity.(*FieldPlayer)
	//if the ball comes close enough to the player or if his team lose control
	//he should change state to chase the ball
	//如果球离球员足够近或者他的球队失去控制，他应该改变状态去追球
	if player.BallWithinReceivingRange() || !player.Team().InControl() {
		player.GetFSM().ChangeState(StateChaseBall)
		return
	}
	if player.Steering().PursuitIsOn() {
		player.Steering().SetTarget(*player.Ball().Pos())
	}

	//if the player has 'arrived' at the steering target he should wait and
	//turn to face the ball
	//如果球员已经到达了steering目标，他应该等待并转身面对球
	if player.AtTarget() {
		player.Steering().ArriveOff()
		player.Steering().PursuitOff()
		player.TrackBall()
		player.SetVelocity(common.Vector2d{0, 0})
	}

}

func (psk *PlayerStateReceiveBall) Exit(entity interface{}) {
	var player = entity.(*FieldPlayer)
	player.Steering().ArriveOff()
	player.Steering().PursuitOff()
	player.Team().SetReceiving(nil)
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

	Debug_State(player.Ctx(), "Player [%d] enters [助攻]", player.Id())
}

func (pss *PlayerStateSupportAttacker) Execute(entity interface{}) {
	//if his team loses control go back home
	var player = entity.(*FieldPlayer)
	if !player.Team().InControl() {
		player.GetFSM().ChangeState(StateReturnToHomeRegion)
	}

	//if the best supporting spot changes, change the steering target
	var supportSpot = player.Team().GetSupportSpot()
	if supportSpot.OpEqual(player.Steering().Target()) {
		player.Steering().SetTarget(player.Team().GetSupportSpot())
		player.Steering().ArriveOn()
	}

	//if this player has a shot at the goal AND the attacker can pass
	//the ball to him the attacker should pass the ball to this player
	//如果这个球员可以射门得分，攻击者也可以把球传给他，
	//攻击者就应该把球传给这个球员。
	var ok, _ = player.Team().CanShoot(*player.Pos(), player.Ctx().Config().MaxShootingForce)
	if ok {
		player.Team().RequestPass(player)
	}

	//if this player is located at the support spot and his team still have
	//possession, he should remain still and turn to face the ball
	//如果这名球员位于支撑点，他的球队仍然拥有控球权，他应该保持静止并转身面对球
	if player.AtTarget() {
		player.Steering().ArriveOff()
		//the player should keep his eyes on the ball!
		//运动员应该注意球！,把球的脸指向球
		player.TrackBall()
		player.SetVelocity(common.Vector2d{0, 0})

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
