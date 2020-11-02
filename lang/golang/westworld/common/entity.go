package common

type IBaseGameEntity interface {
	SetId(id int)                     //设置id
	Update()                          //更新RunTick
	Id() int                          //id
	SetName(name string)              //设置名字
	Name() string                     //名字
	SetBase(id int, name string)      //设置基本信息
	HandleMessage(msg *Telegram) bool //处理消息
}

type BaseGameEntity struct {
	IBaseGameEntity
	id   int
	name string
}

func (bge *BaseGameEntity) SetId(id int) {
	bge.id = id
}

func (bge *BaseGameEntity) Id() int {
	return bge.id
}

func (bge *BaseGameEntity) SetName(name string) {
	bge.name = name
}

func (bge *BaseGameEntity) Name() string {
	return bge.name
}

//设置基本信息
func (bge *BaseGameEntity) SetBase(id int, name string) {
	bge.id = id
	bge.name = name
}
