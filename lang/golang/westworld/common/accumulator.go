package common

type Accumulator struct {
	val int
}

func NewAccumulator() *Accumulator {
	return &Accumulator{val: 0}
}

func (c *Accumulator) Next() int {
	c.val++
	return c.val
}
