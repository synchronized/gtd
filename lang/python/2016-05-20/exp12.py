#!/usr/bin/env python
#-*- coding:utf-8 -*-

import thread
from time import sleep, ctime

loops = [4,2]

def loop(nloop, nsec, lock):
    msg = 'start loop %d at: %s' % (nloop, ctime())
    print msg
    sleep(nsec)
    msg = 'loop %d done at: %s' % (nloop, ctime())
    print msg
    lock.release()

def main():
    print 'starting at:', ctime()
    locks = []
    nloops = range(len(loops))

    for i in nloops:
        lock = thread.allocate_lock()
        lock.acquire()
        locks.append(lock)

    for i in nloops:
        thread.start_new_thread(loop, (i, loops[i], locks[i]))

    for i in nloops:
        while locks[i].locked():
            #print 'test-------'
            pass

    print 'all DONE at:', ctime()

if '__main__' == __name__:
    main()

