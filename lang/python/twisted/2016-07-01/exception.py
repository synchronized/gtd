#-*- coding:utf-8 -*-

def falldown():
    raise Exception('I fall down')

def upagain():
    print 'Bug I get up again.'
    reactor.stop()

from twisted.internet import reactor

reactor.callWhenRunning(falldown)
reactor.callWhenRunning(upagain)

print 'Starting the reactor'
reactor.run()
