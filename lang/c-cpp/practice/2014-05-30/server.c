#include <stdio.h>
#include <Winsock2.h>

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif
//#include <windows.h>
//#include <netinet/in.h>
//#pragma comment(lib, "ws2_32")

int main(int argc, char* argv[])
//int main(int argc, char* argv[])
{
  //加载winsock库
  WSADATA wsaData;
  WORD sockVersion = MAKEWORD(2,2);
  //服务器端监听
  struct sockaddr_in sin;
  //接受客户端
  struct sockaddr_in remoteAddr;
  SOCKET sClient;
  
  if( WSAStartup( sockVersion, &wsaData) == 0)
  {

    do{
      //创建套接字
      SOCKET sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
      if( sServer == INVALID_SOCKET)
      {
        printf( "create socket error\n");
        break;
      }

      do{
        //socket 中装入地址信息
        sin.sin_family = AF_INET;
        sin.sin_port = htons(1129);
        sin.sin_addr.S_un.S_addr = INADDR_ANY;

        //绑定套接字
        if( bind( sServer, (LPSOCKADDR)&sin, sizeof( sin)) == SOCKET_ERROR) {
          printf("bind error!\n");
          break;
        }

        //listen 模式
        if( listen( sServer, 5) == SOCKET_ERROR) {
          printf("listen error!\n");
          break;
        }

        //循环接受连接请求
        int nAddrLen = sizeof( SOCKADDR_IN);
        char revData[255];
        while(1) {
          sClient = accept( sServer, (SOCKADDR*)&remoteAddr, &nAddrLen);
          if( sClient == INVALID_SOCKET) {
            printf("accept error\n");
            continue;
          }
          printf("接受来自%s的连接.\n", inet_ntoa(remoteAddr.sin_addr));
          while(true) {
            int ret = recv( sClient, revData, 255, 0);
            if( ret == 0 || (ret == SOCKET_ERROR && WSAGetLastError() == WSAECONNRESET)) {
              printf("%s关闭连接\n", inet_ntoa(remoteAddr.sin_addr));
              if( closesocket( sClient) == SOCKET_ERROR) {
                printf("close client socket error!\n");
                return -1;
              }
              break;
            }
            else {
              revData[ret]='\n';
              printf( "%s", revData);
            }
          }
        }
      }while(0);

      if( closesocket(sServer) == SOCKET_ERROR) {
        printf("close socket error!\n");
        return -1;
      }

    }while(0);
    WSACleanup();
  }
  return 0;
}
