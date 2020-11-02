package common

type IState interface {
	Execute(entity IBaseGameEntity)
	Enter(entity IBaseGameEntity)
	Exit(entity IBaseGameEntity)
	//实体接受一个消息执行这个
	OnMessage(entity IBaseGameEntity, msg *Telegram) bool
}

type State struct {
	IState
}

func (s *State) OnMessage(entity IBaseGameEntity, msg *Telegram) bool {
	return false
}
