//go:build ignore
// +build ignore

package main

import "fmt"

func getNilMap() map[int]int {
	return nil
}

func main() {
	var vMap = getNilMap()
	delete(vMap, 1)
	_, exist := vMap[1]
	fmt.Printf("exist:%t\n", exist)

	//done := false
	//go func() {
	//	done = true
	//}()
	//for !done {
	//	fmt.Println("not done!") //not inlined
	//}
	//fmt.Println("done!")
}
