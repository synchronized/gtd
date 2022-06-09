package practice

import (
	"fmt"
	"net"
	"testing"

	"github.com/stretchr/testify/assert"
)

func GetFreePort() (int, error) {
	addr, err := net.ResolveTCPAddr("tcp", "localhost:0")
	if err != nil {
		return 0, err
	}

	l, err := net.ListenTCP("tcp", addr)
	if err != nil {
		return 0, err
	}
	defer l.Close()
	return l.Addr().(*net.TCPAddr).Port, nil
}

func ExampleNetParseIP() {
	name := "192.168.1.97"
	ip := net.ParseIP(name)
	defaultMask := ip.DefaultMask()
	ones, bits := defaultMask.Size()

	mask := net.IPv4Mask(255, 255, 0, 0)
	network := ip.Mask(mask)

	telnetPort, _ := net.LookupPort("tcp", "telnet")

	fmt.Printf("IP             : %s\n", ip.String())
	fmt.Printf("DefaultMask    : %s\n", defaultMask.String())
	fmt.Printf("Network        : %s\n", network.String())
	fmt.Printf("Ones : %d Bits : %d\n", ones, bits)

	fmt.Printf("Service Telnet : %d\n", telnetPort)

	// Output:
	// IP             : 192.168.1.97
	// DefaultMask    : ffffff00
	// Network        : 192.168.0.0
	// Ones : 24 Bits : 32
	// Service Telnet : 23
}

func TestGetFreePort(t *testing.T) {
	port, err := GetFreePort()
	assert.Equal(t, err, nil)
	assert.Equal(t, port > 0 && port < 65535, true)
}
