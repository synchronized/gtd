#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/epoll.h> /* epoll function */

#include "sd_epoll.h"

//初始化sd_epoll_mgr
int sd_epoll_init(struct sd_epoll_mgr *mgr, void *arg) {
  if (mgr == NULL) {
    fprintf(stderr, "mgr is null\n");
    return -1;
  }
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

int sd_epoll_opt_create(struct sd_epoll_opt **pp_opt) {
  if (pp_opt == NULL) {
    fprintf(stderr, "pp_so is null\n");
    return -1;
  }
  *pp_opt = (struct sd_epoll_opt*)malloc(sizeof(struct sd_epoll_opt));
  if (*pp_opt == NULL) {
    fprintf(stderr, "malloc failed\n");
    return -1;
  }
  bzero(*pp_opt, sizeof(struct sd_epoll_opt));
  return 0;
}

//添加
int sd_epoll_opt_add(struct sd_epoll_mgr *mgr, struct sd_epoll_opt *p_so) {
  if (mgr == NULL) {
    fprintf(stderr, "mgr is null\n");
    return -1;
  }
  if (p_so == NULL) {
    fprintf(stderr, "p_so is null\n");
    return -1;
  }
  if (p_so->next != NULL) {
    fprintf(stderr, "p_so already in sd_poll\n");
  }
  bzero(&mgr->ev, sizeof(mgr->ev));
  mgr->ev.events = EPOLLIN | EPOLLET;
  mgr->ev.data.ptr = p_so;
  if (epoll_ctl(mgr->efd, EPOLL_CTL_ADD, p_so->fd, &mgr->ev) == -1) {
    fprintf(stderr, "epoll set insertion error: fd=%d\n", p_so->fd);
    return -1;
  }
  mgr->curfds++;

  //加入链表
  mgr->tail->next = p_so;
  mgr->tail = p_so;
  return 0;
}

//从mgr中删除p_so,并且销毁p_so使用的内存
int sd_epoll_opt_destory(struct sd_epoll_mgr *mgr, struct sd_epoll_opt *p_so) {
  if (sd_epoll_del_from_mgr(mgr, p_so) == -1) {
    return -1;
  }
  free(p_so);
}

//从mgr中删除p_so
int sd_epoll_del_from_mgr(struct sd_epoll_mgr *mgr, struct sd_epoll_opt *p_so) {
  if (mgr == NULL) {
    fprintf(stderr, "mgr is null\n");
    return -1;
  }
  if (p_so == NULL) {
    fprintf(stderr, "p_so is null\n");
    return -1;
  }

  if (epoll_ctl(mgr->efd, EPOLL_CTL_DEL, p_so->fd, &mgr->ev) == -1) {
    fprintf(stderr, "del socket '%d' to epoll failed:%s\n", p_so->fd, strerror(errno));
    return -1;
  }

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
    return -1;
  }
  mgr->curfds--;

  //删除p_so
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
  mgr->runing = 1; //运行中
  while (mgr->runing) {
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
  mgr->runing = 0;
}

int sd_epoll_destory(struct sd_epoll_mgr *mgr) {
  //TODO
}
