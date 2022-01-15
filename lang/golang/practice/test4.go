package main

import (
	"fmt"
)

func main() {
	var arr = []int{10, 20, 30, 40, 50, 60}
	var rangeTime = []int{59, 65}
	var d = 3

	var lastIdx = -1
	var lastBeginTime = rangeTime[0]
	var lastEndTime = rangeTime[1]
	for i, item := range arr {
		if item < rangeTime[0] {
			continue
		}
		if item > rangeTime[1] {
			if (rangeTime[1] - lastBeginTime) < 2*d {
				lastIdx = -2
			}
			fmt.Printf("2\n")
			lastEndTime = rangeTime[1]
			break
		}
		if (item - lastBeginTime) >= 2*d {
			fmt.Printf("1\n")
			lastEndTime = item
			break
		}

		lastIdx = i
		lastBeginTime = item
	}

	var bak = append(make([]int, 0, lastIdx+1), arr[lastIdx+1:]...)
	arr = append(arr[:lastIdx+1], 0)
	arr = append(arr, bak...)

	fmt.Print("lastEndTime:", lastEndTime, ", lastBeginTime:", lastBeginTime, "\n")
	fmt.Printf("lastIdx: %d\n", lastIdx)
	fmt.Print("arrr", arr)
}
