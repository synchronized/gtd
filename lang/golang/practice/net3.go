package main

import (
	"net"
	"fmt"
	"os"
)

func main() {
	domain := "www.baidu.com"
	ipAddr, err := net.ResolveIPAddr("ip", domain)
	if err != nil {
		fmt.Fprintf(os.Stderr, "err: %s\n", err.Error())
		return
	}
	fmt.Fprintf(os.Stdout, "%s IP: %s, Network: %s, Zone: %s\n", ipAddr.String(), ipAddr.IP, ipAddr.Network(), ipAddr.Zone)

	ns, err := net.LookupHost(domain)
	if err != nil {
		fmt.Fprintf(os.Stderr, "Err: %s\n", err.Error())
		return
	}

	for _, n := range ns {
		fmt.Fprintf(os.Stdout, "ns item: %s\n", n)
	}

}
