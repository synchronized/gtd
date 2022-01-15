package main

import (
	"fmt"
	"path/filepath"
)

func main() {
	var workPath = "/home/"
	var runPath = "../workdoc"
	var a, err = filepath.Abs(fmt.Sprint(workPath, "/", runPath, "/XXX.exe"))
	var b, err1 = filepath.Abs(filepath.Join(workPath, runPath, "XXX.exe"))
	fmt.Printf("a:%s", a )
	if err != nil {
		fmt.Printf("err:%s", err.Error())
	}
	fmt.Printf("\n")
	fmt.Printf("b:%s", b)
	if err1 != nil {
		fmt.Printf("err1:%s", err1.Error())
	}
	fmt.Printf("\n")
	fmt.Println(filepath.Join("a", "b", "d"))
}
