package common

import (
	"testing"
)

func Test_Equal(t *testing.T) {
	// 设置精确度为0.00001
	var a Accuracy = func() float64 { return 0.00001 }
	if !a.Equal(0.11111222, 0.11111222233333) {
		t.Errorf("Equal(%f, %f), Accuracy:%f", 0.11111222, 0.11111222233333, a())
	}
}
