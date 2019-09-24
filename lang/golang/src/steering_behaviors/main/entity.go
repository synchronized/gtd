package main

import "steering_behaviors/common"

type MovingEntity struct {
	common.BaseGameEntity
	vVelocity    Vector2d //速度
	vHeading     Vector2d //方向
	vSide        Vector2d //垂直与方向的矢量
	dMass        float64  //质量
	dMaxSpeed    float64  //最大速度
	dMaxTrunRate float64  //交通工具能旋转的最大速率(弧度/秒)
}

func (me *MovingEntity) Velocity() Vector2d {
	return me.vVelocity
}

func (me *MovingEntity) Heading() Vector2d {
	return me.vHeading
}
func (me *MovingEntity) Side() Vector2d {
	return me.vSide
}

func (me *MovingEntity) Mass() float64 {
	return me.dMass
}
func (me *MovingEntity) MaxSpeed() float64 {
	return me.dMaxSpeed
}
func (me *MovingEntity) MaxTrunRate() float64 {
	return me.dMaxTrunRate
}

func (me *MovingEntity) SetVelocity(val Vector2d) {
	me.vVelocity = val
}

func (me *MovingEntity) SetHeading(val Vector2d) {
	me.vHeading = val
}
func (me *MovingEntity) SetSide(val Vector2d) {
	me.vSide = val
}

func (me *MovingEntity) SetMass(val float64) {
	me.dMass = val
}
func (me *MovingEntity) SetMaxSpeed(val float64) {
	me.dMaxSpeed = val
}
func (me *MovingEntity) SetMaxTrunRate(val float64) {
	me.dMaxTrunRate = val
}

func (me *MovingEntity) Speed() float64 {
	return me.vVelocity.Length()
}
func (me *MovingEntity) SpeedSq() float64 {
	return me.vVelocity.LengthSq()
}
