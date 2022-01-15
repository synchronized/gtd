package main

import (
	"os"
	"os/signal"
	"syscall"
	"log"
)

func main() {
	sc := make(chan os.Signal)
	signal.Notify(sc, syscall.SIGHUP, syscall.SIGINT, syscall.SIGTERM, syscall.SIGQUIT)


	select {
	case sig := <-sc:
		log.Printf("收到退出信号[%s]\n", sig.String())
	}

	log.Printf("exit\n")
}
