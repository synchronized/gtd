package main

import (
	"net"
	"fmt"
	"os"
)

func main() {
	port, err := net.LookupPort("tcp", "telnet")
	if err != nil {
		fmt.Fprintf(os.Stderr, "找不到服务:%s\n", err.Error())
		return
	}

	fmt.Fprintf(os.Stdout, "telnet port: %d\n", port)
}
