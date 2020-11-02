package common

type IState interface {
	Execute(entity interface{})
	Enter(entity interface{})
	Exit(entity interface{})
	//实体接受一个消息执行这个
	OnMessage(entity interface{}, msg *Telegram) bool
}

type State struct {
	IState
}

func (s *State) OnMessage(entity interface{}, msg *Telegram) bool {
	return false
}
