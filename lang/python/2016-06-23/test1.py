#!/usr/bin/env python
#-*- coding:utf-8 -*-

import urllib2
import urllib

def post(url, data):
    req = urllib2.Request(url)

    opener = urllib2.build_opener(urllib2.HTTPCookieProcessor())
    response = opener.open(req, data)
    return response.read()

def main():
    url = 'http://119.147.23.193:9111/nsdlcallback.aspx'
    data = {'account'      : 10, 
            'addtime'      : '13090394&sdf',
            'custominfo'   : 'test',
            'customorderid': '10001',
            'money'        : 100,
            'orderid'      : '20140210042000000',
            'paytype'      : 'alipay',
            'senddate'     : '13090394',
            'success'      : 1
            }

    sData = urllib.urlencode(data)
    custominfo = '2001&1014&10001&10002&1'
    #orderid = '2014021004200000091';
    orderid = '2014021004200000093'
    #sData = 'account=10&addtime=13090394&custominfo=%s&customorderid=10001&money=100&orderid=%s&paytype=alipay&senddate=13090394&success=1' % (custominfo, orderid)
    data = {'account'       : '10',
            'addtime'       : '13090394',
            'custominfo'    : custominfo,
            'customorderid' : '10001',
            'money'         : '100',
            'orderid'       : orderid,
            'paytype'       : 'alipay',
            'senddate'      : '13090394',
            'success'       : '1'}
    sData = urllib.urlencode(data)
    print "url:%s" % url
    print "params:%s" % sData
    print "resp:%s" % post(url, sData)

if __name__ == '__main__':
    main()
