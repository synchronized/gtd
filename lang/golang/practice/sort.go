package main

import (
	"sort"
	"fmt"
)

func main() {
	var arr = []int{1,2,3,4,5,6}
	sort.Slice(arr, func(i, j int) bool {
		return arr[i] > arr[j]
	})
	fmt.Printf("arr: %#v\n", arr)
}
