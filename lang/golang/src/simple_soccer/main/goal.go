package main

import "simple_soccer/common"

//球门
type Goal struct {
	vLeftPost  common.Vector2d
	vRightPost common.Vector2d

	vFacing common.Vector2d //球门朝向
	vCenter common.Vector2d //中线位置

	iNumGoalsScored int //检测到进球将它++
}

func NewGoal(left, right, facing common.Vector2d) *Goal {
	return &Goal{
		vLeftPost:       left,
		vRightPost:      right,
		vCenter:         *left.OpAdd(&right).OpDivide(2.0),
		vFacing:         facing,
		iNumGoalsScored: 0,
	}
}

func (g *Goal) Center() *common.Vector2d {
	return &g.vCenter
}

func (g *Goal) Facing() *common.Vector2d {
	return &g.vFacing
}

func (g *Goal) LeftPost() *common.Vector2d {
	return &g.vLeftPost
}

func (g *Goal) RightPost() *common.Vector2d {
	return &g.vRightPost
}

func (g *Goal) NumGoalsScored() int {
	return g.iNumGoalsScored
}

func (g *Goal) IncrNumGoalsScored() {
	g.iNumGoalsScored++
}

func (g *Goal) SetNumGoalsScored(score int) {
	g.iNumGoalsScored = score
}

//给定球当前的位置和上次的位置
//如果跨过球门线则返回真,numGoalsScored增加1
func (g *Goal) Scored(ball *SoccerBall) bool {
	if common.LineIntersection2D(*ball.Pos(), *ball.OldPos(), g.vLeftPost, g.vRightPost) {
		g.iNumGoalsScored++
		return true
	}
	return false
}
