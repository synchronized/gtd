package main

import "time"

func main() {
	var ctx *SoccerContext = NewSoccerContext()
	var config *Config = LoadConfig()
	var entityMgr *EntityManager = NewEntityManager()
	var messageDispatcher *MessageDispatcher = NewMessageDispatcher(ctx)
	ctx.SetConfig(config)
	ctx.SetEntityMgr(entityMgr)
	ctx.SetDispatcher(messageDispatcher)
	var cx int = WindowWidth
	var cy int = WindowHeight
	var pitch *SoccerPitch = NewSoccerPitch(ctx, cx, cy)
	for {
		pitch.Update()
		time.Sleep(time.Duration(20) * time.Millisecond)
	}
}
