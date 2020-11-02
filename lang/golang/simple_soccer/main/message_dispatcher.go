package main

import (
	"fmt"
	"simple_soccer/common"
	"time"
)

const SEND_MSG_IMMEDIATELY = time.Duration(0)

type MessageDispatcher struct {
	priorityQ []*common.Telegram
	ctx       *SoccerContext
}

func NewMessageDispatcher(ctx *SoccerContext) *MessageDispatcher {
	return &MessageDispatcher{
		ctx: ctx,
	}
}

//派发消息
func (md *MessageDispatcher) Discharge(receiver common.IBaseGameEntity, msg *common.Telegram) {
	if !receiver.HandleMessage(msg) {
		var name = "" //receiver.Name()
		fmt.Printf("====Message not handled receiver:[%s] msg id:[%d]\n", name, msg.Msg)
	}
}

func (md *MessageDispatcher) DispatchMsg(
	delay time.Duration,
	sender int,
	receiver int,
	msg common.MessageType,
	ExtraInfo interface{},
) {
	//var pSender = md.ctx.EntityMgr().GetEntityFromID(sender)
	var pReceiver = md.ctx.EntityMgr().GetEntityFromID(receiver)
	if pReceiver == nil {
		Debug_Message(md.ctx, "Warning! No Receiver with ID of [%d] found", receiver)
		return
	}
	var telegram = common.NewTelegram(delay, sender, receiver, msg, ExtraInfo)
	var senderName = ""   //pSender.Name()
	var receiverName = "" //pReceiver.Name()
	if delay <= 0 {
		//TODO msg to str
		Debug_Message(md.ctx, "Instant telegram dispatched at time:[%s] by:[%s] for:[%s]. Msg is:[%d]",
			time.Now(), senderName, receiverName, msg)
		md.Discharge(pReceiver, telegram)
	} else {
		var dispatchTime = time.Now().Add(delay)
		telegram.SetDispatchTime(dispatchTime)
		md.priorityQ = append(md.priorityQ, telegram)

		Debug_Message(md.ctx, "====Delayed telegram from:%s recorded at time %s for:[%s]. Msg is [%d]",
			time.Now(), senderName, receiverName, msg)
	}
}

func (md *MessageDispatcher) DispatchDelayMessages() {
	var currentTime = time.Now()
	var newPriorityQ []*common.Telegram
	for _, item := range md.priorityQ {
		if currentTime.After(item.DispatchTime) {
			var pReceiver = md.ctx.EntityMgr().GetEntityFromID(item.Receiver)
			md.Discharge(pReceiver, item)
			var receiverName = "" //pReceiver.Name()
			Debug_Message(md.ctx, "====Queued telegram ready for dispatch: Sent to [%s]. Msg is [%d]\n",
				receiverName, item.Msg)
		} else {
			newPriorityQ = append(newPriorityQ, item)
		}
	}
	md.priorityQ = newPriorityQ
}
