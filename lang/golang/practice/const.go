package main

import(
	"fmt"
)

const (
	mutexLocked = 1 << iota //锁标志，对应state第一位
	mutexWoken              //唤醒标志，对应state第二位
	mutexStarving           //饥饿标志，对应state第三位
	mutexWaiterShift = iota // 等待个数在state的位移
)


func main() {
	fmt.Printf("mutexLocked:%d\n", mutexLocked)
	fmt.Printf("mutexWoken:%d\n", mutexWoken)
	fmt.Printf("mutexStarving:%d\n", mutexStarving)
	fmt.Println()

	fmt.Printf("1<<3: %d\n", 1<<3)
	fmt.Printf("mutexWaiterShift:%d\n", mutexWaiterShift)

	var new = 256-1
	fmt.Printf("new:%d\n", new)
	new &^= mutexWoken
	fmt.Printf("new:%d\n", new)

}
