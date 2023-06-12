//go:build ignore
// +build ignore

package main

import (
	"fmt"
	"time"
)

func test0() { //ok
	var meme = make([][]byte, 0)
	for i := 0; i < 128; i++ {
		var m = make([]byte, 1024*1024*1024)
		for j := 0; j < len(m); j++ {
		}
		meme = append(meme, m)
		fmt.Println("i:", i, "G")
	}
	fmt.Print("meme:", len(meme))
}

func test1() { //kill
	var meme = make([][]byte, 0)
	for i := 0; i < 128; i++ {
		var m = make([]byte, 1024*1024*1024)
		for j := 0; j < len(m); j++ {
			m[j] = byte(j)
		}
		meme = append(meme, m)
		fmt.Println("i:", i, "G")
	}
	fmt.Print("meme:", len(meme))
}

func test2() { //ok
	var meme = make([]*[1024*1024*1024]byte, 0)
	for i := 0; i < 128; i++ {
		var m = new([1024*1024*1024]byte)
		for j := 0; j < len(m); j++ {
			//m[j] = byte(j)
		}
		meme = append(meme, m)
		fmt.Println("i:", i, "G")
	}
	fmt.Print("meme:", len(meme))
}

func test3() { //kill
	var meme = make([]*[1024*1024*1024]byte, 0)
	for i := 0; i < 128; i++ {
		var m = new([1024*1024*1024]byte)
		for j := 0; j < len(m); j++ {
			m[j] = byte(j)
		}
		meme = append(meme, m)
		fmt.Println("i:", i, "G")
	}
	fmt.Print("meme:", len(meme))
}

func test4() { //out of memory
	var data = make([]byte, 1024*1024)
	for i := 0; i < len(data); i++ {
		data[i] = byte(i)
	}
	var meme = make([]byte, 16*1024*1024*1024)
	for i := 0; i < len(meme); i += len(data) {
		//copy(meme[i:], data)
		fmt.Println("i:", i, "G")
	}
	fmt.Print("meme:", len(meme))
}

func test5() { //ok
	var meme = make([][]byte, 0)
	for i := 0; i < 128; i++ {
		var m = make([]byte, 5*1024*1024*1024)
		for j := 0; j < len(m); j++ {
		}
		meme = append(meme, m)
		fmt.Println("i:", i, "x5G")
	}
	fmt.Print("meme:", len(meme))
}

func test6() {
	fmt.Print("+++++++++++\n")
	var m = make([][]byte, 0)
	for i := 0; i < 128; i++ {
		var bs = make([]byte, 1024*1024*1024)
		m = append(m, bs)
		fmt.Println(len(m))
		//time.Sleep(time.Second)
	}
	fmt.Println(len(m))
	for {
		time.Sleep(time.Second)
	}
}

func main() {
	//test0()
	//test1()
	//test2()
	//test3()
	//test4()
	//test5()
	test6()
}
