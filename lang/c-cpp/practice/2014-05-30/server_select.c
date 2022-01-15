#include <stdio.h>
#include <winsock2.h>

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

bool insertsocket(SOCKET *psockarray, SOCKET sock);
void myMessageBox( char* input);

int main(int argc, char* argv[]) {
  //加载winsock库
  WSADATA wsaData;
  WORD sockVersion = MAKEWORD(2,2);
  //服务器端监听地址
  struct sockaddr_in sin;
  SOCKET sServer;
  //接受客户端地址
  struct sockaddr_in remoteAddr;
  SOCKET sClient;

  do{
    if( WSAStartup( sockVersion, &wsaData) !=0 ) {
      printf( "WSAStart fail\n");
      break;
    }
    do{
      sServer = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP);
      if( sServer == INVALID_SOCKET) {
        printf( "socket create fail\n");
        break;
      }
      do{
        u_long u1= 1 ;
        if( ioctlsocket( sServer, FIONBIO,( u_long*)& u1) != NO_ERROR) {
          printf( "socket ioctlsocket error");
          break;
        }
        sin.sin_family = AF_INET;
        sin.sin_port = htons(1129);
        sin.sin_addr.S_un.S_addr = INADDR_ANY;

        //if( bind( sServer, (LPSOCKADDR)&sin, sizeof( sin)) == SOCKET_ERROR){
        if( bind( sServer, (LPSOCKADDR)&sin, sizeof( sin)) == SOCKET_ERROR) {
          printf("bind error\n");
          break;
        }
        if(listen(sServer, 5) == SOCKET_ERROR) {
          printf("listen error\n");
          break;
        }
        //定义套接字数组
        SOCKET socketclientarray[FD_SETSIZE - 1];
        for(int i=0; i<FD_SETSIZE; i++) {
          socketclientarray[i] = INVALID_SOCKET;
        }
        int retSel, nRet;
        char buff[100];
        memset(&buff, 0, sizeof(buff));
        SOCKET clientsocket;
        fd_set readfds,readtmpfds;

        FD_ZERO(&readfds);
        FD_SET(sServer, &readfds);
        struct sockaddr_in remoteAddr;
        int nAddrLen = sizeof( SOCKADDR_IN);
        while(1){
          readtmpfds = readfds;
          retSel = select(0, &readtmpfds, NULL, NULL, NULL);
          if( retSel > 0) {
            for(int i=0; i<(int)readtmpfds.fd_count; i++){
              if(readtmpfds.fd_array[i] == sServer){
                if(readfds.fd_count >= FD_SETSIZE) {
                        continue;
                }
                sockaddr_in remoteAddr;
                int nAddrLen = sizeof( remoteAddr);
                SOCKET sNew = accept( sServer, (SOCKADDR*)&remoteAddr, &nAddrLen);
                FD_SET( sNew, &readfds);
                printf( "accept from:%s\n", inet_ntoa( remoteAddr.sin_addr));
                
              }
              else {
                char cbuf[256];
                memset(cbuf,0,256);        
                int cRecv;
                cRecv = recv(readtmpfds.fd_array[i], cbuf, 256, 0);
                if(cRecv == SOCKET_ERROR) {
                  printf("close client socket:%d\n", readtmpfds.fd_array[i]);
                  closesocket( readtmpfds.fd_array[i]);
                  FD_CLR( readtmpfds.fd_array[i], &readtmpfds);
                }
                else if(cRecv > 0) {
                  //cbuf[cbuf] = 0;
                  printf("recv data from:%d\n %s", readtmpfds.fd_array[i], cbuf);
                }
                else {
                  printf("client socket close\n");
                  closesocket( readtmpfds.fd_array[i]);
                  FD_CLR( readtmpfds.fd_array[i], &readtmpfds);
                }
                
              }
            }
          }
          else if( retSel == 0) {
            printf("timeout %d\n", x);
            if(x<3) {
              x++;
              continue;
            }
            else {
              printf( "timeout exit");
              break;
            }
          }
          else{
            printf("select() Failed, Error:%d\n", WSAGetLastError());
            break;
          }
          //处理接受连接
          /**
          if(FD_ISSET(sServer, &readfds)) {
            clientsocket = accept(sServer, (SOCKADDR*)&remoteAddr, &nAddrLen);
            if(!insertsocket(socketclientarray, clientsocket)) {
              closesocket(clientsocket);
              continue;
            }
            printf( "accept from:%s\n", inet_ntoa( remoteAddr.sin_addr));
          }

          FD_ZERO(&readfds);

          for( int j=0; j<FD_SETSIZE; j++) {
            if( socketclientarray[j] != INVALID_SOCKET){
              FD_SET(socketclientarray[j], &readfds);
            }
          }
          //处理待解决的套接字
          for( int j=0; j<FD_SETSIZE; j++) {
            if( socketclientarray[j] != INVALID_SOCKET && FD_ISSET(socketclientarray[j], &readfds)){
              nRet = recv(socketclientarray[j], buff, sizeof(buff), 0);
              if(nRet == 0 || nRet == INVALID_SOCKET) {
                printf("receive error\n");
                closesocket(socketclientarray[j]);
                socketclientarray[j] = INVALID_SOCKET;
                continue;
              }
              //对数据进行处理
              myMessageBox(buff);
              //MessageBox(buff);
            }
          }
          */
        }
        FD_ZERO(&readfds);
        FD_SET(sServer, &readfds);
        for(int idx=0; idx<FD_SETSIZE; idx++){
          if(socketclientarray[idx] != INVALID_SOCKET) {
            FD_SET(socketclientarray[idx], &readfds);
          }
        }
        
      }while(0);
      closesocket(sServer);
    }while(0);
    WSACleanup();
  }while(0);
}

bool insertsocket(SOCKET *psockarray, SOCKET sock) {
  for(int idx=0; idx<FD_SETSIZE; idx++) {
    if(psockarray[idx] == INVALID_SOCKET)
    {
      psockarray[idx] = sock;
      break;
    }
    if( idx == FD_SETSIZE - 1) {
      return false;
    }
  }
  return true;
}

void myMessageBox( char* input){
  printf( "%s", input);
}
