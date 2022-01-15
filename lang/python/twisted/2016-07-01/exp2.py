#-*- coding:utf-8 -*-

from twisted.internet import pollreactor
pollreactor.install()

from twisted.internet import reactor
reactor.run()
