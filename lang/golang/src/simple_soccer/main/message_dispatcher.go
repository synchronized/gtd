package main

import (
	"fmt"
	"time"
	"westworld/common"
)

const SEND_MSG_IMMEDIATELY = time.Duration(0)

type MessageDispatcher struct {
	priorityQ []*common.Telegram
	entityMgr *EntityManager
}

func NewMessageDispatcher(entityMgr *EntityManager) *MessageDispatcher {
	return &MessageDispatcher{
		entityMgr: entityMgr,
	}
}

//派发消息
func (md *MessageDispatcher) Discharge(receiver common.IBaseGameEntity, msg *common.Telegram) {
	if !receiver.HandleMessage(msg) {
		fmt.Printf("====Message not handled receiver:[%s] msg id:[%d]\n", receiver.Name(), msg.Msg)
	}
}

func (md *MessageDispatcher) DispatchMessage(
	delay time.Duration,
	sender int,
	receiver int,
	msg common.MessageType,
	ExtraInfo interface{},
) {
	var pSender = md.entityMgr.GetEntityById(sender)
	var pReceiver = md.entityMgr.GetEntityById(receiver)
	if pReceiver == nil {
		Debug_Message("Warning! No Receiver with ID of [%d] found", receiver)
		return
	}
	var telegram = common.NewTelegram(delay, sender, receiver, msg, ExtraInfo)
	if delay <= 0 {
		//TODO msg to str
		Debug_Message("Instant telegram dispatched at time:[%s] by:[%s] for:[%s]. Msg is:[%d]",
			time.Now(), pSender.Name(), pReceiver.Name(), msg)
		md.Discharge(pReceiver, telegram)
	} else {
		var dispatchTime = time.Now().Add(delay)
		telegram.SetDispatchTime(dispatchTime)
		md.priorityQ = append(md.priorityQ, telegram)

		Debug_Message("====Delayed telegram from:%s recorded at time %s for:[%s]. Msg is [%d]",
			time.Now(), pSender.Name(), pReceiver.Name(), msg)
	}
}

func (md *MessageDispatcher) DispatchDelayMessages() {
	var currentTime = time.Now()
	var newPriorityQ []*common.Telegram
	for _, item := range md.priorityQ {
		if currentTime.After(item.DispatchTime) {
			var pReceiver = md.entityMgr.GetEntityById(item.Receiver)
			md.Discharge(pReceiver, item)
			fmt.Printf("====Queued telegram ready for dispatch: Sent to [%s]. Msg is [%d]\n",
				pReceiver.Name(), item.Msg)
		} else {
			newPriorityQ = append(newPriorityQ, item)
		}
	}
	md.priorityQ = newPriorityQ
}

func (md *MessageDispatcher) SetEntityMgr(entityMgr *EntityManager) {
	md.entityMgr = entityMgr
}
