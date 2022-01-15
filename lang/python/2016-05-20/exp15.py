#!/usr/bin/env python
#-*- coding:utf-8 -*-

import threading
from time import sleep, ctime()

loops = (4, 2)

class MyThread(threading.Thread):
    def __init__(self, func, args, name=''):
