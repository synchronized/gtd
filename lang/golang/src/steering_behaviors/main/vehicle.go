package main

type Vehicle struct {
	MovingEntity
	pWorld    *GameWorld
	pSteering *SteeringBehaviors
}

func (v *Vehicle) Update(time_elapsed float64) {
	var steeringForce Vector2d = v.pSteering.Calculate()
	var acceleration Vector2d = steeringForce.OpDevive(v.Mass())
	var vel = v.Velocity()
	//使用加速度计算数度
	vel.OpAdd(acceleration.OpMultiply(time_elapsed))
	//确保不超过最大速度
	vel.Truncate(v.MaxSpeed())
	v.SetVelocity(vel)
	//更新位置
	v.SetPos(v.Pos().OpMultiply(time_elapsed))

	//如果速度大于一个很小的值，更新朝向
	if vel.lengthSq() > vel.AccuracyVal() {
		var heading = vel.Normalize()
		v.SetHeading(heading)
		v.SetSide(heading.Perp())
	}
}

func (v *Vehicle) Render() {
	//TODO
}
func (v *Vehicle) HandleMessage(msg Telegram) bool {
	//TODO
	return false
}

func (v *Vehicle) World() *GameWorld {
	return v.pWorld
}
