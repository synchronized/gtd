#!/usr/bin/env python
#-*- coding:utf-8 -*-

import signal
import time

def receive_alarm(signum, stack):
    print 'Alarm :', time.ctime()

signal.signal(signal.SIGALRM, receive_alarm)
signal.alarm(2)

print 'Before', time.ctime()
time.sleep(10)
print 'After', time.ctime()

