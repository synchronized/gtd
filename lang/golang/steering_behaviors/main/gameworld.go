package main

type GameWorld struct {
}

func (gw *GameWorld) Update(time_elapsed float64) {
	//TODO
}

func (gw *GameWorld) Render() {
	//TODO
}

//标记范围内的所有障碍物
func (gw *GameWorld) TagObstacleWithViewRange(vehicle *Vehicle, dBoxLength float64) {
	//TODO
}
