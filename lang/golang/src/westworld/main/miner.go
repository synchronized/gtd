package main

import "westworld/common"

//矿工
type Miner struct {
	//common.IBaseGameEntity
	common.BaseGameEntity
	stateMachine *StateMachine       //状态机
	location     common.LocationType //位置
	goldCarried  int                 //背包中金块数量
	moneyInBank  int                 //银行存款
	thirst       int                 //口渴程度
	fatigue      int                 //疲劳程度
	wife         *MinerWife          //妻子实例
}

func NewMiner(id int, name string) *Miner {
	var m = &Miner{
		stateMachine: nil,
		location:     LocationShack, //位置
		goldCarried:  0,             //背包中金块数量
		moneyInBank:  0,             //银行存款
		thirst:       0,             //口渴程度
		fatigue:      0,             //疲劳程度
		wife:         nil,
	}
	m.stateMachine = NewStateMachine(m)
	m.stateMachine.SetCurrentState(StateGoHomeAndSleepTilRested)
	// m.stateMachine.SetGlobalState(StateMinerGlobal)
	m.SetBase(id, name)
	return m
}

func (m *Miner) Update() {
	m.thirst++
	if m.stateMachine != nil {
		m.stateMachine.Update()
	}
}

//获取位置
func (m *Miner) Location() common.LocationType {
	return m.location
}

//改变位置
func (m *Miner) ChangeLocation(newLocation common.LocationType) {
	m.location = newLocation
}

func (m *Miner) GoldCarried() int {
	return m.goldCarried
}

//增加背包的金块
func (m *Miner) AddToGoldCarried(num int) {
	m.goldCarried += num
	if m.goldCarried < 0 {
		m.goldCarried = 0
	}
}

func (m *Miner) SetGoldCarried(num int) {
	m.goldCarried = num
}

func (m *Miner) AddToWealth(num int) {
	m.moneyInBank += num
	if m.moneyInBank < 0 {
		m.moneyInBank = 0
	}
}

func (m *Miner) Wealth() int {
	return m.moneyInBank
}

//增加疲劳值
func (m *Miner) IncreaseFatigue() {
	m.fatigue++
}

//减少疲劳值
func (m *Miner) DecreaseFatigue() {
	m.fatigue--
}

//背包是否已经满了
func (m *Miner) PocketsFull() bool {
	return m.goldCarried > MaxNuggets
}

func (m *Miner) IsThirsty() bool {
	return m.thirst > ThirstLevel
}

func (m *Miner) IsFatigued() bool {
	return m.fatigue > TirednessThreshold
}

func (m *Miner) BuyAndDrinkAWhiskey() {
	m.thirst = 0
	m.moneyInBank -= 2
}

func (m *Miner) GetFSM() *StateMachine {
	return m.stateMachine
}

func (m *Miner) HandleMessage(msg *common.Telegram) bool {
	return m.stateMachine.HandleMessage(msg)
}

func (m *Miner) GetWife() *MinerWife {
	return m.wife
}

func (m *Miner) SetWife(wife *MinerWife) {
	m.wife = wife
}
