//go:build ignore
// +build ignore

package main

import (
	"fmt"
)

func test1() {
	var mMap = make(map[int]map[int]int)
	var mMap2 = mMap[1]
	fmt.Printf("mMap2: %#V\n", mMap2)
	if mMap2[2] == 0 {
		fmt.Println("mMap2[2] == 0 ")
	} else {
		fmt.Println("mMap2[2] != 0 ")
	}
}

const SoccerClubRecentPlayerPointsNum = 5

var RecentPlayerPoints []int

func test2(PlayerPoint int) {
	var num = len(RecentPlayerPoints)
	var slen = SoccerClubRecentPlayerPointsNum - 1
	if num >= SoccerClubRecentPlayerPointsNum {
		RecentPlayerPoints = append(RecentPlayerPoints[:0], RecentPlayerPoints[num-slen:]...)
	}
	RecentPlayerPoints = append(RecentPlayerPoints, PlayerPoint)
	fmt.Printf("RecentPlayerPoints:%#v\n", RecentPlayerPoints)
}

func test3() {
	test2(1)
	test2(2)
	test2(3)
	test2(5)
	test2(4)
	test2(6)
	test2(9)
	test2(8)
	test2(7)
}

func test4() {
	var level = 11
	var rang [2]int = [2]int{10, 25}
	var lr = (level - rang[0]) * 40 / (rang[1] - rang[0])
	fmt.Printf("lr: %d\n", lr)
}

func main() {
	test4()
}
