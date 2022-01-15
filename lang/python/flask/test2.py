#!/usr/bin/env python
#-*- coding:utf-8 -*-

#用来处理gitlab自动发布

import sys
reload(sys)
sys.setdefaultencoding('utf8')

import commands
import threading
from flask import Flask,request
app = Flask(__name__)

@app.route('/lion')
def webhook_lion():
    clientip = request.remote_addr
    myClientip = '127.0.0.1'
    gitlabToken = request.headers.get('X-Gitlab-Token', default='')
    myToken = '7d35153a-3f20-4398-94d5-16cc7bfbd57e'
    if (myToken != gitlabToken):
        return 'et'
    if (myClientip != clientip):
        return 'ei'

    return commands.getoutput("git -C /a-git-root-path status")

def jellyfish_webhook_build():
    print commands.getoutput("cd /a-git-root-path; git pull; npm run build")

@app.route('/jellyfish', methods=['POST'])
def webhook_jellyfish():
    clientip = request.remote_addr
    myClientip = '127.0.0.1'
    gitlabToken = request.headers.get('X-Gitlab-Token', default='')
    myToken = '7d35153a-3f20-4398-94d5-16cc7bfbd57e'
    if (myToken != gitlabToken):
        return 'et'
    if (myClientip != clientip):
        return 'ei'

    print 'request.data', request.data
    #thr = threading.Thread(target=jellyfish_webhook_build, args=[])#创建线程
    #thr.start()
    return 'success';

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=10000)
