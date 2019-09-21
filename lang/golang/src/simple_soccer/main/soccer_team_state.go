package main

import (
	"simple_soccer/common"
)

var StateAttacking common.IState
var StateDefending common.IState
var StatePrepareForKickOff common.IState

func init() {
	StateAttacking = NewTeamStateAttacking()
	StateDefending = NewTeamStateDefending()
	StatePrepareForKickOff = NewTeamStatePrepareForKickOff()
}

//进攻
type TeamStateAttacking struct {
	common.IState
}

func NewTeamStateAttacking() *TeamStateAttacking {
	return &TeamStateAttacking{}
}

//防守
type TeamStateDefending struct {
	common.IState
}

func NewTeamStateDefending() *TeamStateDefending {
	return &TeamStateDefending{}
}

//准备开球
type TeamStatePrepareForKickOff struct {
	common.IState
}

func NewTeamStatePrepareForKickOff() *TeamStatePrepareForKickOff {
	return &TeamStatePrepareForKickOff{}
}
