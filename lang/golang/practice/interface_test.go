package practice

import (
	"testing"
)

type ISprite interface {
	GetName() string
}

type Sprite struct {
	Name string
}

func (this *Sprite) GetName() string {
	return this.Name
}

func TestInterfaceNil(t *testing.T) {
	var va ISprite = nil
	var vb *Sprite = nil
	var vc interface{} = va
	var vd interface{} = vb
	if vc != nil {
		t.Logf("vc != nil(%v)", vc)
		t.Fail()
	}
	if vd == nil {
		t.Logf("vd == nil(%v)", vd)
		t.Fail()
	}
}

func TestInterfaceEquals(t *testing.T) {
	var vc interface{} = 1
	var vd interface{} = 1
	var ve interface{} = vd
	if vc != vd {
		t.Logf("vc(%v) != vd(%v)", vc, vd)
		t.Fail()
	}
	if vc != ve {
		t.Logf("vc(%v) != ve(%v)", vc, ve)
		t.Fail()
	}
}
