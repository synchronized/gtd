package main

import (
	"simple_soccer/common"
)

var (
	StateAttacking         common.IState
	StateDefending         common.IState
	StatePrepareForKickOff common.IState
)

func init() {
	StateAttacking = NewTeamStateAttacking()
	StateDefending = NewTeamStateDefending()
	StatePrepareForKickOff = NewTeamStatePrepareForKickOff()
}

//----------------------------------------------------
//公共方法

func changePlayerHomeRegions(team *SoccerTeam, NewRegions []int) {
	for plyr := 0; plyr < TeamSize; plyr++ {
		team.SetPlayerHomeRegion(plyr, NewRegions[plyr])
	}
}

//----------------------------------------------------
//进攻
type TeamStateAttacking struct {
	common.IState
}

func NewTeamStateAttacking() *TeamStateAttacking {
	return &TeamStateAttacking{}
}

func (tsa *TeamStateAttacking) Enter(entity interface{}) {
	var team = entity.(*SoccerTeam)
	Debug_State(team.Ctx(), "[%s] entering Attacking state", team.Name())

	//these define the home regions for this state of each of the players
	//定义了每个玩家的这个状态的home regions
	var BlueRegions = []int{1, 12, 14, 6, 4}
	var RedRegions = []int{16, 3, 5, 9, 13}

	//set up the player's home regions
	//设置球员的homeRegion
	if team.Color() == TeamColor_Blue {
		changePlayerHomeRegions(team, BlueRegions)
	} else {
		changePlayerHomeRegions(team, RedRegions)
	}
	//if a player is in either the Wait or ReturnToHomeRegion states, its
	//steering target must be updated to that of its new home region to enable
	//it to move into the correct position.
	//如果玩家处于等待或返回本地区状态，
	//则必须将其转向目标更新为新本地区的目标，以使其能够移动到正确的位置。
	team.UpdateTargetsOfWaitingPlayers()
}

func (tsa *TeamStateAttacking) Execute(entity interface{}) {
	var team = entity.(*SoccerTeam)
	//if this team is no longer in control change states
	//如果该团队不再控制球则更改状态
	if !team.InControl() {
		team.GetFSM().ChangeState(StateDefending)
		return
	}

	//calculate the best position for any supporting attacker to move to
	//计算任意一个助攻移动到的最佳位置
	team.DetermineBestSupportingPosition()
}

func (tsa *TeamStateAttacking) Exit(entity interface{}) {
	var team = entity.(*SoccerTeam)
	//there is no supporting player for defense
	//防守没有助攻的球员
	team.SetSupportingPlayer(nil)
}

//----------------------------------------------------
//防守
type TeamStateDefending struct {
	common.IState
}

func NewTeamStateDefending() *TeamStateDefending {
	return &TeamStateDefending{}
}

func (tsd *TeamStateDefending) Enter(entity interface{}) {
	var team = entity.(*SoccerTeam)
	Debug_State(team.Ctx(), "[%s] entering Defending state", team.Name())

	var BlueRegions = []int{1, 6, 8, 3, 5}
	var RedRegions = []int{16, 9, 11, 12, 14}

	//set up the player's home regions
	//设置各个球员的home region
	if team.Color() == TeamColor_Blue {
		changePlayerHomeRegions(team, BlueRegions)
	} else {
		changePlayerHomeRegions(team, RedRegions)
	}

	//if a player is in either the Wait or ReturnToHomeRegion states, its
	//steering target must be updated to that of its new home region
	//如果玩家处于StateWait 或者 StateReturnToHomeRegion状态,
	//那么它的steering 目标必须被更新为新的 home region
	team.UpdateTargetsOfWaitingPlayers()
}

func (tsd *TeamStateDefending) Execute(entity interface{}) {
	var team = entity.(*SoccerTeam)
	//假如拿到球，改变状态
	if team.InControl() {
		team.GetFSM().ChangeState(StateAttacking)
		return
	}
}

func (tsd *TeamStateDefending) Exit(entity interface{}) {}

//----------------------------------------------------
//准备开球
type TeamStatePrepareForKickOff struct {
	common.IState
}

func NewTeamStatePrepareForKickOff() *TeamStatePrepareForKickOff {
	return &TeamStatePrepareForKickOff{}
}

func (tsp *TeamStatePrepareForKickOff) Enter(entity interface{}) {
	var team = entity.(*SoccerTeam)
	//reset key player pointers
	//重置各个角色的指针
	team.SetControllingPlayer(nil)
	team.SetSupportingPlayer(nil)
	team.SetReceiving(nil)
	team.SetPlayerClosestToBall(nil)

	//对每个球员发送 Msg_GoHome消息
	team.ReturnAllFieldPlayersToHome()
}

func (tsp *TeamStatePrepareForKickOff) Execute(entity interface{}) {
	var team = entity.(*SoccerTeam)
	if team.AllPlayersAtHome() && team.Opponents().AllPlayersAtHome() {
		team.GetFSM().ChangeState(StateDefending)
	}
}

func (tsp *TeamStatePrepareForKickOff) Exit(entity interface{}) {
	var team = entity.(*SoccerTeam)
	team.Pitch().SetGameOn()
}
