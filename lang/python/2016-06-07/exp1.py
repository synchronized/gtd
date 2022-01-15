#!/usr/bin/env python
#-*- coding:utf-8 -*-

import sys
import os
reload(sys)
sys.setdefaultencoding('utf-8')

from twisted.internet.protocol import ServerFactory, ProcessProtocol
from twisted.protocols.basic import LineReceiver
from twisted.python import log
from twisted.internet import reactor

class TailProtocol(ProcessProtocol):
    def __init__(self, write_callback):
        self.write = write_callback

    def outReceive(self, data):
        self.write("begin lastlog\n")
        data = [line for line in data.split('\n') if not line.starswith('==')]
        for d in data:
            self.write(d + '\n')
        self.write('End lastlog\n')

    def processEnded(self, reason):
        if reason.value.exitcode != 0:
            log.msg(reason)

class CmdProtocol(LineReceiver):
    delimiter = '\n'

    def processCmd(self, line):
        if line.startswith('lastlog'):
            tailProtocol = TailProtocol(self.transport.write)
            reactor.spawnProcess(tailProtocol, '/usr/bin/tail',
                                 args=['/usr/bin/tail', -10, '/var/log/syslog'])
        elif line.startswith('exit'):
            self.transport.lostConnection()
        else:
            self.transport.write('command not found.\n')

    def connectionMade(self):
        self.client_ip = self.transport.getPeer()
        log.msg("Client connection from  %s" % self.client_ip)
        if len(self.factory.clients) >= self.factory.clients_max:
            log.msg('Too many connections. Bye!')
            self.client_ip = None
        else:
            self.factory.clients.append(self.client_ip)

    def connectionLost(self, reason):
        log.msg('Lost client connection. Reason: %s' % reason)
        if self.client_ip:
            self.factory.clients.remove(self.client_ip)

    def dataReceived(self, line):
        log.msg('Cmd received from %s : %s' % (self.client_ip, line))
        self.processCmd(line)

class MyFactory(ServerFactory):
    protocol = CmdProtocol

    def __init__(self, clients_max=10):
        self.clients_max = clients_max
        self.clients = []

log.startLogging(sys.stdout)
reactor.listenTCP(9999, MyFactory(2))
reactor.run()
