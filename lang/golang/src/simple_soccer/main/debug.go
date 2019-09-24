package main

import (
	"fmt"
	"time"
)

//消息调试信息
func Debug_Message(ctx *SoccerContext, format string, arg ...interface{}) {
	var msg = fmt.Sprintf(format, arg...)
	fmt.Printf("[%s] [MSG] %s\n", time.Now().Format("15:04:05"), msg)
}

//状态调试信息
func Debug_State(ctx *SoccerContext, format string, arg ...interface{}) {
	var msg = fmt.Sprintf(format, arg...)
	fmt.Printf("[%s] [STATE] %s\n", time.Now().Format("15:04:05"), msg)
}
