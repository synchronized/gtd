#!/usr/bin/env python
#-*- coding:utf-8 -*-

import threading
import time
import random

class MyThread(threading.Thread):
    def __init__(self, cond, *args, **kw):
        super(MyThread, self).__init__(*args, **kw)
        self.cond = cond

    def run(self):
        slenum = random.randint(1, 4)
        print 'cond notify sleep %d second %s' % (slenum, time.ctime())
        time.sleep(slenum)
        self.cond.acquire()
        self.cond.notify()
        self.cond.release()

def test():
    cond = threading.Condition()

    threads = []
    for i in range(5):
        t = MyThread(cond)
        threads.append(t)

    for t in threads:
        t.start()

    for t in threads:
        t.join()

if __name__ == '__main__':
    test()
