package main

import (
	"fmt"
)

func main() {
	var arri = []int{1, 2, 4, 5, 6, 0, 3}
	var rmIdList = []int{1}
	var rmMap = make(map[int]int)
	for idx, val := range rmIdList {
		rmMap[val] = idx
	}

	var j = 0
	for i:=0; i<len(arri); i++ {
		var v = arri[i]
		if _, exist := rmMap[v]; !exist {
			arri[j] = arri[i]
			j++
		}
	}
	arri = arri[:j]
	fmt.Printf("arri:%#v\n", arri)
}
