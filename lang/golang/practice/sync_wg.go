package main

import (
	"fmt"

	"sync"
)

func test1() {
	var mMap = make(map[int][2]int)
	var a = mMap[1]
	a[0] = 1
	a[1] = 2
	mMap[1] = a

	fmt.Printf("mMap:%#v", mMap)
}

func test2() {
	var wg sync.WaitGroup
	for i:=0; i<10; i++ {
		wg.Add(1)
		go func() {
			wg.Done()
		}()
	}
	wg.Wait()

}

func main() {
	test2()
}
