#!/usr/bin/env python
#-*- coding:utf-8 -*-

from twisted.internet import reactor

class Countdown(object):
    counter = 5

    def count(self):
        if self.counter == 0:
            reactor.stop()
        else:
            print self.counter, '...'
            self.counter -= 1
            reactor.callLater(1, self.count)

reactor.callWhenRunning(Countdown().count)
print "start!"
reactor.run()
print "stop!"
