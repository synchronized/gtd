#!/usr/bin/env python
# -*- coding:utf-8 -*-

class DevNull2(object):
    def __get__(self, obj, typ=None):
        print 'Accessing attribute... ignoring'
        return '__get__'

    def __set__(self, obj, val):
        print 'Attempt to assign %r... ignoring' % (val)

class C2(object):
    foo = DevNull2()

class DevNull3(object):
    def __init__(self, name=None):
        self.name = name
    def __get__(self, obj, type=None):
        print 'Accessing [%s]... ignoring' % (self.name)
    def __set__(self, obj, val):
        print 'Assigning %r to [%s]... ignoring' % (val, self.name)

class C3(object):
    foo = DevNull3('foo')

def main():
    # c2 = C2()
    # print "c2.foo = 'bar':",
    # c2.foo = 'bar'
    # print "x = c2.foo:",
    # x = c2.foo
    # print 'C2.foo contains:', x

    c3 = C3()
    print "c3.foo = 'bar':",
    c3.foo = 'bar'
    print "x = c3.foo:",
    x = c3.foo
    print 'c3.foo contains:', x
    print '-'*30
    print 'Let us try to sneak it into c3 instance...'
    c3.__dict__['foo'] = 'bar'
    print "x = c3.foo:",
    x = c3.foo
    print 'c3.foo contains:', x
    print "c3.__dict__['foo'] constains: %r" % \
        c3.__dict__['foo'], "... why?!?"


if __name__ == '__main__':
    main()
