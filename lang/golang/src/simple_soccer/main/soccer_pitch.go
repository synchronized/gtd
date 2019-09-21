package main

//球场
type SoccerPitch struct {
	ball     *SoccerBall //足球
	redTeam  *SoccerTeam //红队
	blueTeam *SoccerTeam //蓝队
	redGoal  *Goal       //红队球门
	blueGoal *Goal       //蓝队球门

	walls []*Wall2d //足球场的墙

	playingArea       *Region
	regions           []*Region
	goalKeeperHasBall bool //守门员拿到了球
	gameOn            bool //是否正在游戏
	paused            bool //暂停
	cxClient          int
	cyClient          int
}

func (sp *SoccerPitch) GetRegionFromIndex(idx int) *Region {
}

func (sp *SoccerPitch) TogglePause() {
	sp.paused = !sp.paused
}

func (sp *SoccerPitch) Paused() {
	return sp.paused
}

func (sp *SoccerPitch) CxClient() {
	return sp.cxClient
}
func (sp *SoccerPitch) CyClient() {
	return sp.cyClient
}

func (sp *SoccerPitch) IsGoalKeeperHasBall() {
	return sp.goalKeeperHasBall
}

func (sp *SoccerPitch) SetGoalKeeperHasBall(b bool) {
	sp.goalKeeperHasBall = b
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
	return sp.gameOn
}

func (sp *SoccerPitch) SetGameOn() {
	sp.gameOn = true
}

func (sp *SoccerPitch) SetGameOff() {
	sp.gameOn = false
}

func (sp *SoccerPitch) Update() {
	//TODO
}

func (sp *SoccerPitch) Render() bool {
	//TODO
}
