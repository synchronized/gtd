#include <stdio.h>
//#include <windows.h>
#include <Winsock2.h>
//#pragma comment(lib, "ws2_32.dll")
#define PORT 1129
#define ADDRESS "127.0.0.1"
#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

int main() {
  //加载winsock
  WSADATA wsaData;
  WORD sockVersion = MAKEWORD(2,2);
  if( WSAStartup( sockVersion, &wsaData) != 0)
  {

    do{
      //创建套接字
      SOCKET sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
      if( sClient == INVALID_SOCKET)
      {
        printf("create socket error\n");
        break;
      }

      do{
        //socket 装入远程地址信息
        SOCKADDR_IN remote;
        remote.sin_family = AF_INET;
        remote.sin_port = htons(1129);
        remote.sin_addr.S_un.S_addr = inet_addr(ADDRESS);

        if( connect( sClient, (SOCKADDR*)&remote, sizeof(SOCKADDR)) == SOCKET_ERROR)
        {
          printf("connect error\n");
          break;
        }

        while(true)
        {
          char SendData[255];
          int i,ch;
          for(i=0;(i<254)&&((ch=getchar())!=EOF)&&(ch!='\n'); i++)
          {
            SendData[i] = (char)ch;
          }
          SendData[i] = '\n';
          SendData[i+1] = '\0';
          send( sClient, SendData, i+2, 0);
        }
      }while(0);


      if(closesocket(sClient) == SOCKET_ERROR)
      {
        printf("close socket error");
        return 0;
      }
    }
    WSACleanup();
  }
  return 0;
}
