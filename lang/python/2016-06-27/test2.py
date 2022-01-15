#-*- coding:utf-8 -*-

import MySQLdb
import urllib2
import urllib
import hashlib
import json
import sys
#reload(sys)
#sys.setdefaultencoding('utf-8')

def md5(str):
    m = hashlib.md5()
    m.update(str)
    return m.hexdigest()

def getgameslist():
    conn = MySQLdb.connect(
        host = '127.0.0.1',
        port = 3306,
        user = 'root',
        passwd = '123456',
        # host        ='127.0.0.1',
        # port        = 13306,
        # user        ='asdk',
        # passwd      ='VfCEPbV4Mt9UNBmx',

        db = 'asdk_beanspay',
        use_unicode = 1,
        charset = 'utf8'
    )

    sql = ("select ginfo_id as gameid,pay_way as payids from gamesinfo "
           #"where pay_way like '%12%' "
           "where ginfo_id in('100079100250', '100079100212')"
    )

    cur = conn.cursor(MySQLdb.cursors.DictCursor);
    cur.execute(sql)
    res = cur.fetchall()
    data = {}
    for row in res:
        gameid = row['gameid']
        payids = row['payids']

        payidlist = payids.split(',')
        if unicode(14) in payidlist:
            data[gameid] = payids
        else:
            data[gameid] = payids + ',14'
        continue
        # if unicode(12) in payidlist:
        #     data[gameid] = payids + ',14'
        #     continue
    return data

def protoRequest(host, protoName, data):
    url = 'http://%s/mgrapi.php?gameparam=%s' % (host, protoName)
    signkey = '/5gQK41GrCzUv2Zu35O78IDOQu8c/v3o2Q+P9C2t7gg='
    mysignstr = ''
    keys = data.keys()
    keys.sort()
    for k in keys:
        v = data[k]
        if isinstance(k, str):
            k = v.decode('utf8')
        if isinstance(v, str):
            v = v.decode('utf8')
        if len(mysignstr) > 0:
            mysignstr += '&'
        mysignstr += '%s=%s' % (k, v)
    mysignstr += '&key=%s' % (signkey)
    mysign = md5(mysignstr.encode('utf8'))
    data['sign'] = mysign
    datastr = urllib.urlencode(data)
    req = urllib2.Request(url, data=datastr)
    resp = urllib2.urlopen(req)
    respContent = resp.read();
    # print 'url:%s' % url
    # print 'params:%s' % datastr
    # print 'mysignstr:%s' % mysignstr
    # print 'resp:%s' % respContent
    return respContent

def getgameinfobyurl(host, gameid):
    protoName = 'getgamesinfo'
    data = {
        u'gameidlist': gameid
    }
    resp = protoRequest(host, protoName, data)
    decodejson = json.loads(resp)
    return decodejson

def setgameinfobyurl(host, data):
    protoName = u'setgamesinfo'
    resp = protoRequest(host, protoName, data)
    decodejson = json.loads(resp)
    return decodejson

def main():
    host = u'gameapp.asdk.local'
    #host = '120.25.14.118:8001'
    #host = '112.74.65.143:8001'
    data = getgameslist()
    for gameid in data.keys():
        newpayway = data[gameid]
        print 'gameid:%s payway:%s' % (gameid, newpayway)
        resp = getgameinfobyurl(host, gameid)
        if resp['code'] != '0':
            print 'error %s getgameinfo failed' % gameid
            sys.exit(1)
        gameinfo = resp['data'][gameid]
        gameinfo['pay_way'] = newpayway
        gameinfo['game_name'] = gameinfo['game_name'].encode('utf-8')
        resp = setgameinfobyurl(host, gameinfo)
        if resp['code'] != '0':
            print 'error %s getgameinfo failed' % gameid
            sys.exit(1)
        print '%s:%s' % (resp['code'], resp['msg'])

    print data


if __name__ == '__main__':
    main()
