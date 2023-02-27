//go:build ignore
// +build ignore

package main

import (
	"fmt"
)

type A struct{}
type B struct{}

func main() {
	a1 := A{}
	var i1 int = 1
	a2 := A{}
	var i2 int = 2
	b1 := B{}
	s1 := struct{}{}

	fmt.Sprint(i1, i2)

	fmt.Printf("%p\n", &i1)
	fmt.Printf("%p\n", &i2)

	fmt.Printf("%p\n", &a1)
	fmt.Printf("%p\n", &a2)
	fmt.Printf("%p\n", &b1)
	fmt.Printf("%p\n", &s1)

	m := make(map[A]int)
	m[a1] = 1
	m[a2] = 2
	fmt.Printf("m: %v\n", m)
}
