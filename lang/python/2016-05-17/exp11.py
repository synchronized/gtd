#!/usr/bin/env python

def foo():
    m = 3
    def bar():
        n = 4
        print m + n
        print m
    bar()

foo()
