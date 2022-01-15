#!/usr/bin/env python
#-*- coding:utf-8 -*-

import time
import logging
import threading

logging.basicConfig(
    level = logging.DEBUG,
    format = '(%(threadName)-10s) %(message)s')

def worker(event):
    logging.debug('waiting for redis ready...')
    event.wait()
    logging.debug('redis read, and connect to redis server and do some work [%s]', time.ctime())
    time.sleep(1)

readis_ready = threading.Event()
threads = []
for i in range(2):
    t = threading.Thread(target=worker, args=(readis_ready,), name='t'+str(i))
    threads.append(t)

for t in threads:
    t.start()

logging.debug('first of all, check redis server, make sure it is ok, and then'
'trigger the redis ready event')
time.sleep(3)
readis_ready.set()

for t in threads:
    t.join()
