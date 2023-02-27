//go:build ignore
// +build ignore

package main

import (
	"github.com/elliotchance/orderedmap"
	"testing"
)

type OrderMapFixedLength struct {
	*orderedmap.OrderedMap
}

func NewOrderMapFixedLength() *OrderMapFixedLength {
	return &OrderMapFixedLength{
		OrderedMap: orderedmap.NewOrderedMap(),
	}
}

func (omfl *OrderMapFixedLength) FixedLength(maxLength int) {
	for omfl.Len() > maxLength {
		var elem = omfl.Front()
		omfl.Delete(elem.Key)
	}
}

func (omfl *OrderMapFixedLength) Push(maxLength int, key interface{}, value interface{}) {
	omfl.Set(key, value)
	omfl.FixedLength(maxLength)
}

func BenchmarkOrderMapFixedLengthPush(b *testing.B) {
	var m = NewOrderMapFixedLength()
	for i := 0; i < b.N; i++ {
		m.Push(5000, i, i)
	}
}

func BenchmarkOrderdMapSet(b *testing.B) {
	var orderedMap = orderedmap.NewOrderedMap()
	var id int
	for i := 0; i < b.N; i++ {
		id++
		orderedMap.Set(id, id)
	}
}

func BenchmarkOrderdMapGet(b *testing.B) {
	var orderedMap = orderedmap.NewOrderedMap()
	var id int
	for i := 0; i < 100000; i++ {
		id++
		orderedMap.Set(id, id)
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		id++
		_, _ = orderedMap.Get(id)
	}
}

func BenchmarkNormalMapSet(b *testing.B) {
	var normalMap = make(map[interface{}]interface{})
	var id int
	for i := 0; i < b.N; i++ {
		id++
		normalMap[id] = id
	}
}

func BenchmarkNormalMapGet(b *testing.B) {
	var normalMap = make(map[interface{}]interface{})
	var id int
	for i := 0; i < 100000; i++ {
		id++
		normalMap[id] = id
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		_, _ = normalMap[i]
	}
}

type MapEntry struct {
	Key   interface{}
	Value interface{}
}

type SliceMap []*MapEntry

func (pmlil *SliceMap) Append(item *MapEntry) {
	*pmlil = append(*pmlil, item)
}

func (pmlil *SliceMap) FindByFilter(fn func(item *MapEntry) bool) *MapEntry {
	for _, item := range *pmlil {
		if fn(item) {
			return item
		}
	}
	return nil
}

func (mrml *SliceMap) RemoveByFilter(fn func(idx int, item *MapEntry) bool) int {
	var cpsl = (*mrml)[:0]
	for i, elem := range *mrml {
		if !fn(i, elem) {
			cpsl.Append(elem)
		}
	}
	//将删除的列表部分设置为空
	for i := len(cpsl); i < len(*mrml); i++ {
		(*mrml)[i] = nil
	}
	var result = len(*mrml) - len(cpsl)
	*mrml = cpsl
	return result
}

func (mrml *SliceMap) FixedLength(maxLength int) {
	var starIdx = len(*mrml) - maxLength
	if starIdx > 0 {
		*mrml = append((*mrml)[:0], (*mrml)[starIdx:]...)
	}
}

func (pmlil *SliceMap) Push(maxLength int, key interface{}, value interface{}) {
	pmlil.Append(&MapEntry{key, value})
	pmlil.FixedLength(maxLength)
}

func BenchmarkSliceMapFixedLengthPush(b *testing.B) {
	var m SliceMap
	for i := 0; i < b.N; i++ {
		m.Push(5000, i, i)
	}
}
