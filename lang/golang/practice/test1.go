//go:build ignore
// +build ignore

package main

import (
	"fmt"
	"strconv"
)

func test1() {
	var a int64 = 1111111111
	fmt.Printf("a: %d\n", a)
	var strA = strconv.FormatInt(a, 10)
	fmt.Printf("strA: %s\n", strA)
}

func test2() {
	var a = []int64{1, 2, 3, 4, 5}
	contactsUniIds := make([]int64, len(a))
	copy(contactsUniIds, a)
	fmt.Printf("contactsUniIds: %#v\n", contactsUniIds)
}

func test3() {
	var a = []int64{1, 2, 3, 4, 5, 6, 7, 8, 9}
	var b = append(a[:0], a[2:]...)
	fmt.Printf("b: %#v\n", b)
}

type StructA struct {
	FieldA int
}

func test4() {
	var aMap = make(map[int]StructA)
	var strA = aMap[0]
	aMap[0] = strA
	fmt.Printf("strA: %#v\n", strA)
	strA.FieldA = 10
	aMap[0] = strA
	fmt.Printf("strA: %#v\n", aMap[0])
}

func main() {
	test4()
}
