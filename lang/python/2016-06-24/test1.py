#!/usr/bin/env python
#-*- coding:utf-8 -*-

import sys
import os

"""将当前进程 fork 为守护进程

    注意：如果你的守护进程是由inetd启动的，不要这样做！inetd完成了
    所有需要做的事情，包括重定向标准文件描述符，需要做的事情只有
    chdir() 和 umask()了
"""

def daemonize(stdin='/dev/null', stdout='/dev/null', stderr='/dev/null'):
    """Fork 当前进程为守护进程，重定向标准文件描述符
        (默认情况下定向到/dev/null)
    """
    #第一次fork
    try:
        if os.fork() > 0:
            sys.exit(0) #第一次 fork 父进程
    except OSError, e:
        sys.stderr.write("fork #1 failed:(%d) %s\n" % (e.errno, e.strerror))
        sys.exit(1)

    #从母体环境脱离
    os.chdir("/")
    os.umask(0)
    os.setsid()

    #第二次 fork
    try:
        pid = os.fork()
        if pid > 0:
            sys.exit(0) #第二次 fork 父进程
    except OSError, e:
        sys.stderr.write("fork #2 failed:(%d) %s\n" % (e.errno, e.strerror))
        sys.exit(1)

    #进程已经是守护进程乐,重定向文件描述符
    for f in sys.stdout, sys.stderr:
        f.flush()

    si = file(stdin, 'r')
    so = file(stdout, 'a+')
    se = file(stderr, 'a+', 0)
    os.dup2(si.fileno(), sys.stdin.fileno())
    os.dup2(so.fileno(), sys.stdout.fileno())
    os.dup2(se.fileno(), sys.stderr.fileno())


def _example_main():
    """示例函数:每秒打印一个数字和时间戳"""
    import time
    sys.stdout.write('Daemon started with pid %d\n' % os.getpid())
    sys.stdout.write('Daemon stdout output\n')
    sys.stderr.write('Daemon stderr output\n')

    c = 0
    while True:
        sys.stdout.write('%d: %s\n' % (c, time.ctime()))
        sys.stdout.flush()
        c = c+1
        time.sleep(1)

if __name__ == '__main__':
    logpath = '/home/sunday/workspace/python/2016-06-24/daemon.log'
    daemonize('/dev/null', logpath, logpath)
    _example_main()

