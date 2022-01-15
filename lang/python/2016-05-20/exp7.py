#!/usr/bin/env python

from twisted.internet import protocol, reactor
from time import ctime

PORT = 21567

class TSServProtocol(protocol.Protocol):
    def connectionMade(self):
        clnt = self.clnt = self.transport.getPeer().host
        print '...connected from:', clnt

    def dataReceived(self, data):
        print '[%s] %s' % (ctime(), data)
        self.transport.write('[%s] %s' % (ctime(), data))

    def connectionLost(self, reason):
        print '...connection lost:', self.clnt
        super(TSServProtocol, self).connectionLost(reason)

class TSServFactory(protocol.Factory):
    protocol = TSServProtocol

def main():
    print 'waiting for connection...'
    reactor.listenTCP(PORT, TSServFactory())
    reactor.run()

if __name__ == '__main__':
    main()
