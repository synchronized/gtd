//go:build ignore
// +build ignore

package main

import (
	"fmt"
)

func test1(a, b, c bool) {
	fmt.Printf("a(%t) && b(%t) || c(%t) = %t\n", a, b, c, a && b || c)
}

func test2(a, b bool) {
	fmt.Printf("%t ^ %t = %t\n", a, b, !(a || b) || (a && b))
}

func ()

func main() {
	test1(true, true, true)

	test1(false, true, true)
	test1(true, false, true)
	test1(true, true, false)

	test1(false, false, true)
	test1(false, true, false)
	test1(true, false, false)

	test1(false, false, false)

	test2(true, true)
	test2(true, false)
	test2(false, true)
	test2(false, false)
}
