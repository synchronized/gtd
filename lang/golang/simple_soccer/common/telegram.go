package common

import (
	"time"
)

type MessageType int

type Telegram struct {
	Delay        time.Duration
	Sender       int
	Receiver     int
	Msg          MessageType
	ExtraInfo    interface{}
	DispatchTime time.Time
}

func NewTelegram(
	Delay time.Duration,
	Sender int,
	Receiver int,
	Msg MessageType,
	ExtraInfo interface{},
) *Telegram {
	return &Telegram{
		Delay:     Delay,
		Sender:    Sender,
		Receiver:  Receiver,
		Msg:       Msg,
		ExtraInfo: ExtraInfo,
	}
}

func (tg *Telegram) SetDispatchTime(dt time.Time) {
	tg.DispatchTime = dt
}
