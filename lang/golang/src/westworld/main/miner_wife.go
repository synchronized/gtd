package main

import "westworld/common"

//矿工
type MinerWife struct {
	common.BaseGameEntity
	stateMachine *StateMachine       //状态机
	location     common.LocationType //位置
	bCooking     bool                //是否在做饭
	miner        *Miner
}

func NewMinerWife(id int, name string) *MinerWife {
	var mw = &MinerWife{
		stateMachine: nil,
		location:     LocationShack, //位置
		bCooking:     false,
		miner:        nil,
	}
	mw.stateMachine = NewStateMachine(mw)
	mw.stateMachine.SetCurrentState(StateDoHouseWork)
	mw.stateMachine.SetGlobalState(StateWifesGlobalState)
	mw.SetBase(id, name)
	return mw
}

func (mw *MinerWife) Update() {
	if mw.stateMachine != nil {
		mw.stateMachine.Update()
	}
}

func (m *MinerWife) Cooking() bool {
	return m.bCooking
}

func (m *MinerWife) SetCooking(val bool) {
	m.bCooking = val
}

func (mw *MinerWife) GetFSM() *StateMachine {
	return mw.stateMachine
}

func (m *MinerWife) HandleMessage(msg *common.Telegram) bool {
	return m.stateMachine.HandleMessage(msg)
}

func (m *MinerWife) GetMiner() *Miner {
	return m.miner
}

func (m *MinerWife) SetMiner(miner *Miner) {
	m.miner = miner
}
