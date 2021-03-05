#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/epoll.h> /* epoll function */

#include "sd_epoll.h"

//初始化sd_epoll_mgr
int sd_epoll_init(struct sd_epoll_mgr *mgr, void *arg) {
  if (!mgr) return -1;

  mgr->efd = epoll_create(MAXEPOLLSIZE);
  if (mgr->efd == -1) {
    perror("epoll_create");
    return -1;
  }
  mgr->curfds = 0;
  mgr->ctx = arg;
  mgr->tail = &mgr->head;
  mgr->head.next = NULL;
  return 0;
}

//添加
int sd_epoll_opt_add(struct sd_epoll_mgr *mgr, struct sd_epoll_opt *p_so) {
  if (!mgr) return -1;
  if (!p_so) return -2;
  if (p_so->next) return -3;

  struct epoll_event ev;
  bzero(&ev, sizeof(ev));
  ev.data.ptr = p_so;
  if (p_so->flags & SD_EPOLL_IN) ev.events |= EPOLLIN;
  if (p_so->flags & SD_EPOLL_OUT) ev.events |= EPOLLOUT;

  if (epoll_ctl(mgr->efd, EPOLL_CTL_ADD, p_so->fd, &ev) == -1) {
    fprintf(stderr, "epoll set insertion error: fd=%d\n", p_so->fd);
    return -4;
  }
  mgr->curfds++;

  //加入链表
  mgr->tail->next = p_so;
  mgr->tail = p_so;
  return 0;
}

int sd_epoll_opt_mod(struct sd_epoll_mgr *mgr, struct sd_epoll_opt *p_so) {
  if (!mgr) return -1;
  if (!p_so) return -2;

  struct epoll_event ev;
  bzero(&ev, sizeof(ev));
  ev.data.ptr = p_so;
  if (p_so->flags & SD_EPOLL_IN) ev.events |= EPOLLIN;
  if (p_so->flags & SD_EPOLL_OUT) ev.events |= EPOLLOUT;

  if (epoll_ctl(mgr->efd, EPOLL_CTL_MOD, p_so->fd, &ev) == -1) {
    fprintf(stderr, "epoll set insertion error: fd=%d\n", p_so->fd);
    return -4;
  }
  return 0;
}

//从mgr中删除p_so
int sd_epoll_opt_del(struct sd_epoll_mgr *mgr, struct sd_epoll_opt *p_so) {
  if (!mgr) return -1;
  if (!p_so) return -2;

  //查询链表中的位置
  struct sd_epoll_opt *it = &mgr->head;
  while (it != mgr->tail) {
    if (it->next == p_so) {
      break;
    }
    it = it->next;
  }
  if (it->next != p_so) {
    fprintf(stderr, "p_so is not in sd_poll fd:%d\n", p_so->fd);
    return -3;
  }
  if (epoll_ctl(mgr->efd, EPOLL_CTL_DEL, p_so->fd, NULL) == -1) {
    fprintf(stderr, "del socket '%d' to epoll failed:%s\n", p_so->fd, strerror(errno));
    return -1;
  }

  //删除p_so
  mgr->curfds--;
  it->next = p_so->next;
  if (mgr->tail == p_so) {
    mgr->tail = it;
  }
}

int sd_epoll_run(struct sd_epoll_mgr *mgr) {
  if (mgr == NULL) {
    fprintf(stderr, "mgr is null\n");
    return -1;
  }
  int nfds, n;
  mgr->terminate = 0; //运行中
  while (!mgr->terminate) {
    nfds = epoll_wait(mgr->efd, mgr->events, mgr->curfds, -1);
    if (nfds == -1) {
      perror("epoll_wait");
      continue;
    }
    for (n=0; n<nfds; n++) {
      struct sd_epoll_opt* p_so = (struct sd_epoll_opt*)mgr->events[n].data.ptr;
      p_so->handle(mgr, p_so);
    }
  }
  return 0;
}

int sd_epoll_stop(struct sd_epoll_mgr *mgr) {
  if (mgr == NULL) {
    fprintf(stderr, "mgr is null\n");
    return -1;
  }
  mgr->terminate = 1;
}

int sd_epoll_destory(struct sd_epoll_mgr *mgr) {
  if (!mgr) return -1;

  mgr->curfds = 0;
  mgr->ctx = NULL;
  mgr->tail = &mgr->head;
  mgr->head.next = NULL;
  return 0;
}
