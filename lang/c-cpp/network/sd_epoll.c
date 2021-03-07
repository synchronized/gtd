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
int sd_epoll_opt_add(struct sd_epoll_mgr *mgr, struct sd_epoll_opt *opt) {
  if (!mgr) return -1;
  if (!opt) return -2;
  if (opt->next) return -3;

  struct epoll_event ev;
  bzero(&ev, sizeof(ev));
  ev.data.ptr = opt;
  if (opt->flags & SD_EPOLL_IN) ev.events |= EPOLLIN;
  if (opt->flags & SD_EPOLL_OUT) ev.events |= EPOLLOUT;

  if (epoll_ctl(mgr->efd, EPOLL_CTL_ADD, opt->fd, &ev) == -1) {
    fprintf(stderr, "epoll set insertion error: fd=%d\n", opt->fd);
    return -4;
  }
  mgr->curfds++;

  //加入链表
  mgr->tail->next = opt;
  mgr->tail = opt;
  return 0;
}

int sd_epoll_opt_mod(struct sd_epoll_mgr *mgr, struct sd_epoll_opt *opt) {
  if (!mgr) return -1;
  if (!opt) return -2;

  struct epoll_event ev;
  bzero(&ev, sizeof(ev));
  ev.data.ptr = opt;
  if (opt->flags & SD_EPOLL_IN) ev.events |= EPOLLIN;
  if (opt->flags & SD_EPOLL_OUT) ev.events |= EPOLLOUT;

  if (epoll_ctl(mgr->efd, EPOLL_CTL_MOD, opt->fd, &ev) == -1) {
    fprintf(stderr, "epoll set insertion error: fd=%d\n", opt->fd);
    return -4;
  }
  return 0;
}

//从mgr中删除opt
int sd_epoll_opt_del(struct sd_epoll_mgr *mgr, struct sd_epoll_opt *opt) {
  if (!mgr) return -1;
  if (!opt) return -2;

  //查询链表中的位置
  struct sd_epoll_opt *it = &mgr->head;
  while (it != mgr->tail) {
    if (it->next == opt) {
      break;
    }
    it = it->next;
  }
  if (it->next != opt) {
    fprintf(stderr, "opt is not in sd_poll fd:%d\n", opt->fd);
    return -3;
  }
  if (epoll_ctl(mgr->efd, EPOLL_CTL_DEL, opt->fd, NULL) == -1) {
    fprintf(stderr, "del socket '%d' to epoll failed:%s\n", opt->fd, strerror(errno));
    return -1;
  }

  //删除opt
  mgr->curfds--;
  it->next = opt->next;
  if (mgr->tail == opt) {
    mgr->tail = it;
  }
  return 0;
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
      struct epoll_event *ev = &mgr->events[n];
      struct sd_epoll_opt* opt = (struct sd_epoll_opt*)ev->data.ptr;
      if (ev->events & (EPOLLIN | EPOLLHUP)) { //read
        if (opt->handle_read) {
          opt->handle_read(mgr->ctx, opt->ud);
        }
      }
      if (ev->events & EPOLLOUT) {
        if (opt->handle_write) {
          opt->handle_write(mgr->ctx, opt->ud);
        }
      }
      if (ev->events & EPOLLERR) {
        if (opt->handle_error) {
          opt->handle_error(mgr->ctx, opt->ud);
        }
      }
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
