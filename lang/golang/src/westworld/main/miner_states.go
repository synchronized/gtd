package main

import (
	"fmt"
	"time"
	"westworld/common"
)

var StateEnterMineAndDigForNugget common.IState
var StateVisitBankAndDepositGold common.IState
var StateGoHomeAndSleepTilRested common.IState
var StateQuenchThirst common.IState
var StateEatStew common.IState

func init() {
	StateEnterMineAndDigForNugget = NewEnterMineAndDigForNugget()
	StateVisitBankAndDepositGold = NewVisitBankAndDepositGold()
	StateGoHomeAndSleepTilRested = NewGoHomeAndSleepTilRested()
	StateQuenchThirst = NewQuenchThirst()
	StateEatStew = NewEatStew()
}

//------------------------挖掘
type EnterMineAndDigForNugget struct {
	*common.State
}

func NewEnterMineAndDigForNugget() *EnterMineAndDigForNugget {
	return &EnterMineAndDigForNugget{}
}

func (em *EnterMineAndDigForNugget) Enter(entity common.IBaseGameEntity) {
	m, ok := entity.(*Miner)
	if !ok {
		panic("EnterMineAndDigForNugget::Enter() IBaseGameEntity->Miner failed")
	}
	if m.Location() != LocationGoldmine {
		fmt.Printf("%s: 走进到金矿\n", m.Name())
		m.ChangeLocation(LocationGoldmine)
	}
}

func (em *EnterMineAndDigForNugget) Execute(entity common.IBaseGameEntity) {
	m, ok := entity.(*Miner)
	if !ok {
		panic("EnterMineAndDigForNugget::Execute() IBaseGameEntity->Miner failed")
	}
	//矿工挖掘金子知道达到背包上限
	//如果口渴了会去喝啤酒
	m.AddToGoldCarried(1)
	//增加疲劳值
	m.IncreaseFatigue()

	fmt.Printf("%s: 挑选一个金块放到背包\n", m.Name())
	//如果开采足够的金子,去把它放到银行里面
	if m.PocketsFull() {
		m.GetFSM().ChangeState(StateVisitBankAndDepositGold)
	}
	if m.IsThirsty() {
		m.GetFSM().ChangeState(StateQuenchThirst)
	}
}

func (em *EnterMineAndDigForNugget) Exit(entity common.IBaseGameEntity) {
	fmt.Printf("%s: 啊，离开这个金矿，里面装满了满满的黄金\n", entity.Name())
}

//------------------------存钱
type VisitBankAndDepositGold struct {
	*common.State
}

func NewVisitBankAndDepositGold() *VisitBankAndDepositGold {
	return &VisitBankAndDepositGold{}
}

func (vb *VisitBankAndDepositGold) Enter(entity common.IBaseGameEntity) {
	m, ok := entity.(*Miner)
	if !ok {
		panic("VisitBankAndDepositGold::Enter() IBaseGameEntity->Miner failed")
	}
	if m.Location() != LocationBank {
		fmt.Printf("%s: 去银行。 是的siree\n", m.Name())
		m.ChangeLocation(LocationBank)
	}
}

func (vb *VisitBankAndDepositGold) Execute(entity common.IBaseGameEntity) {
	m, ok := entity.(*Miner)
	if !ok {
		panic("VisitBankAndDepositGold::Execute() IBaseGameEntity->Miner failed")
	}
	//deposit the gold
	m.AddToWealth(m.GoldCarried())
	m.SetGoldCarried(0)

	fmt.Printf("%s: 存金。 现在总节省: %d\n", m.Name(), m.Wealth())
	if m.Wealth() >= ComfortLevel {

		fmt.Printf("%s: 哇噢！ 现在足够丰富了。 回家\n", m.Name())
		m.GetFSM().ChangeState(StateGoHomeAndSleepTilRested)
	} else {
		m.GetFSM().ChangeState(StateEnterMineAndDigForNugget)
	}
}

func (vb *VisitBankAndDepositGold) Exit(entity common.IBaseGameEntity) {
	fmt.Printf("%s: 离开银行\n", entity.Name())
}

//------------------------回家休息
type GoHomeAndSleepTilRested struct {
	*common.State
}

func NewGoHomeAndSleepTilRested() *GoHomeAndSleepTilRested {
	return &GoHomeAndSleepTilRested{}
}

func (vb *GoHomeAndSleepTilRested) Enter(entity common.IBaseGameEntity) {
	m, ok := entity.(*Miner)
	if !ok {
		panic("GoHomeAndSleepTilRested::Enter() IBaseGameEntity->Miner failed")
	}
	if m.Location() != LocationShack {
		fmt.Printf("%s: 走回家\n", m.Name())
		m.ChangeLocation(LocationShack)

		//TODO
		Dispatcher.DispatchMessage(0, m.Id(), m.GetWife().Id(), Msg_HiHoneImHome, nil)
	}
}

func (vb *GoHomeAndSleepTilRested) Execute(entity common.IBaseGameEntity) {
	m, ok := entity.(*Miner)
	if !ok {
		panic("GoHomeAndSleepTilRested::Execute() IBaseGameEntity->Miner failed")
	}
	if !m.IsFatigued() {
		fmt.Printf("%s: 多么神奇的午睡！ 是时候寻找更多的黄金了\n", m.Name())
		m.GetFSM().ChangeState(StateEnterMineAndDigForNugget)
	} else {
		//sleep
		m.DecreaseFatigue()
		fmt.Printf("%s: ZZZZ... \n", m.Name())
	}
}

func (vb *GoHomeAndSleepTilRested) Exit(entity common.IBaseGameEntity) {
	//fmt.Printf("%s: 离开房子\n", entity.Name())
}

func (vb *GoHomeAndSleepTilRested) OnMessage(entity common.IBaseGameEntity, msg *common.Telegram) bool {
	m, ok := entity.(*Miner)
	if !ok {
		panic("GoHomeAndSleepTilRested::OnMessage() IBaseGameEntity->Miner failed")
	}
	switch msg.Msg {
	case Msg_StewReady:
		fmt.Printf("++++Message handled by [%s] at time[%s]\n", entity.Name(), time.Now())
		fmt.Printf("%s: 好的，来吃吧\n", entity.Name())

		m.GetFSM().ChangeState(StateEatStew)
		return true
	}
	return false
}

//------------------------喝啤酒
type QuenchThirst struct {
	*common.State
}

func NewQuenchThirst() *QuenchThirst {
	return &QuenchThirst{}
}

func (qt *QuenchThirst) Enter(entity common.IBaseGameEntity) {
	m, ok := entity.(*Miner)
	if !ok {
		panic("QuenchThirst::Enter() IBaseGameEntity->Miner failed")
	}

	if m.Location() != LocationSaloon {
		m.ChangeLocation(LocationSaloon)

		fmt.Printf("%s: 男孩啊，肯定是值得信赖的！ 走到沙龙\n", m.Name())
	}
}

func (qt *QuenchThirst) Execute(entity common.IBaseGameEntity) {
	m, ok := entity.(*Miner)
	if !ok {
		panic("QuenchThirst::Execute() IBaseGameEntity->Miner failed")
	}
	if m.IsThirsty() {
		m.BuyAndDrinkAWhiskey()

		fmt.Printf("%s: 那是一种强烈的啜饮酒\n", m.Name())

		m.GetFSM().ChangeState(StateEnterMineAndDigForNugget)
	} else {
		fmt.Printf("\nERROR!\nERROR!\nERROR!")
	}
}

func (qt *QuenchThirst) Exit(entity common.IBaseGameEntity) {
	fmt.Printf("%s: 离开沙龙，感觉很好\n", entity.Name())
}

//吃食物
type EatStew struct {
	common.State
}

func NewEatStew() *EatStew {
	return &EatStew{}
}

func (es *EatStew) Enter(entity common.IBaseGameEntity) {
	m, ok := entity.(*Miner)
	if !ok {
		panic("EatStew::Enter() IBaseGameEntity->Miner failed")
	}
	fmt.Printf("%s: 闻起来真的很好[%s]！\n", m.Name(), m.GetWife().Name())
}

func (es *EatStew) Execute(entity common.IBaseGameEntity) {
	m, ok := entity.(*Miner)
	if !ok {
		panic("EatStew::Execute() IBaseGameEntity->Miner failed")
	}
	fmt.Printf("%s: 口味也很棒！\n", m.Name())
	m.GetFSM().RevertToPreviousState()
}

func (es *EatStew) Exit(entity common.IBaseGameEntity) {
	m, ok := entity.(*Miner)
	if !ok {
		panic("EatStew::Exit() IBaseGameEntity->Miner failed")
	}
	fmt.Printf("%s: 谢谢你,可爱的女士, 最好回到什么\n", m.Name())
}
