#include <sys/select.h>
#include <sys/time.h>
#include <stdio.h>

/**

//轮询扫描多个描述符中的任一描述符是否发生响应，或经过一段时间后唤醒
//@param maxfd 指定要检测的描述符的范围 所检测描述符最大值+1
//@paarm readset 可读描述符集
//@param writeset 可写描述符集
//@param exceptset 异常描述符集
//@param timeout 超时时间
//@return 0：超时, -1：出错, >0：准备好的文件描述符数量
int select(int maxfd, fd_set *readset, fd_set *writeset, fd_set *exceptset, const struct timeval *timeout);

//该结构体表示等待超时的时间
struct timeval{
  long tv_sec;//秒
  long tv_usec;//微秒
};

//比如等待10.2秒
struct timeval timeout;
timeoout.tv_sec = 10;
timeoout.tv_usec = 200000;

//将select函数的timeout参数设置为NULL则永远等待

描述符集操作
void FD_ZERO(fd_set *fdset); //初始化描述符集
void FD_SET(int fd, fd_set *fdset); //将一个描述符添加到描述符集
void FD_CLR(int fd, fd_set *fdset); //将一个描述符从描述符集中删除
int FD_ISSET(int fd, fd_set *fdset); //检测指定的描述符是否有事件发生
*/

void sample1() {
  while(1) {
    fd_set rset; //创建一个描述符集rset
    FD_ZERO(&rset); //对描述符集rset清零
    FD_SET(0, &rset); //将描述符0加入到描述符集rset中
    FD_SET(4, &rset); //将描述符4加入到描述符集rset中
    FD_SET(5, &rset); //将描述符5加入到描述符集rset中

    if(select(5+1, &rset, NULL, NULL, NULL) > 0) {
      if(FD_ISSET(0, &rset)) {
        //描述符0可读及相应的处理代码
        printf("%d可读\n", 0);
      }

      if(FD_ISSET(4, &rset)) {
        //描述符4可读及相应的处理代码
        printf("%d可读\n", 4);
      }
      if(FD_ISSET(5, &rset)) {
        //描述符5可读及相应的处理代码
        printf("%d可读\n", 5);
      }
    }
  }
}

int
main() {
  sample1();
  return 0;
}
