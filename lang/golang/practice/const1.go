package main

import (
	"fmt"
)

//资源类型定义-与角色绑定
const (
	ResSoccer_None     = iota
	ResSoccer_Money    = 1 //金钱
	ResSoccer_Honor    = 2 //荣誉点
	ResSoccer_SkillExp = 3 //技能经验
	//注意，增加类型后在player_base处增加类型对应属性
	ResSoccer_5 = 5 //技能经验

	ResSoccer_Max = iota +1
)

func test1() {
	fmt.Printf("ResSoccer_Max:%d\n", ResSoccer_Max)
}

func main() {
	test1()
}
