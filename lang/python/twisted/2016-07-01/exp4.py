#-*- coding:utf-8 -*-

import traceback
from twisted.internet import reactor

def stack():
    print 'The python stack'
    traceback.print_stack()

reactor.callWhenRunning(stack)
reactor.run()

