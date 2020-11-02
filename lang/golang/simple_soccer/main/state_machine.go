package main

import (
	"reflect"
	"simple_soccer/common"
)

type StateMachine struct {
	ctx           *SoccerContext
	owner         interface{}
	currentState  common.IState
	previousState common.IState
	globalState   common.IState
}

func NewStateMachine(ctx *SoccerContext, owner interface{}) *StateMachine {
	return &StateMachine{
		ctx:           ctx,
		owner:         owner,
		currentState:  nil,
		previousState: nil,
		globalState:   nil,
	}
}

//set get方法
func (sm *StateMachine) CurrentState() common.IState {
	return sm.currentState
}
func (sm *StateMachine) PreviousState() common.IState {
	return sm.previousState
}
func (sm *StateMachine) GlobalState() common.IState {
	return sm.globalState
}

func (sm *StateMachine) SetCurrentState(state common.IState) {
	sm.currentState = state
}
func (sm *StateMachine) SetPreviousState(state common.IState) {
	sm.previousState = state
}
func (sm *StateMachine) SetGlobalState(state common.IState) {
	sm.globalState = state
}

//调用这个更新FSM
func (sm *StateMachine) Update() {
	if sm.globalState != nil {
		sm.globalState.Execute(sm.owner)
	}
	if sm.currentState != nil {
		sm.currentState.Execute(sm.owner)
	}
}

//改变到一个新的状态
func (sm *StateMachine) ChangeState(newState common.IState) {
	sm.previousState = sm.currentState
	if sm.currentState != nil {
		Debug_State(sm.ctx, "exit state [%s]", reflect.TypeOf(newState).Kind().String())
		sm.currentState.Exit(sm.owner)
	}

	Debug_State(sm.ctx, "enter state [%s]", reflect.TypeOf(newState).Kind().String())
	sm.currentState = newState
	sm.currentState.Enter(sm.owner)
}

//改变回到前一个状态
func (sm *StateMachine) RevertToPreviousState() {
	sm.ChangeState(sm.previousState)
}

//当前状态等于传入的状态返回true
func (sm *StateMachine) IsInState(state common.IState) bool {
	return sm.currentState == state
}

//处理消息
func (sm *StateMachine) HandleMessage(msg *common.Telegram) bool {
	if sm.currentState != nil && sm.currentState.OnMessage(sm.owner, msg) {
		return true
	}
	if sm.globalState != nil && sm.globalState.OnMessage(sm.owner, msg) {
		return true
	}
	return false
}
