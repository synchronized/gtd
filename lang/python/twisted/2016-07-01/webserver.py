#-*- coding:utf-8 -*-

from twisted.web.resource import Resource
from twisted.web import server
from twisted.web import static
from twisted.internet import reactor

PORT = 1234

class ReStructed(Resource):
    def __init__(self, filename, *a):
        """Constructor"""
        self.rst = open(filename).read()

    def render(self, request):
        return self.rst

resource = static.File('htm/')
resource.processors = {'.html':ReStructed}
resource.indexNames = ['index.html']

reactor.listenTCP(PORT, server.Site(resource))
reactor.run()
