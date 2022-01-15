#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <string.h>

#define MAXEVENTS 64

/**
 * 函数：
 * 功能：创建和帮idng一个TCP socket
 * 参数：端口
 * 返回值：创建的socket
 */

static int create_and_bind(char *port)
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int s, sfd;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC; //return IPv4 and IPv6 choices
    hints.ai_socktype = SOCK_STREAM; //We want a TCP socket
    hints.ai_flags = AI_PASSIVE; //ALL interface

    s = getaddrinfo( NULL, port, &hints, &result);
    if( s != 0) {
        fprintf(stderr, "getaddrinfo: %s", gai_strerror(s));
        return -1;
    }

    for( rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if( sfd == -1) {
            continue;
        }

        s = bind( sfd, rp->ai_addr, rp->ai_addrlen);
        if( s == 0) {
            //We managed to bind successfully!
            break;
        }

        close(sfd);
    }

    if( rp == NULL) {
        fprintf(stderr, "Could not bind: %s\n", port);
        return -1;
    }

    freeaddrinfo( result);
    return sfd;
}

/**
 * 函数
 * 功能：设置socket为非阻塞的
 */
static int make_socket_non_blocking(int sfd) {
    int flags, s;
    //得到文件状态标志
    flags = fcntl( sfd, F_GETFL, 0);
    if( flags == -1) {
        perror("fcntl");
        return -1;
    }

    //设置文件状态标志
    flags |= O_NONBLOCK;
    s = fcntl(sfd, F_SETFL, flags);
    if( s == -1) {
        perror("fcntl");
        return -1;
    }
    return 0;
}

//端口由参数argv[1]指定
int main( int argc, char *argv[]) {
    int sfd, s;
    int efd;
    struct epoll_event event;
    struct epoll_event *events;

    if(argc != 2) {
        fprintf(stderr, "Usage: %s [port]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    sfd = create_and_bind(argv[1]);
    if( sfd == -1) {
        return -1;
    }

    if( s == -1) {
        perror("listen");
        return -1;
    }

    //除了参数size被忽略外，此函数和epoll_create完全相同
    efd = epoll_create(0);
    if( efd == -1) {
        perror("epoll_create");
        return -1;
    }

    event.data.fd = sfd;
    event.events = EPOLLIN | EPOLLET; //读入，边缘触发方式
    s = epoll_ctl(efd, EPOLL_CTL_ADD, sfd, &event);
    if( s == -1) {
        perror("epoll_ctl");
        return -1;
    }

    //Buffer where events are returned
    events = calloc( MAXEVENTS, sizeof(event));

    //The event loop
    while(1) {
        int n, i;
        n = epoll_wait(efd, events, MAXEVENTS, -1);
        for( i=0; i<n; i++) {
            if( (events[i].events & EPOLLERR) ||
                (events[i].events & EPOLLHUP) ||
                (!(events[i].events & EPOLLIN))) {
                //An error has occured on this fd, or the socketis not
                //ready for reading(why were we notified then?)
                fprintf(stderr, "epoll error\n");
                close(events[i].data.fd);
                continue;
            }
            else if(sfd == events[i].data.fd) {
                //We have a notification on the listening socket, which
                //meansone or more incoming connections.
                while(1) {
                    struct sockaddr in_addr;
                    socklen_t in_len;
                    int infd;
                    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
                    in_len = sizeof(in_addr);
                    infd = accept( sfd, &in_addr, &in_len);
                    if(infd == -1) {
                        if((errno == EAGAIN) ||
                           (errno == EWOULDBLOCK)) {
                            //We have processed all incoming connections.
                            break;

                        }
                        else {
                            perror("accept");
                            break;
                        }
                    }

                    //flag参数：一数字名返回
                    s = getnameinfo(&in_addr, in_len, hbuf, sizeof(hbuf),
                                    sbuf, sizeof(sbuf), NI_NUMERICHOST|NI_NUMERICSERV);
                    if( s == 0) {
                        printf("Accepted connection on descriptor %d (host=%s, port=%s)\n",
                               infd, hbuf, sbuf);
                    }

                    //Make the incoming socket no-blocking
                    //and add it to the list of monitor
                    s = make_socket_non_blocking(infd);
                    if( s == -1) return -1;

                    event.data.fd = infd;
                    event.events = EPOLLIN | EPOLLET;
                    s = epoll_ctl(efd, EPOLL_CTL_ADD, infd, &event);
                    if( s == -1) {
                        perror("epoll_ctl");
                        return -1;
                    }
                }
                continue;
            }
            else {
                //We have data on the fd waiting to be read .
                //Read and display it .We must read whatever data is available
                //completely, as we are running in edge-triggered mode
                //and won't get a notification again for the same data.
                int done = 0;

                while(1) {
                    ssize_t count;
                    char buf[512];

                    count = read(events[i].data.fd, buf, sizeof(buf));
                    if( count == -1) {
                        //If errno == EGAGIN, that means we have read all data
                        //So go back to the mail loop.
                        if( errno != EAGAIN) {
                            perror("read");
                            done = 1;
                        }
                        break;
                    }
                    else if( count == 0) {
                        //End of file. The remote has closed the connection.
                        done = 1;
                        break;
                    }

                    //Write the buffer to standard output
                    s = write(1, buf, count);
                    if( s == -1) {
                        perror("write");
                        return -1;
                    }
                }

                if(done) {
                    printf("closed connection on descriptor %d\n", events[i].data.fd);
                    //Closing the descriptor will make epoll remove it
                    //from the set of descriptors which are monitored.
                    close(events[i].data.fd);
                }
            }
        }
    }

    free(events);
    close(sfd);
    return EXIT_SUCCESS;
}
