#!/usr/bin/env python
#-*- coding:utf-8 -*-

import threading
import MySQLdb
from time import sleep

def loop():
    print "start thread"
    sql = 'select * from account limit 100'

    conn = MySQLdb.Connect(
        host        = '127.0.0.1',
        port        = 3306,
        user        = 'root',
        passwd      = '123456',
        db          = 'asdk_beanspay',
        use_unicode = 1,
        charset     = 'utf8'
    )
    cursor = conn.cursor()
    cursor.execute(sql)
    print "execute sql"
    sleep(5)
    print "fetch data"
    print cursor.fetchall()

def main():
    nloop = range(2);

    threads = []
    for i in nloop:
        t = threading.Thread(target=loop, )
        threads.append(t)

    for i in nloop:
        threads[i].start()

    for i in nloop:
        threads[i].join()

if __name__ == '__main__':
    main()
