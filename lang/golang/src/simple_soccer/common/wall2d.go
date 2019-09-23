package common

type Wall2d struct {
	vA Vector2d
	vB Vector2d
	vN Vector2d
}

func NewWall2d(from, to Vector2d) *Wall2d {
	var w = &Wall2d{
		vA: from,
		vB: to,
	}
	w.CalculateNormal()
	return w
}

func (w *Wall2d) CalculateNormal() {
	var temp Vecotr2d = *w.vA.OpMinus(w.vB).Normalize()
	w.vN.X = -temp.Y
	w.vN.Y = temp.X
}

func (w *Wall2d) From() Vector2d {
	return w.vA
}

func (w *Wall2d) SetFrom(val Vector2d) {
	w.vA = val
	w.CalculateNormal()
}

func (w *Wall2d) To() Vector2d {
	return w.vB
}

func (w *Wall2d) SetTo(val Vector2d) {
	w.vB = val
	w.CalculateNormal()
}

func (w *Wall2d) Normal() Vector2d {
	return w.vN
}
