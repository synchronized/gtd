//go:build ignore
// +build ignore

package main

import (
	"fmt"
)

func _bit_test_and_or(a, b, c bool) {
	fmt.Printf("%t && %t || %t = %t\n", a, b, c, a && b || c)
}

func ExampleBitTestAndOr() {
	_bit_test_and_or(true, true, true)
	_bit_test_and_or(false, true, true)
	_bit_test_and_or(true, false, true)
	_bit_test_and_or(true, true, false)
	_bit_test_and_or(false, false, true)
	_bit_test_and_or(false, true, false)
	_bit_test_and_or(true, false, false)
	_bit_test_and_or(false, false, false)

	// Output:
	// true && true || true = true
	// false && true || true = true
	// true && false || true = true
	// true && true || false = true
	// false && false || true = true
	// false && true || false = false
	// true && false || false = false
	// false && false || false = false
}

func ExampleBitAndNor() {
	fmt.Printf("255 &^ 130 = %d\n", 255&^130)
	fmt.Printf("255 & (^130) = %d\n", 255&(^130))

	// Output:
	// 255 &^ 130 = 125
	// 255 & (^130) = 125
}

func ExampleBitTimerMask() {
	const (
		TIME_NEAR_SHIFT  uint32 = 8
		TIME_NEAR        uint32 = (1 << TIME_NEAR_SHIFT)
		TIME_LEVEL_SHIFT uint32 = 6
		TIME_LEVEL       uint32 = (1 << TIME_LEVEL_SHIFT)
		TIME_NEAR_MASK   uint32 = (TIME_NEAR - 1)
		TIME_LEVEL_MASK  uint32 = (TIME_LEVEL - 1)
	)

	fmt.Printf("TIME_NEAR_SHIFT: %d\n", TIME_NEAR_SHIFT)
	fmt.Printf("TIME_NEAR: %b\n", TIME_NEAR)
	fmt.Printf("TIME_LEVEL_SHIFT: %d\n", TIME_LEVEL_SHIFT)
	fmt.Printf("TIME_LEVEL: %b\n", TIME_LEVEL)
	fmt.Printf("TIME_NEAR_MASK: %b\n", TIME_NEAR_MASK)
	fmt.Printf("TIME_LEVEL_MASK: %b\n", TIME_LEVEL_MASK)

	// Output:
	//TIME_NEAR_SHIFT: 8
	//TIME_NEAR: 100000000
	//TIME_LEVEL_SHIFT: 6
	//TIME_LEVEL: 1000000
	//TIME_NEAR_MASK: 11111111
	//TIME_LEVEL_MASK: 111111
}
