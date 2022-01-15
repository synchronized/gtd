#!/usr/bin/env python
#-*- coding:utf-8 -*-

from socket import *
from time import ctime

HOST = ''
PORT = 21567
BUFSIZ = 1024
ADDR = (HOST, PORT)

tcpSerSock = socket(AF_INET, SOCK_STREAM)
tcpSerSock.bind(ADDR)
tcpSerSock.listen(5)

while True:
    print 'waiting for connection...'
    tcpCliSock, addr = tcpSerSock.accept()
    print '...connected from:', addr

    while True:
        data = tcpCliSock.recv(BUFSIZ)
        if not data:
            print ' '*4, "client not data send"
            break

        if('exit' == data.strip()):
            sdata = 'bye'
        else:
            sdata = data
        msg = '[%s] %s' % (ctime(), sdata)
        print ' '*4, "send msg:", msg
        tcpCliSock.send(msg)
        if('bye' == sdata):
            break

    tcpCliSock.close()
    print '...connecte from:', addr, ' has close'

tcpSerSock.close()
