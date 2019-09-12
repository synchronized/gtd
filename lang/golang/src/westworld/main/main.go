package main

import (
	"time"
	"westworld/common"
)

var accumulator *common.Accumulator
var Dispatcher *MessageDispatcher
var EntityMgr *EntityManager

func init() {
	accumulator = common.NewAccumulator()
	EntityMgr = NewEntityManager()
	Dispatcher = NewMessageDispatcher(EntityMgr)
}

func main() {
	var wife = NewMinerWife(accumulator.Next(), "elsa")
	var miner = NewMiner(accumulator.Next(), "bob")
	EntityMgr.RegisterEntity(wife)
	EntityMgr.RegisterEntity(miner)

	wife.SetMiner(miner)
	miner.SetWife(wife)

	//simply run the miner through a few Update calls
	for i := 0; i < 200; i++ {
		miner.Update()
		wife.Update()

		//dispatch any delayed messages
		Dispatcher.DispatchDelayMessages()

		time.Sleep(800 * time.Millisecond)
	}
}
