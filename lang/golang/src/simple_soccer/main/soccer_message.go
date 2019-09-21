package main

const (
	Msg_ReceiveBall     common.MessageType = 1 //接球
	Msg_PassToMe        common.MessageType = 2 //传球给我
	Msg_SupportAttacker common.MessageType = 3 //助攻
	Msg_GoHome          common.MessageType = 4 //回家
	Msg_Wait            common.MessageType = 5 //等待
)

var msgMap map[common.MessageType]string

func init() {
	msgMap = map[common.MessageType]string{
		Msg_ReceiveBall:     "Msg_ReceiveBall",
		Msg_PassToMe:        "Msg_PassToMe",
		Msg_SupportAttacker: "Msg_SupportAttacker",
		Msg_GoHome:          "Msg_GoHome",
		Msg_Wait:            "Msg_Wait",
	}
}

func MessageToString(int msg) string {
	var result, ok = msgMap[int]
	if !ok {
		return "INVALID MESSAGE!!"
	}
	return result
}
