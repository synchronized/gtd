package practice

import (
	"sort"
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestSliceEmpty(t *testing.T) {
	var arr1 = []int{1, 2, 3}
	assert.Equal(t, len(arr1[:0]), 0)
}

//倒序
func TestSliceSort(t *testing.T) {
	var arr = []int{1, 2, 3, 4, 5, 6}
	var arrb = make([]int, len(arr))
	copy(arrb, arr)
	sort.Slice(arr, func(i, j int) bool {
		return arr[i] > arr[j]
	})

	for i, elem := range arr {
		var ib = len(arr) - i - 1
		var elemb = arrb[ib]
		assert.Equal(t, elem, elemb)
	}
}
