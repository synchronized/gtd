package main

import (
	"fmt"
	"math/rand"
	"time"
	"westworld/common"
)

var StateWifesGlobalState common.IState
var StateDoHouseWork common.IState
var StateVisitBathroom common.IState
var StateCookStew common.IState

func init() {
	StateWifesGlobalState = NewWifesGlobalState()
	StateDoHouseWork = NewDoHouseWork()
	StateVisitBathroom = NewVisitBathroom()
	StateCookStew = NewCookStew()
}

//------------------------挖掘
type WifesGlobalState struct {
	*common.State
}

func NewWifesGlobalState() *WifesGlobalState {
	return &WifesGlobalState{}
}

func (wg *WifesGlobalState) Enter(entity common.IBaseGameEntity) {}

func (em *WifesGlobalState) Execute(entity common.IBaseGameEntity) {
	mw, ok := entity.(*MinerWife)
	if !ok {
		panic("WifesGlobalState::Execute() IBaseGameEntity->Miner failed")
	}
	if rand.Intn(100) < 10 {
		mw.GetFSM().ChangeState(StateVisitBathroom)
	}
}

func (em *WifesGlobalState) Exit(entity common.IBaseGameEntity) {}

func (em *WifesGlobalState) OnMessage(entity common.IBaseGameEntity, msg *common.Telegram) bool {
	mw, ok := entity.(*MinerWife)
	if !ok {
		panic("WifesGlobalState::Execute() IBaseGameEntity->Miner failed")
	}
	switch msg.Msg {
	case Msg_HiHoneImHome:
		fmt.Printf("++++Message Handed by [%s] at time: [%s]\n", entity.Name(), time.Now())
		fmt.Printf("%s: 嗨亲爱的。 让我为你做一些好的乡村炖肉\n", entity.Name())
		mw.GetFSM().ChangeState(StateCookStew)
		return true
	}
	return false
}

//做家务
type DoHouseWork struct {
	*common.State
}

func NewDoHouseWork() *DoHouseWork {
	return &DoHouseWork{}
}

func (wg *DoHouseWork) Enter(entity common.IBaseGameEntity) {}

func (em *DoHouseWork) Execute(entity common.IBaseGameEntity) {
	mw, ok := entity.(*MinerWife)
	if !ok {
		panic("DoHouseWork::Execute() IBaseGameEntity->Miner failed")
	}
	switch rand.Intn(3) {
	case 0:
		fmt.Printf("%s: 拖地板\n", mw.Name())
	case 1:
		fmt.Printf("%s: 洗碗\n", mw.Name())
	case 2:
		fmt.Printf("%s: 整理床铺\n", mw.Name())
	}
}

func (em *DoHouseWork) Exit(entity common.IBaseGameEntity) {}

//--------------------------------------------------
type VisitBathroom struct {
	*common.State
}

func NewVisitBathroom() *VisitBathroom {
	return &VisitBathroom{}
}

func (wg *VisitBathroom) Enter(entity common.IBaseGameEntity) {
	fmt.Printf("%s: 走到卫生间，需要漂亮的小鼻子\n", entity.Name())
}

func (em *VisitBathroom) Execute(entity common.IBaseGameEntity) {
	mw, ok := entity.(*MinerWife)
	if !ok {
		panic("VisitBathroom::Execute() IBaseGameEntity->Miner failed")
	}
	fmt.Printf("%s: : Ahhhhhh! 舒服的解脱!\n", mw.Name())
	mw.GetFSM().RevertToPreviousState()
}

func (em *VisitBathroom) Exit(entity common.IBaseGameEntity) {
	fmt.Printf("%s: 离开卫生间\n", entity.Name())
}

//做饭
type CookStew struct {
	*common.State
}

func NewCookStew() *CookStew {
	return &CookStew{}
}

func (cs *CookStew) Enter(entity common.IBaseGameEntity) {
	mw, ok := entity.(*MinerWife)
	if !ok {
		panic("CookStew::Execute() IBaseGameEntity->MinerWife failed")
	}
	if !mw.Cooking() {
		fmt.Printf("%s: 把炖汤放入烤箱\n", mw.Name())
		//间隔500毫秒
		Dispatcher.DispatchMessage(500*time.Millisecond, mw.Id(), mw.Id(), Msg_StewReady, nil)
		mw.SetCooking(true)
	}
}

func (cs *CookStew) Execute(entity common.IBaseGameEntity) {
	fmt.Printf("%s: 赞美事物\n", entity.Name())
}

func (cs *CookStew) Exit(entity common.IBaseGameEntity) {
	fmt.Printf("%s: 把炖汤放在桌子上\n", entity.Name())
}

func (cs *CookStew) OnMessage(entity common.IBaseGameEntity, msg *common.Telegram) bool {
	mw, ok := entity.(*MinerWife)
	if !ok {
		panic("CookStew::OnMessage() IBaseGameEntity->MinerWife failed")
	}
	switch msg.Msg {
	case Msg_StewReady:
		fmt.Printf("++++Message received by:[%s] at time: [%s]\n", mw.Name(), time.Now())
		fmt.Printf("%s: 做好了，开始吃吧\n", mw.Name())

		Dispatcher.DispatchMessage(0, mw.Id(), mw.GetMiner().Id(), Msg_StewReady, nil)

		mw.SetCooking(false)
		mw.GetFSM().ChangeState(StateDoHouseWork)
		return true
	}
	return false
}
