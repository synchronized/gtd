//go:build ignore
// +build ignore

package main

import (
	"fmt"
)

func ExampleNumberConvert() {
	var a uint32 = 0x7FFFFFFF
	var b uint32 = 0x7FFFFFFF
	fmt.Printf("int64(a*b) = %X\n", int64(a*b))
	fmt.Printf("int64(a)*int64(b) = %X\n", int64(a)*int64(b))

	// Output:
	// int64(a*b) = 1
	// int64(a)*int64(b) = 3FFFFFFF00000001
}
