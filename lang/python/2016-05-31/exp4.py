#!/usr/bin/env python
#-*- coding:utf-8 -*-

import threading
import time

class MyThread(threading.Thread):
    def run(self):
        global num
        time.sleep(1)

        if mutex.acquire(1):
            num = num + 1
            msg = self.name + 'set num to ' + str(num)
            print msg
            mutex.release()

num = 0
mutex = threading.Lock()

def test():
    threads = []
    for i in range(5):
        t = MyThread()
        threads.append(t)

    for t in threads:
        t.start()

    for t in threads:
        t.join()

if __name__ == '__main__':
    test()