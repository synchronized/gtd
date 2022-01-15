#!/usr/bin/env python

from werkzeug.wrappers import Response

def application(environ, start_response):
    request = Request(environ)
    text = 'Hello %s!' % request.args.get('name', 'World')
    response = Response(text, minetype='text/plain')
    return response(environ, start_response)
