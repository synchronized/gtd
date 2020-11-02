package common

import "math"

type IMovingEntity interface {
	IBaseGameEntity
	Velocity() *Vector2d
	Heading() *Vector2d
	Side() *Vector2d
	Mass() float64
	MaxSpeed() float64
	MaxTurnRate() float64

	SetVelocity(val Vector2d)
	SetHeading(val Vector2d)
	SetSide(val Vector2d)
	SetMass(val float64)
	SetMaxSpeed(val float64)
	SetMaxTurnRate(val float64)
	Speed() float64
	SpeedSq() float64
	MaxForce() float64
	SetMaxForce(mf float64)
	IsSpeedMaxedOut() bool

	RotateHeadingToFacePosition(target Vector2d) bool
}

type MovingEntity struct {
	BaseGameEntity
	vVelocity    Vector2d //速度
	vHeading     Vector2d //方向
	vSide        Vector2d //垂直与方向的矢量
	dMass        float64  //质量
	dMaxSpeed    float64  //最大速度
	dMaxForce    float64  //最大力
	dMaxTurnRate float64  //交通工具能旋转的最大速率(弧度/秒)
}

func NewMovingEntity(
	id int, name string,
	position Vector2d,
	radius float64,
	velocity Vector2d,
	maxSpeed float64,
	heading Vector2d,
	mass float64,
	scale Vector2d,
	maxTurnRate float64,
	maxForce float64,
) *MovingEntity {
	var me = &MovingEntity{
		vVelocity:    velocity,
		vHeading:     heading,
		vSide:        *heading.Perp(),
		dMass:        mass,
		dMaxSpeed:    maxSpeed,
		dMaxTurnRate: maxTurnRate,
		dMaxForce:    maxForce,
	}
	me.SetId(id)
	me.SetName(name)
	me.SetPos(position)
	me.SetBRadius(radius)
	me.SetScale(scale)
	return me
}

func (me *MovingEntity) Velocity() *Vector2d {
	return &me.vVelocity
}

func (me *MovingEntity) Heading() *Vector2d {
	return &me.vHeading
}
func (me *MovingEntity) Side() *Vector2d {
	return &me.vSide
}

func (me *MovingEntity) Mass() float64 {
	return me.dMass
}
func (me *MovingEntity) MaxSpeed() float64 {
	return me.dMaxSpeed
}
func (me *MovingEntity) MaxTurnRate() float64 {
	return me.dMaxTurnRate
}

func (me *MovingEntity) SetVelocity(val Vector2d) {
	me.vVelocity = val
}

func (me *MovingEntity) SetHeading(val Vector2d) {
	me.vHeading = val
	me.vSide = *me.vHeading.Perp()
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
func (me *MovingEntity) SetMaxTurnRate(val float64) {
	me.dMaxTurnRate = val
}

func (me *MovingEntity) Speed() float64 {
	return me.vVelocity.Length()
}
func (me *MovingEntity) SpeedSq() float64 {
	return me.vVelocity.LengthSq()
}

func (me *MovingEntity) MaxForce() float64 {
	return me.dMaxForce
}
func (me *MovingEntity) SetMaxForce(mf float64) {
	me.dMaxForce = mf
}

func (me *MovingEntity) IsSpeedMaxedOut() bool {
	return me.dMaxSpeed*me.dMaxSpeed >= me.SpeedSq()
}

func (me *MovingEntity) RotateHeadingToFacePosition(target Vector2d) bool {
	var toTarget *Vector2d = target.OpMinus(me.Pos()).Normalize()

	var dot float64 = me.vHeading.Dot(toTarget)
	dot = math.Min(dot, 1)
	dot = math.Max(dot, -1)

	//return true if the player is facing the target
	var angle float64 = math.Acos(dot)

	if FloatSmaller(angle, 0.0) {
		return true
	}

	if angle > me.dMaxTurnRate {
		angle = me.dMaxTurnRate
	}

	var RotationMatrix C2DMatrix

	RotationMatrix.Rotate(angle * float64(me.vHeading.Sign(toTarget)))
	RotationMatrix.TransformVector2D(&me.vHeading)
	RotationMatrix.TransformVector2D(&me.vVelocity)

	//finally recreate m_vSide
	me.vSide = *me.vHeading.Perp()

	return false
}
