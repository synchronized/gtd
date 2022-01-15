#-*- coding:utf-8 -*-

import traceback

def stack():
    print "The Python stack:"
    traceback.print_stack()

from twisted.internet import reactor

reactor.callWhenRunning(stack)
reactor.run()
