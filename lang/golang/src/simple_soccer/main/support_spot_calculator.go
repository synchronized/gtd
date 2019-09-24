package main

import (
	"math"
	"simple_soccer/common"
)

//助攻点
type SupportSpot struct {
	vPos   common.Vector2d //位置
	dScore float64         //分数
}

func NewSupportSpot(pos common.Vector2d, value float64) *SupportSpot {
	return &SupportSpot{
		vPos:   pos,
		dScore: value,
	}
}

//助攻点计算器
type SupportSpotCalculator struct {
	pTeam               *SoccerTeam
	aSpots              []*SupportSpot
	pBestSupportingSpot *SupportSpot
	pRegulator          *Regulator
}

func NewSupportSpotCalculator(numX, numY int, team *SoccerTeam) *SupportSpotCalculator {

	var ssc = &SupportSpotCalculator{
		pTeam: team,
	}

	var playingField *Region = team.Pitch().PlayingArea()

	//calculate the positions of each sweet spot, create them and
	//store them in m_Spots
	//计算每个最佳击球位置，创建它们并将它们存储在ssc.aSpots中
	var heightOfSSRegion float64 = playingField.Height() * 0.8
	var widthOfSSRegion float64 = playingField.Width() * 0.9
	var sliceX = widthOfSSRegion / float64(numX)
	var sliceY = heightOfSSRegion / float64(numY)

	var left float64 = playingField.Left() + (playingField.Width()-widthOfSSRegion)/2.0 + sliceX/2.0
	var right float64 = playingField.Right() - (playingField.Width()-widthOfSSRegion)/2.0 - sliceX/2.0
	var top float64 = playingField.Top() + (playingField.Height()-heightOfSSRegion)/2.0 + sliceY/2.0

	for x := 0; x < (numX/2)-1; x++ {
		for y := 0; y < numY; y++ {
			if ssc.pTeam.Color() == TeamColor_Blue {
				ssc.aSpots = append(ssc.aSpots, NewSupportSpot(common.Vector2d{
					left + float64(x)*sliceX,
					top + float64(y)*sliceY,
				}, 0.0))
			} else {
				ssc.aSpots = append(ssc.aSpots, NewSupportSpot(common.Vector2d{
					right - float64(x)*sliceX,
					top + float64(y)*sliceY,
				}, 0.0))
			}
		}
	}

	//create the regulator
	ssc.pRegulator = NewRegulator(team.Ctx().Config().SupportSpotUpdateFreq)
	return ssc
}

//获取最佳主攻点
func (ssc *SupportSpotCalculator) GetBestSupportingSpot() common.Vector2d {
	if ssc.pBestSupportingSpot != nil {
		return ssc.pBestSupportingSpot.vPos
	} else {
		return ssc.DetermineBestSupportingPosition()
	}
}

//this method iterates through each possible spot and calculates its
//score.
//迭代每个可能的点，计算分数
func (ssc *SupportSpotCalculator) DetermineBestSupportingPosition() common.Vector2d {
	//only update the spots every few frames
	if !ssc.pRegulator.IsReady() && ssc.pBestSupportingSpot != nil {
		return ssc.pBestSupportingSpot.vPos
	}

	//重置
	ssc.pBestSupportingSpot = nil
	var team = ssc.pTeam

	var bestScoreSoFar float64 = 0.0
	for _, curSpot := range ssc.aSpots {
		//first remove any previous score. (the score is set to one so that
		//the viewer can see the positions of all the spots if he has the
		//aids turned on)
		//首先删除以前的分数。
		//（分数设为1，以便观看者在打开辅助设备时可以看到所有斑点的位置）
		curSpot.dScore = 1.0

		//Test 1. is it possible to make a safe pass from the ball's position
		//to this position?
		//1. 从球的位置到这个位置能安全传球吗？
		if ssc.pTeam.IsPassSafeFromAllOpponents(
			*team.ControllingPlayer().Pos(),
			curSpot.vPos,
			nil,
			team.Ctx().Config().MaxPassingForce) {
			curSpot.dScore += team.Ctx().Config().Spot_PassSafeScore
		}

		//Test 2. Determine if a goal can be scored from this position.
		//确定这个位置是否可以得分。
		var ok, _ = team.CanShoot(curSpot.vPos, team.Ctx().Config().MaxShootingForce)
		if ok {
			curSpot.dScore += team.Ctx().Config().Spot_CanScoreFromPositionScore
		}

		//Test 3. calculate how far this spot is away from the controlling
		//player. The further away, the higher the score. Any distances further
		//away than OptimalDistance pixels do not receive a score.
		//计算这个位置离控制玩家有多远。越远，得分越高。
		//任何比最佳距离像素更远的距离都不会得到分数。
		if team.SupportingPlayer() != nil {
			var optimalDistance float64 = 200.0
			var dist float64 = team.ControllingPlayer().Pos().Distance(&curSpot.vPos)

			var temp float64 = math.Abs(optimalDistance - dist)
			if temp < optimalDistance {
				//normalize the distance and add it to the score
				//normalize距离并将其添加到分数中
				curSpot.dScore += team.Ctx().Config().Spot_DistFromControllingPlayerScore *
					(optimalDistance - temp) / optimalDistance

			}
		}

		//check to see if this spot has the highest score so far
		//检查这个助攻点是否是目前为止得分最高的
		if curSpot.dScore > bestScoreSoFar {
			bestScoreSoFar = curSpot.dScore
			ssc.pBestSupportingSpot = curSpot
		}
	}

	return ssc.pBestSupportingSpot.vPos
}

func (ssc *SupportSpotCalculator) Render() { /*TODO*/ }
