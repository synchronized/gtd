#!/usr/bin/env python
#-*- coding:utf-8 -*-

import sys
reload(sys)
sys.setdefaultencoding('utf8')

import commands
from flask import Flask,request
app = Flask(__name__)

@app.route('/')
def kangaroo_wap_gitpull():
    clientip = request.remote_addr
    myClientip = '127.0.0.1'
    gitlabToken = request.headers.get('X-Gitlab-Token', default='')
    myToken = '7d35153a-3f20-4398-94d5-16cc7bfbd57e'
    if (myToken != gitlabToken):
        return 'et'
    if (myClientip != clientip):
        return 'ei'

    return commands.getoutput("git -C /a-git-root-path status")

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=10000)
