package main

import (
	"math"
	"math/rand"
	"simple_soccer/common"
)

type RegionType int

//TODO
const (
	Region_Normal   RegionType = 1
	Region_Halfsize RegionType = 2
)

//区域
type Region struct {
	dTop, dLeft, dRight, dBottom float64
	dWidth, dHeight              float64
	vCenter                      common.Vector2d
	iId                          int
}

func NewRegion(left, top, right, bottom float64, id int) *Region {
	var r = &Region{
		dTop:    top,
		dLeft:   left,
		dRight:  right,
		dBottom: bottom,
	}
	r.vCenter = common.Vector2d{(left + right) * 0.5, (top + bottom) * 0.5}
	r.dWidth = math.Abs(right - left)
	r.dHeight = math.Abs(bottom - top)
	return r
}

func (r *Region) Top() float64             { return r.dTop }
func (r *Region) Left() float64            { return r.dLeft }
func (r *Region) Right() float64           { return r.dRight }
func (r *Region) Bottom() float64          { return r.dBottom }
func (r *Region) Width() float64           { return r.dWidth }
func (r *Region) Height() float64          { return r.dHeight }
func (r *Region) Length() float64          { return math.Max(r.Width(), r.Height()) }
func (r *Region) Breadth() float64         { return math.Min(r.Width(), r.Height()) }
func (r *Region) Center() *common.Vector2d { return &r.vCenter }

func (r *Region) GetRandomPosition() common.Vector2d {
	return common.Vector2d{rand.Float64()*(r.dRight-r.dLeft) + r.dLeft,
		rand.Float64()*(r.dBottom-r.dTop) + r.dTop}
}

func (r *Region) Inside(pos common.Vector2d, rtype RegionType) bool {
	if rtype == Region_Normal {
		return pos.X > r.dLeft && pos.X < r.dRight &&
			pos.Y > r.dTop && pos.Y < r.dBottom
	} else {
		var marginX float64 = r.dWidth * 0.25
		var marginY float64 = r.dHeight * 0.25
		return pos.X > (r.dLeft+marginX) && pos.X < (r.dRight-marginX) &&
			pos.Y > (r.dTop+marginY) && pos.Y < (r.dBottom-marginY)
	}
}

func (fp *Region) Render() {
	/*TODO*/
}
