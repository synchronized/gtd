#include <Winsock2.h>
#pragma comment(lib, "ws2_32")
#include <stdio.h>

int WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData);
int WSACleanup(void);

SOCKET socket(int af, int type, int protocal);
int closesocket(SOCKET s);

int send(SOCKET s, const char FAR* buf, int len, int flags);
int recv(SOCKET s, char FAR* buf, int len, int flags);

struct sockaddr{
	u_short sa_family;
	char sa_data[14];
};
struct in_addr{
	int s_addr;
};
struct sockaddr_in{
	short sin_family;
	u_short sin_port;
	struct in_addr sin_addr;
	char sin_zero[8];
};
int bind(SOCKET s, const struct sockaddr FAR* name, int namelen);
int listen(SOCKET s, int backlog);

SOCKET accept(SOCKET s,struct sockaddr FAR* addr, int FAR* addrlen);
int connect(SOCKET s, const struct sockaddr FAR* name, int namelen);



int main() {
	LPWSADATA wsaData
	WORD wVersionRequested = MAKEWORD(2,1);
	err = WSAStartup( wVersionRequested, &wsaData);

	

	WSACleanup();
	return 
}
