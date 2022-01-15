#!/usr/bin/env python
# -*- coding:utf-8 -*-

class TestStaticMethod:
    @staticmethod
    def foo():
        print 'calling static method foo（）'

class TestClassMethod:
    @classmethod
    def foo(cls):
        print 'calling class method foo()'
        print 'foo() is part of class:', cls.__name__

def main():
    stm = TestStaticMethod()
    TestStaticMethod.foo()
    stm.foo()

    tcm = TestClassMethod()
    TestClassMethod.foo()
    tcm.foo()

if __name__ == '__main__':
    main()
