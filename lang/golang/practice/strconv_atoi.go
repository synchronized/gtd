package main

import (
	"strconv"

	log "github.com/sirupsen/logrus"
)

func test1() {
	var i, err = strconv.Atoi("")
	log.Info("i:", i)
	log.Error("err:", err)
}

func main() {
	test1()
}
