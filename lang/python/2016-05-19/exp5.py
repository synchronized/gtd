#!/usr/bin/env python
# -*- coding:utf-8 -*-

class FooFoo(object):
    def foo(self):
        print 'Very important foo() method'

def main():
    bar = FooFoo()
    print 'bar.foo():',
    bar.foo()

    bar.foo = 'It is no longer here.'
    print 'bar.foo:', bar.foo

    del bar.foo
    print 'bar.foo():',
    bar.foo()

if __name__ == '__main__':
    main()
