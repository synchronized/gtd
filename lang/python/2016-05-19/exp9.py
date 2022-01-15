#!/usr/bin/env python
#-*- coding:utf-8 -*-

from subprocess import call, Popen, PIPE
import os

def test_call():
    res = call(('cat', '/etc/motd'))
    print 'res:', res

def test_popen():
    f = Popen(('uname', '-a'), stdout=PIPE).stdout
    data = f.readline()
    f.close()
    print data

    print '-'*30
    f = Popen('who', stdout=PIPE).stdout
    data = [eachLine.strip() for eachLine in f]
    f.close()
    for eachLine in data:
        print eachLine

test_popen()
