package main

import (
	"fmt"
)


func test1() {
	var arr1 = []int {1, 2, 3}
	fmt.Println("arr1:", arr1[:0])
}

func main() {
	test1()
}
