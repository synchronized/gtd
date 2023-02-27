//go:build ignore
// +build ignore

package main

import (
	"testing"
)

type Point struct {
	X int
	Y int
}

func BenchmarkSimpleStructEqualPoint(b *testing.B) {
	var pointList = make([]*Point, 0, 100000)
	for i := 0; i < 100000; i++ {
		pointList = append(pointList, &Point{i, i})
	}

	b.ResetTimer()
	var pPoint = pointList[0]
	var equalNum int
	for i := 0; i < b.N; i++ {
		var j = i % len(pointList)
		var point = pointList[j]
		if pPoint.X == point.X && pPoint.Y == point.Y {
			equalNum++
		}
	}
	_ = equalNum
}

func BenchmarkSimpleStructEqualStruct(b *testing.B) {
	var pointList = make([]Point, 0, 100000)
	for i := 0; i < 100000; i++ {
		pointList = append(pointList, Point{i, i})
	}

	b.ResetTimer()
	var pPoint = pointList[0]
	var equalNum int
	for i := 0; i < b.N; i++ {
		var j = i % len(pointList)
		var point = pointList[j]
		if pPoint == point {
			equalNum++
		}
	}
	_ = equalNum
}
