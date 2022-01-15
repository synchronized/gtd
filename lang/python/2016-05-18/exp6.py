#/usr/bin/env python
# -*- coding: utf-8 -*-

class P():
    def __del__(self):
        print "P.__del__"

class C(P):
    def __init__(self):
        print 'initialized'
    def __del__(self):
        P.__del__(self)

c1 = C()
c2 = c1
c3 = c2

print 'id(c1):', c1
print 'id(c2):', c2
print 'id(c3):', c3

print '-' * 20
del c1
del c2
del c3
print '-' * 20
