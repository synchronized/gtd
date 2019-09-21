package main

import (
	"fmt"
	"time"
)

//消息调试信息
func Debug_Message(ctx *SoccerContext, arg ...interface{}) {
	var msg = fmt.SPrintf(arg...)
	fmt.Printf("[%s] [MSG] %s", time.Now(), msg)
}

//状态调试信息
func Debug_State(ctx *SoccerContext, arg ...interface{}) {
	var msg = fmt.SPrintf(arg...)
	fmt.Printf("[%s] [Sstate] %s", time.Now(), msg)
}
