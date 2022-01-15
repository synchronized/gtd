package main

import (
	"net"
	"fmt"
	"os"
)

func main() {
	name := "192.168.1.97a"
	ip := net.ParseIP(name)
	if ip == nil {
		fmt.Fprintf(os.Stderr, "Err: 错误的ip格式")
		return;
	}
	mask := ip.DefaultMask()
	network := ip.Mask(mask)

	fmt.Fprintf(os.Stdout, "ip: %s\n", ip.String())
	fmt.Fprintf(os.Stdout, "mask: %s\n", mask.String())
	fmt.Fprintf(os.Stdout, "network: %s\n", network.String())

}
