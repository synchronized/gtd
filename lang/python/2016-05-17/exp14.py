#!/usr/bin/env python

x = 10
def foo():
    y = 5
    bar = lambda : x + y
    print bar()

foo()
