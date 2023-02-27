package practice

import (
	"github.com/huandu/skiplist"
	"math/rand"
	"testing"
	"time"
)

func getSkipListShuffleArr(num int) []int {

	var arr = make([]int, 0, num)
	for i := 0; i < num; i++ {
		arr = append(arr, i)
	}

	rnd := rand.New(rand.NewSource(time.Now().UnixNano()))
	rnd.Shuffle(num, func(i, j int) {
		arr[i], arr[j] = arr[j], arr[i]
	})
	return arr
}

func BenchmarkSkipListInsertInt(b *testing.B) {
	list := skiplist.New(skiplist.Int)

	for i := 0; i < b.N; i++ {
		list.Set(i, i)
	}
}

func BenchmarkSkipListGetInt(b *testing.B) {
	list := skiplist.New(skiplist.Int)
	var arr = getSkipListShuffleArr(b.N)
	for i := 0; i < len(arr); i++ {
		list.Set(arr[i], i)
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		list.Get(i)
	}
}

func BenchmarkSkipListPopInt(b *testing.B) {
	list := skiplist.New(skiplist.Int)
	var arr = getSkipListShuffleArr(b.N * 2)
	for i := 0; i < len(arr); i++ {
		list.Set(arr[i], i)
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		list.RemoveFront()
	}
}
