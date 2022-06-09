package practice

import (
	"fmt"
)

const (
	mutexLocked      = 1 << iota //锁标志，对应state第一位
	mutexWoken                   //唤醒标志，对应state第二位
	mutexStarving                //饥饿标志，对应state第三位
	mutexWaiterShift = iota      // 等待个数在state的位移
)

func ExampleCostIotaBit() {
	fmt.Printf("mutexLocked      : %d\n", mutexLocked)
	fmt.Printf("mutexWoken       : %d\n", mutexWoken)
	fmt.Printf("mutexStarving    : %d\n", mutexStarving)
	fmt.Printf("mutexWaiterShift : %d\n", mutexWaiterShift)
	// Output:
	// mutexLocked      : 1
	// mutexWoken       : 2
	// mutexStarving    : 4
	// mutexWaiterShift : 3
}

//资源类型定义-与角色绑定
const (
	ResSoccer_None     = iota
	ResSoccer_Money    = 1 //金钱
	ResSoccer_Honor    = 2 //荣誉点
	ResSoccer_SkillExp = 3 //技能经验
	//注意，增加类型后在player_base处增加类型对应属性
	ResSoccer_5 = 5 //技能经验

	ResSoccer_Max = iota + 1
)

func ExampleCostIotaMax() {
	fmt.Printf("ResSoccer_Max :%d\n", ResSoccer_Max)
	// Output: ResSoccer_Max :6
}
