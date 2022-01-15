#!/usr/bin/env python
#-*- coding:utf-8 -*-

import threading
import time

def timer_hello():
    print "hello world ", time.ctime()

t = threading.Timer(5, timer_hello)

print 'before ', time.ctime()
t.start()
print 'after ', time.ctime()
