//go:build ignore
// +build ignore

package main

import (
	"fmt"
)

type IntListFuncEqual func(elem, elemb int) bool
type IntListFuncFilter func(idx int, elem int) bool
type IntListFuncMap func(idx int, elem int) int
type IntListFuncFilterAndMap func(idx int, elem int) (bool, int)

type IntList []int

func (sl *IntList) Equals(_set IntList) bool {
	if len(*sl) != len(_set) {
		return false
	}
	for idx, val := range *sl {
		if val != _set[idx] {
			return false
		}
	}
	return true
}

// Append add the int to the end of IntList
func (sl *IntList) Append(elems ...int) {
	*sl = append(*sl, elems...)
}

// Remove removes the int from IntList
func (sl *IntList) Remove(elem int) int {
	return sl.RemoveByFilter(func(idx int, _elem int) bool {
		return _elem == elem
	})
}

// RemoveByFilter 根据过滤器删除元素(用于批量删除多个的时候)
func (sl *IntList) RemoveByFilter(fn IntListFuncFilter) int {
	return sl.RemoveByFilterMap(func(idx int, elem int) (bool, int) {
		return fn(idx, elem), elem
	})
}

// RemoveByFilterMap 根据过滤器删除元素并且会对不删除的元素执行Map
func (sl *IntList) RemoveByFilterMap(fn IntListFuncFilterAndMap) int {
	var cpsl = (*sl)[:0]
	for i, elem := range *sl {
		if ok, newElem := fn(i, elem); !ok {
			cpsl.Append(newElem)
		}
	}
	//将删除的列表部分设置为空
	var zeroVal int
	for i := len(cpsl); i < len(*sl); i++ {
		(*sl)[i] = zeroVal
	}
	var result = len(*sl) - len(cpsl)
	*sl = cpsl
	return result
}

func main() {
	var data = make(map[int]IntList)
	data[1] = []int{1, 2, 3, 4, 5, 6}
	fmt.Println("data:", data)
	data[1].Remove(2)
	fmt.Println("data:", data)
}
