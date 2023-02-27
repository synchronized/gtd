package practice

import (
	"testing"
)

func BenchmarkMapInsterInt(b *testing.B) {
	var m = make(map[int]int)
	for i := 0; i < b.N; i++ {
		m[i] = i
	}
}

func BenchmarkMapInsterInterface(b *testing.B) {
	var m = make(map[interface{}]interface{})
	for i := 0; i < b.N; i++ {
		m[i] = i
	}
}

func BenchmarkMapGetInt(b *testing.B) {
	var normalMap = make(map[int]int)
	var id int
	for i := 0; i < 100000; i++ {
		id++
		normalMap[id] = id
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		_, _ = normalMap[i]
	}
}

func BenchmarkMapGetInterface(b *testing.B) {
	var normalMap = make(map[interface{}]interface{})
	var id int
	for i := 0; i < 100000; i++ {
		id++
		normalMap[id] = id
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		_, _ = normalMap[i]
	}
}
