package main

import (
	"math"
	"math/rand"
	"simple_soccer/common"
)

type TeamColor int

const (
	TeamColor_Redk TeamColor = 1
	TeamColor_Blue TeamColor = 2
)

//球队
type SoccerTeam struct {
	ctx           *SoccerContext //上下文对象
	pStateMachine *StateMachine  //状态机
	color         TeamColor      //队伍颜色

	members        []*PlayerBase //队员
	pPitch         *SoccerPitch  //球场
	pOpponentsGoal *Goal         //对方球门
	pHomeGoal      *Goal         //己方球门
	pOpponentsTeam *SoccerTeam   //对方球队

	pReceivingPlayer     *PlayerBase //接球队员
	pPlayerClosestToBall *PlayerBase //离球最近的队员
	pControllingPlayer   *PlayerBase //控球队员
	pSupportingPlayer    *PlayerBase //接应球员

	dDistSqToBallOfClosestPlayer float64 //己方离球最近的球员于球的距离

	pSupportSpotCalc *SupportSpotCalculator //接应点计算
}

func NewSoccerTeam(
	ctx *SoccerContext,
	homeGoal,
	opponentsGoal Goal,
	pitch *SoccerPitch,
	color TeamColor,
) *SoccerTeam {
	var st = &SoccerTeam{
		ctx: ctx,

		pHomeGoal:      homeGoal,
		pOpponentsGoal: opponentsGoal,
		pPitch:         pitch,
		color:          color,
		pOpponentsTeam: nil,

		pReceivingPlayer:     nil, //接球队员
		pPlayerClosestToBall: nil, //离球最近的队员
		pControllingPlayer:   nil, //控球队员
		pSupportingPlayer:    nil, //接应球员

		dDistSqToBallOfClosestPlayer: 0.0,
	}

	st.pStateMachine = NewStateMachine(st)
	st.pStateMachine.SetCurrentState(StateDefending)
	st.pStateMachine.SetPreviousState(StateDefending)
	st.pStateMachine.SetGlobalState(nil)

	st.CreateMembers()
	for _, player := range st.members {
		player.Steering().SeparationOn()
	}
	return st
}

func (st *SoccerTeam) CreateMembers() {
	if st.Color() == blue {
		//goalkeeper
		st.members = append(st.members, NewGoalKeeper(this,
			1,
			StateTendGoal,
			Vector2D(0, 1),
			Vector2D(0.0, 0.0),
			st.ctx.Config().PlayerMass,
			st.ctx.Config().PlayerMaxForce,
			st.ctx.Config().PlayerMaxSpeedWithoutBall,
			st.ctx.Config().PlayerMaxTurnRate,
			st.ctx.Config().PlayerScale))

		//create the players
		st.members = append(st.members, NewFieldPlayer(this,
			6,
			StateWait,
			Vector2D(0, 1),
			Vector2D(0.0, 0.0),
			st.ctx.Config().PlayerMass,
			st.ctx.Config().PlayerMaxForce,
			st.ctx.Config().PlayerMaxSpeedWithoutBall,
			st.ctx.Config().PlayerMaxTurnRate,
			st.ctx.Config().PlayerScale,
			RoleType_Attacker))

		st.members = append(st.members, NewFieldPlayer(this,
			8,
			StateWait,
			Vector2D(0, 1),
			Vector2D(0.0, 0.0),
			st.ctx.Config().PlayerMass,
			st.ctx.Config().PlayerMaxForce,
			st.ctx.Config().PlayerMaxSpeedWithoutBall,
			st.ctx.Config().PlayerMaxTurnRate,
			st.ctx.Config().PlayerScale,
			RoleType_Attacker))

		st.members = append(st.members, NewFieldPlayer(this,
			3,
			StateWait,
			Vector2D(0, 1),
			Vector2D(0.0, 0.0),
			st.ctx.Config().PlayerMass,
			st.ctx.Config().PlayerMaxForce,
			st.ctx.Config().PlayerMaxSpeedWithoutBall,
			st.ctx.Config().PlayerMaxTurnRate,
			st.ctx.Config().PlayerScale,
			RoleType_Defender))

		st.members = append(st.members, NewFieldPlayer(this,
			5,
			StateWait,
			Vector2D(0, 1),
			Vector2D(0.0, 0.0),
			st.ctx.Config().PlayerMass,
			st.ctx.Config().PlayerMaxForce,
			st.ctx.Config().PlayerMaxSpeedWithoutBall,
			st.ctx.Config().PlayerMaxTurnRate,
			st.ctx.Config().PlayerScale,
			RoleType_Defender))

	} else {

		//goalkeeper
		st.members = append(st.members, NewGoalKeeper(this,
			16,
			StateTendGoal,
			Vector2D(0, -1),
			Vector2D(0.0, 0.0),
			st.ctx.Config().PlayerMass,
			st.ctx.Config().PlayerMaxForce,
			st.ctx.Config().PlayerMaxSpeedWithoutBall,
			st.ctx.Config().PlayerMaxTurnRate,
			st.ctx.Config().PlayerScale))

		//create the players
		st.members = append(st.members, NewFieldPlayer(this,
			9,
			StateWait,
			Vector2D(0, -1),
			Vector2D(0.0, 0.0),
			st.ctx.Config().PlayerMass,
			st.ctx.Config().PlayerMaxForce,
			st.ctx.Config().PlayerMaxSpeedWithoutBall,
			st.ctx.Config().PlayerMaxTurnRate,
			st.ctx.Config().PlayerScale,
			RoleType_Attacker))

		st.members = append(st.members, NewFieldPlayer(this,
			11,
			StateWait,
			Vector2D(0, -1),
			Vector2D(0.0, 0.0),
			st.ctx.Config().PlayerMass,
			st.ctx.Config().PlayerMaxForce,
			st.ctx.Config().PlayerMaxSpeedWithoutBall,
			st.ctx.Config().PlayerMaxTurnRate,
			st.ctx.Config().PlayerScale,
			RoleType_Attacker))

		st.members = append(st.members, NewFieldPlayer(this,
			12,
			StateWait,
			Vector2D(0, -1),
			Vector2D(0.0, 0.0),
			st.ctx.Config().PlayerMass,
			st.ctx.Config().PlayerMaxForce,
			st.ctx.Config().PlayerMaxSpeedWithoutBall,
			st.ctx.Config().PlayerMaxTurnRate,
			st.ctx.Config().PlayerScale,
			RoleType_Defender))

		st.members = append(st.members, NewFieldPlayer(this,
			14,
			StateWait,
			Vector2D(0, -1),
			Vector2D(0.0, 0.0),
			st.ctx.Config().PlayerMass,
			st.ctx.Config().PlayerMaxForce,
			st.ctx.Config().PlayerMaxSpeedWithoutBall,
			st.ctx.Config().PlayerMaxTurnRate,
			st.ctx.Config().PlayerScale,
			RoleType_Defender))

	}

	//register the players with the entity manager
	for _, player := range st.members {
		st.ctx.EntityMgr().RegisterEntity(player)
	}
}

func (st *SoccerTeam) CalculateClosestPlayerToBall() {
	var closestSoFar float64 = common.MaxFloat
	for _, player := range st.members {
		//计算玩家到球 距离的平方
		var dist float64 = player.Pos().DistanceSq(st.Patch().Ball().Pos())
		player.SetDistSqToBall(dist)
		if dist < closestSoFar {
			closestSoFar = dist
			st.PlayerClosestToBall = player
		}
	}

	st.dDistSqToBallOfClosestPlayer = closestSoFar
}

//向所有玩家发送信息，立即返回其home region
func (st *SoccerTeam) ReturnAllFieldPlayersToHome() {
	for _, player := range st.members {
		if player.Role != RoleType_Keeper {
			st.ctx.Dispatcher().DispatchMsg(
				MSG_SEND_MSG_IMMEDIATELY,
				1,
				player.Id(),
				Msg_GoHome,
				nil,
			)
		}
	}
}

/*
 * 给定一个球的位置，
 * 一个踢球的力量和一个参考common.Vector2d
 * 这个函数将沿着对手的球门随机抽样位置，
 * 并检查一个目标是否可以得分，如果球是在那个方向被踢与给定的力量。
 * 如果找到可能的子弹，
 * 函数将立即返回true，和 目标位置shottarget。
 *
 */
func (st *SoccerTeam) CanShoot(ballPos common.Vector2d, power float64) (ok bool, shotTarget common.Vector2d) {
	var numAttempts int = st.ctx.Config()().NumAttemptsToFindValidStrike
	for i := 0; i < numAttempts; i++ {
		shotTarget = st.pOpponentsGoal.Center()
		var minYVal float64 = st.pOpponentsGoal.LeftPost().Y + st.Pitch().Ball().BRadius()
		var maxYVal float64 = st.pOpponentsGoal.RightPost().Y - st.Pitch().Ball().BRadius()
		shotTarget.Y = rand.Float64()*(maxYVal-minYVal) + minYVal

		//确保用给定的力量击球足以使球越过球门线。
		var time float64 = st.Pitch().Ball().TimeToCoverDistance(ballPos, shotTarget, power)
		if time >= 0 {
			if st.isPassSafeFromAllOpponents(ballPos, shotTarget, nil, power) {
				return true
			}
		}
	}
	return false
}

/**
 * 最好的传球被认为是对手无法拦截的传球，并且尽可能地在接球手的前方
 * 如果找到一个pass，则在引用中返回接收方的地址，
 * “receiver”和传递的位置将返回到引用“passtarget”中
 */
func (st *SoccerTeam) FindPass(
	passer *PlayerBase,
	power float64,
	minPassingDistance float64,
) (canFind bool, receiver *PlayerBase, passTarget common.Vector2d) {
	var closestToGoalSoFar float64 = common.MaxFloat
	for _, player := range st.members {
		//传球者和本球员的距离
		//确保被检查的潜在接受者不是该球员，并且距离大于最小传球距离
		var dist float64 = passer.Pos().DistanceSq(player.Pos())
		if player != passer && dist > minPassingDistance*minPassingDistance {
			var ok, target = st.GetBestPassToReceiver(passer, player, power)
			if ok {
				//如果传球目标离对手的球门线最近，请记录
				var distToGoal float64 = math.Abs(passTarget.X - st.pOpponentsGoal.Center().X)
				if distToGoal < closestToGoalSoFar {
					closestToGoalSoFar = distToGoal

					//keep a record of this player
					receiver = player
					passTarget = target
				}
			}
		}
	} //next team member

	if receiver != nil {
		canFind = true
	} else {
		canFind = false
	}
	return
}

/**
 * 计算了三个势能传递。
 * 一个直接指向接收器的当前位置，两个是从球位置到接收器半径“范围”圆的切线。
 * 然后测试这些传球，看他们是否能被对手拦截，并确保他们在比赛区域内终止。
 * 如果所有传递都无效，则函数返回false。否则，函数返回将球带到最靠近对方球门区域的传球
 */
func (st *SoccerTeam) GetBestPassToReceiver(
	passer,
	receiver *PlayerBase,
	power float64,
) (ok bool, passTarget common.Vector2d) {
	//首先，计算如果接球者静止不动，球到达接球者所需的时间
	var time float64 = st.Pitch().Ball().TimeToCoverDistance(st.Patch().Ball().Pos(), receiver.Pos(), power)
	if time < 0 {
		return
	}
	// 此时接收者可以覆盖的最大距离
	var interceptRange = time * receiver.MaxSpeed()
	var scalingFactor float64 = 0.3
	interceptRange *= scalingFactor

	//现在计算传球目标，这些目标位于球到接球方射程圆切线的截距处。
	var ok, ip1, ip2 = common.GetTangentPoints(receiver.Pos(), interceptRange, st.Pitch().Ball().Pos())
	if !ok {
		//TODO 这里没有处理返回值(只有在半径为interceptRange的圆内才会返回false)
		//return
	}
	var numPassesToTry int = 3
	var passes = [numPassesToTry]common.Vector2d{ip1, receiver.Pos(), ip2}

	var closestSoFar float64 = common.MaxFloat
	for _, pass := range passes {
		var dist float64 = math.Abs(pass.X - st.OpponentsGoal().Center().X)
		var isPassSafeFromAll = st.isPassSafeFromAllOpponents(st.Patch().Ball().Pos(), pass, receiver, power)
		if dist < closestSoFar && st.Pitch().PlayerArea().Inside(pass) && isPassSafeFromAll {
			closestSoFar = dist
			passTarget = pass
			ok = true
		}
	}
	return
}

/**
 * 检测, 如果一个传球 从位置'from' 到 'target' 使用传球力的大小'passingForce'
 * 能否被对方的目标队员截获
 */
func (st *SoccerTeam) isPassSafeFromOpponent(
	from,
	target common.Vector2d,
	receiver,
	opp *PlayerBase,
	passingForce float64,
) bool {
	var toTarget common.Vector2d = *target.OpMinus(from)
	var ToTargetNormalized common.Vector2d = *toTarget.Normalize()

	var localPosOpp = common.PointToLocalSpace(
		opp.Pos(),
		toTargetNormalized,
		toTargetNormalized.Perp(),
		from,
	)
	//如果对方在踢球者后面，那么传球就被认为是可以的
	//（这是基于这样一个假设：球将以大于对方最大速度的速度被踢出）
	if localPosOpp.X < 0 {
		return true
	}

	//如果对手离目标较远，我们需要考虑对手是否能到达接受者之前的位置。
	if from.DistanceSq(target) < opp.Pos().DistanceSq(from) {
		if receiver == nil {
			return true
		}
		if target.DistanceSq(opp.Pos()) > target.DistanceSq(receiver.Pos()) {
			return true
		} else {
			return false
		}
	}

	// 计算球到达与对手位置垂直的位置所需的距离
	var timeForBall float64 = st.Pitch().Ball().TimeToCoverDistance(
		Vector2d{0, 0}, Vector{localPosOpp.X, 0}, passingForce)

	//现在计算对手这次能跑多远
	var reach float64 = opp.MaxSpeed()*timeForBall + st.Pitch().Ball().BRadius() + opp.BRadius()

	//如果到对手Y位置的距离小于他的跑动距离加上球的半径和对手的半径，则可以拦截球
	if math.Abs(localPosOpp.Y) < reach {
		return false
	}

	return true
}

/*
 * 对对方球队的每个成员测试从'from'到'target'目标的传球。
 * 如果可以在不被拦截的情况下进行传递，则返回true
 */
func (st *SoccerTeam) isPassSafeFromAllOpponents(
	from,
	target common.Vector2d,
	receiver *PlayerBase,
	passingForce float64,
) bool {
	for _, opp := range st.pOpponentsTeam.Members() {
		if isPassSafeFromOpponent(from, to, receiver, opp, passingForce) {
			return false
		}
	}
	return true
}

/*
 * 如果位置半径内有对手，则返回true
 */
func (st *SoccerTeam) isOpponentWithinRadius(pos common.Vector2d, radius float64) bool {
	for _, opp := range st.pOpponentsTeam.Members() {
		if pos.DictanceSq(opp.Pos()) < radius*radius {
			return true
		}
	}
	return false
}

/*
 * 这将测试请求者和控制者之间是否可以通过。
 * 如果有可能，会向控制球员发送一条信息，以便尽快传球。
 */
func (st *SoccerTeam) RequestPass(requester *FieldPlayer) {
	// 也许在这里限制一下
	if rand.Float64() > 0.1 {
		return
	}
	if st.isPassSafeFromAllOpponents(
		st.ControllingPlayer().Pos(),
		requester.Pos(),
		requester,
		st.ctx.Config().MaxPassingForce,
	) {
		st.ctx.Dispatcher.DispatchMsg(SEND_MSG_IMMEDIATELY,
			requester.Id(),
			st.ControllingPlayer().Id(),
			Msg_PassToMe,
			requester)
	}
}

// 计算最佳支撑位置并找到最合适的攻击者前往该位置
func (st *SoccerTeam) DetermineBestSupportingAttacker() *PlayerBase {
	var closestSoFar float64 = common.MaxFloat
	var basePlayer *PlayerBase

	for _, player := range st.player {
		//主攻角色的球员没有拿到球
		if RoleType_Attacker == player.Role() && player != st.pControllingPlayer {
			var dict float64 = player.Pos().DistanceSq(st.pSupportSpotCalc.GetBaseSupportingSpot())
			if dist < closestSoFar {
				closestSoFar = dist
				bastPlayer = player
			}
		}
	}
	return basePlayer
}

func (st *SoccerTeam) Members() []*PlayerBase {
	return st.members
}

func (st *SoccerTeam) HomeGoal() *Goal {
	return st.pHomeGoal
}

func (st *SoccerTeam) OpponentsGoal() *Goal {
	return st.pOpponentsTeam
}

func (st *SoccerTeam) Pitch() *SoccerPitch {
	return st.pPitch
}

func (st *SoccerTeam) Opponents() *SoccerTeam {
	return st.pOpponentsTeam
}

func (st *SoccerTeam) SetOpponents(team *SoccerTeam) {
	st.pOpponentsTeam = team
}

func (st *SoccerTeam) Color() TeamColor {
	return st.color
}

func (st *SoccerTeam) PlayerClosestToBall() *PlayerBase {
	return st.pPlayerClosestToBall
}

func (st *SoccerTeam) SetPlayerClosestToBall(player *PlayerBase) {
	st.pPlayerClosestToBall = player
}

func (st *SoccerTeam) ClosestDistToBallSq() float64 {
	return st.dDistSqToBallOfClosestPlayer
}

func (st *SoccerTeam) GetSupportSpot() common.Vector2d {
	return st.pSupportSpotCalc.GetBastSupportingSpot()
}

func (st *SoccerTeam) SupportingPlayer() *PlayerBase {
	return st.pSupportingPlayer
}

func (st *SoccerTeam) SetSupportingPlayer(player *PlayerBase) {
	st.pSupportingPlayer = player
}

func (st *SoccerTeam) Receiving() *PlayerBase {
	return st.pReceivingPlayer
}

func (st *SoccerTeam) SetReceiving(player *PlayerBase) {
	st.pReceivingPlayer = player
}

func (st *SoccerTeam) ControllingPlayer() *PlayerBase {
	return st.pControllingPlayer
}

func (st *SoccerTeam) SetControllingPlayer(player *PlayerBase) {
	st.pControllingPlayer = player
	st.Opponents().LostControl()
}

func (st *SoccerTeam) InControl() bool {
	return st.controllingPlayer != nil
}

func (st *SoccerTeam) LostControl() {
	st.pControllingPlayer = nil
}

func (st *SoccerTeam) GetPlayerFromID(id int) *PlayerBase {
	for _, player := range st.Member() {
		if player.Id() == id {
			return player
		}
	}
	return nil
}

func (st *SoccerTeam) SetPlayerHomeRegion(playerIdx, region int) {
	st.members[plyr].SetHomeRegion(region)
}

func (st *SoccerTeam) DetermineBestSupportingPosition() {
	st.pSupportSpotCalc.DetermineBestSupportingPosition()
}

func (st *SoccerTeam) UpdateTargetsOfWaitingPlayers() {
	for _, player := range st.members {
		if player.Role() == RoleType_Keeper {
			var plyr = player.(*FieldPlayer)
			if plyr.GetFSM().IsInState(StateWait) ||
				plyr.GetFSM().IsInState(StateReturnToHomeRegion) {
				plyr.Steering().SetTarget(plyr.HomeRegion().Center())
			}
		}
	}
}

//returns false if any of the team are not located within their home region
func (st *SoccerTeam) AllPlayersAtHome() bool {
	for _, player := range st.members {
		if !player.InHomeRegion() {
			return false
		}
	}
	return true
}

func (st *SoccerTeam) Name() string {
	/* TODO*/
	if st.color == TeamColor_Red {
		return "Red"
	} else {
		return "Blue"
	}
}

/*------ 状态机 -------*/

func (st *SoccerTeam) Update() {
	st.CalculateClosestPlayerToBall()
	st.pStateMachine.Update()
	for _, player := range st.members {
		player.Update()
	}
}
func (st *SoccerTeam) Render() bool { /*TODO*/ }
