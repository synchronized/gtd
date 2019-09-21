package common

type IMessageHandler interface {
	HandleMessage(msg Telegram) bool
}
