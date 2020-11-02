package common

import "math"

type IBaseGameEntity interface {
	IUpdater
	IRender
	IMessageHandler
	Id() int
	SetId(val int)
	Name() string
	SetName(n string)
	EntityType() int
	SetEntityType(val int)
	IsTagged() bool
	Tag()
	UnTag()

	Pos() *Vector2d
	SetPos(pos Vector2d)
	BRadius() float64
	SetBRadius(val float64)
	Scale() *Vector2d
	SetScale(val Vector2d)
	SetScaleFloat64(val float64)

	//Write()
	//Read()
}

type BaseGameEntity struct {
	IBaseGameEntity
	id         int
	name       string
	entityType int
	bTag       bool

	pos             Vector2d //位置
	scale           Vector2d //缩放比例
	dBoundingRadius float64  //包围半径

}

func (bge *BaseGameEntity) Id() int {
	return bge.id
}

func (bge *BaseGameEntity) SetId(val int) {
	bge.id = val
}

func (bge *BaseGameEntity) Name() string {
	return bge.name
}
func (bge *BaseGameEntity) SetName(n string) {
	bge.name = n
}

func (bge *BaseGameEntity) EntityType() int {
	return bge.entityType
}

func (bge *BaseGameEntity) SetEntityType(val int) {
	bge.entityType = val
}

func (bge *BaseGameEntity) IsTagged() bool {
	return bge.bTag
}

func (bge *BaseGameEntity) Tag() {
	bge.bTag = true
}

func (bge *BaseGameEntity) UnTag() {
	bge.bTag = false
}

func (bge *BaseGameEntity) Pos() *Vector2d {
	return &bge.pos
}

func (bge *BaseGameEntity) SetPos(val Vector2d) {
	bge.pos = val
}

func (bge *BaseGameEntity) BRadius() float64 {
	return bge.dBoundingRadius
}

func (bge *BaseGameEntity) SetBRadius(val float64) {
	bge.dBoundingRadius = val
}

func (bge *BaseGameEntity) Scale() *Vector2d {
	return &bge.scale
}

func (bge *BaseGameEntity) SetScale(val Vector2d) {
	bge.dBoundingRadius *= math.Max(val.X, val.Y) / math.Max(bge.scale.X, bge.scale.Y)
	bge.scale = val
}

func (bge *BaseGameEntity) SetScaleFloat64(val float64) {
	bge.dBoundingRadius *= val / math.Max(bge.scale.X, bge.scale.X)
	bge.scale = Vector2d{val, val}
}
