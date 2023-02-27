package practice

import (
	"container/heap"
	"math/rand"
	"testing"
	"time"
)

type IntList []int

func (il *IntList) Len() int           { return len(*il) }
func (il *IntList) Swap(i, j int)      { (*il)[i], (*il)[j] = (*il)[j], (*il)[i] }
func (il *IntList) Less(i, j int) bool { return (*il)[i] < (*il)[j] }
func (il *IntList) Push(x interface{}) { *il = append(*il, x.(int)) }
func (il *IntList) Pop() interface{}   { l := len(*il); r := (*il)[l-1]; *il = (*il)[:l-1]; return r }

func getShuffleArr(num int) []int {

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

func BenchmarkHeapInsertInt(b *testing.B) {
	var hp IntList
	heap.Init(&hp)
	var arr = getShuffleArr(b.N)

	b.ResetTimer()
	for i := 0; i < len(arr); i++ {
		heap.Push(&hp, arr[i])
	}

}

func BenchmarkHeapGetInt(b *testing.B) {
	var hp IntList
	heap.Init(&hp)
	var arr = getShuffleArr(b.N * 2)

	for i := 0; i < len(arr); i++ {
		heap.Push(&hp, arr[i])
	}
	b.ResetTimer()

	for i := 0; i < b.N; i++ {
		heap.Pop(&hp)
	}
}
