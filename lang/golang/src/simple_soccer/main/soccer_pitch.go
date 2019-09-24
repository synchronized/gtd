package main

import "simple_soccer/common"

//球场
type SoccerPitch struct {
	ctx       *SoccerContext
	pBall     *SoccerBall //足球
	pRedTeam  *SoccerTeam //红队
	pBlueTeam *SoccerTeam //蓝队
	pRedGoal  *Goal       //红队球门
	pBlueGoal *Goal       //蓝队球门

	aWalls []*Wall2d //足球场的墙

	pPlayingArea       *Region
	aRegions           []*Region
	bGoalKeeperHasBall bool //守门员拿到了球
	bGameOn            bool //是否正在游戏
	bPaused            bool //暂停
	cxClient           int
	cyClient           int

	allMembers []*PlayerBase //场上所有的角色
}

func NewSoccerPitch(ctx *SoccerContext, cx, cy int) *SoccerPitch {
	var sp = &SoccerPitch{
		ctx:                ctx,
		aRegions:           make([]*Region, NumRegionsHorizontal*NumRegionsVertical),
		bGoalKeeperHasBall: false,
		bGameOn:            false,
		bPaused:            false,
		cxClient:           cx,
		cyClient:           cy,
	}
	//define the playing area
	sp.pPlayingArea = NewRegion(20, 20, cx-20, cy-20)
	//create regions
	sp.CreateRegions(
		sp.pPlayingArea.Width()/float64(NumRegionsHorizontal),
		sp.pPlayingArea.Height()/float64(NumRegionsVertical))

	//create the goals
	var goalWidth float64 = sp.ctx.Config().GoalWidth
	sp.pRedGoal = NewGoal(
		common.Vector2d{pPlayingArea.Left(), (cy - goalWidth) / 2},
		common.Vector2d{pPlayingArea.Left(), cy - (cy-goalWidth)/2},
		common.Vector2d{1, 0})

	sp.pBlueGoal = NewGoal(
		common.Vector2d{pPlayingArea.Right(), (cy - goalWidth) / 2},
		common.Vector2d{pPlayingArea.Right(), cy - (cy-goalWidth)/2},
		common.Vector2d{-1, 0})

	//create the walls
	var topLeft = common.Vector2d{sp.pPlayingArea.Left(), sp.pPlayingArea.Top()}
	var topRight = common.Vector2d{sp.pPlayingArea.Right(), sp.pPlayingArea.Top()}
	var bottomLeft = common.Vector2d{sp.pPlayingArea.Left(), sp.pPlayingArea.Bottom()}
	var bottomRight = common.Vector2d{sp.pPlayingArea.Right(), sp.pPlayingArea.Bottom()}
	sp.aWalls = append(sp.aWalls, NewWall2D(bottomLeft, sp.pRedGoal.RightPost()))
	sp.aWalls = append(sp.aWalls, NewWall2D(sp.pRedGoal.LeftPost(), topLeft))
	sp.aWalls = append(sp.aWalls, NewWall2D(topLeft, topRight))
	sp.aWalls = append(sp.aWalls, NewWall2D(topRight, sp.pBlueGoal.LeftPost()))
	sp.aWalls = append(sp.aWalls, NewWall2D(sp.pBlueGoal.RightPost(), bottomRight))
	sp.aWalls = append(sp.aWalls, NewWall2D(bottomRight, bottomLeft))

	//create the soccer ball
	sp.pBall = NewSoccerBall(
		common.Vector2d{float64(sp.cxClient) / 2.0, float64(sp.cyClient) / 2.0},
		sp.ctx.Config().BallSize,
		sp.ctx.Config().BallMass,
		sp.aWalls)

	//create the teams
	sp.pRedTeam = NewSoccerTeam(ctx, sp.pRedGoal, sp, TeamColor_Red)
	sp.pBlueTeam = NewSoccerTeam(ctx, sp.pBlueGoal, sp, TeamColor_Blue)

	//make sure each team knows who their opponents are
	sp.pRedTeam.SetOpponents(sp.pBlueTeam)
	sp.pBlueTeam.SetOpponents(sp.pRedTeam)
	sp.allMembers = append(sp.allMembers, sp.pRedTeam.Members()...)
	sp.allMembers = append(sp.allMembers, sp.pBlueTeam.Members()...)

	return sp
}

func (sp *SoccerPitch) Ctx() *SoccerContext {
	return sp.ctx
}

func (sp *SoccerPitch) CreateRegions(idx int, width, height float64) *Region {
	var idx int = len(sp.aRegions)
	for col := 0; col < NumRegionsHorizontal; col++ {
		for row := 0; row < NumRegionsVertical; row++ {
			sp.aRegions[idx] = NewRegion(
				sp.pPlayingArea.Left()+col*width,
				sp.pPlayingArea.Top()+row*height,
				sp.pPlayingArea.Left()+(col+1)*width,
				sp.pPlayingArea.Top()+(row+1)*height,
				idx,
			)
			idx--
		}
	}
}

func (sp *SoccerPitch) GetRegionFromIndex(idx int) *Region {
	return sp.aRegions[idx]
}

func (sp *SoccerPitch) TogglePause() {
	sp.bPaused = !sp.bPaused
}

func (sp *SoccerPitch) Paused() {
	return sp.bPaused
}

func (sp *SoccerPitch) CxClient() {
	return sp.cxClient
}
func (sp *SoccerPitch) CyClient() {
	return sp.cyClient
}

func (sp *SoccerPitch) IsGoalKeeperHasBall() {
	return sp.bGoalKeeperHasBall
}

func (sp *SoccerPitch) SetGoalKeeperHasBall(b bool) {
	sp.bGoalKeeperHasBall = b
}

func (sp *SoccerPitch) PlayingArea() *Region {
	return sp.playingArea
}

func (sp *SoccerPitch) Walls() []*Wall2d {
	return sp.walls
}

func (sp *SoccerPitch) Ball() *SoccerBall {
	return sp.ball
}

func (sp *SoccerPitch) GetRegionFromIndex(idx int) *Region {
	return regions[idx]
}

func (sp *SoccerPitch) IsGameOn() bool {
	return sp.bGameOn
}

func (sp *SoccerPitch) SetGameOn() {
	sp.bGameOn = true
}

func (sp *SoccerPitch) SetGameOff() {
	sp.bGameOn = false
}

func (sp *SoccerPitch) AllMembers() []*PlayerBase {
	return sp.allMembers
}

//  this demo works on a fixed frame rate (60 by default) so we don't need
//  to pass a time_elapsed as a parameter to the game entities
//这个演示程序以固定的帧速率（默认为60）工作，
//因此我们不需要将经过的时间作为参数传递给游戏实体
func (sp *SoccerPitch) Update() {
	if sp.bPaused {
		return
	}

	var tick int = 0
	//upadte the balls
	sp.pBall.Update()

	//update the teams
	sp.pRedTeam.Update()
	sp.pBlueTeam.Update()

	//if a goal has been detected reset the pitch ready for kickoff
	if sp.pBlueGoal.Scored(sp.pBall) || sp.pRedGoal.Scored(sp.pBall) {
		sp.bGameOn = false
		//reset the ball
		sp.pBall.PlaceAtPostion(common.Vector2d{float64(sp.cxClient) / 2.0, float64(sp.cyClient) / 2.0})

		//get the teams ready for kickoff
		sp.pRedTeam.GetFSM().ChangeState(StatePrepareForKickOff)
		sp.pBlueTeam.GetFSM().ChangeState(StatePrepareForKickOff)
	}
}

func (sp *SoccerPitch) Render() bool {
	//TODO
}
