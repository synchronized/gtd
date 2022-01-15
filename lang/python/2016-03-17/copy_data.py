
import sys
import MySQLdb

reload(sys)
sys.setdefaultencoding('utf8')

try:
    conn = MySQLdb.connect(
        host='127.0.0.1',
        user='root',
        passwd='123456',
        db='asdk_beanspay',
        port=3306,
        use_unicode = 1,
        charset='utf8')

    lconn = MySQLdb.connect(
        host='127.0.0.1',
        user='root',
        passwd='123456',
        db='asdk_beanspay',
        port=3306,
        use_unicode = 1,
        charset='utf8')
    cur = conn.cursor()

    dt_tab = []
    sql = 'select `a_id`, `a_account`, `a_password`, `a_powers`, `a_serverip`, `a_phone`, `a_op`, `a_imei`, `a_ua`, `a_sdk`, `a_bv`, `a_regip`, `a_addtime`, `a_lastip`, `a_pb`, `a_lasttime`, `a_count`, `a_kickofflinetime`, `a_lock`, `a_firstserverid`, `a_serverid_records`, `a_autoreg`, `a_lastsvr`, `a_channel`, `a_sessionid`, `a_email`, `a_gameid`, `a_othersdkextdata1`, `a_othersdkextdata2`, `a_othersdkextdata3`, `a_othersdkextdata4`, `a_lastimei` from account'
    cur.execute(sql)
    for row in cur.fetchall():
        asdkid = row[1]
        dt_tab.append(asdkid)
        print '.'
#        print row[0], asdkid, row[2], row[3], '---'


    cnt_bad = 0
    lcur = lconn.cursor()
    for asdkid in dt_tab:
        acc_tab = {}

        sql = "select a_id,a_account from account where a_account like '%s%%'" % asdkid
        cur.execute(sql)
        acc_row = cur.fetchone()
        if acc_row:
            acc_tab['asdkid'] = asdkid
            acc_tab['accountid'] = acc_row[0]
            acc_tab['account'] = acc_row[1]
        else:
            print "------bad"
            cnt_bad += 1
            del acc_row
            continue

        sql = "select pp_id from ly2_player_payrecord where pp_accountid='%s'" % acc_tab['accountid']
        pp_row = lcur.execute(sql)
        if not pp_row:

            sql = "select c_serverid,c_playerid,c_charactername ,char_viplevel,char_level from player where a_id ='%s' limit 1" % acc_tab['accountid']
            cur.execute(sql)
            ply_row = cur.fetchone()

            if not ply_row:
                print "+++++++bad"
                cnt_bad += 1
                del acc_row
                continue

            acc_tab['serverid'] = ply_row[0]
            acc_tab['playerid'] = ply_row[1]
            acc_tab['playername'] = ply_row[2]
            acc_tab['viplevel'] = ply_row[3]
            acc_tab['level'] = ply_row[4]

            sql = "insert into ly2_player_payrecord(pp_asdkid,pp_accountid,pp_account,pp_serverid,pp_playerid,pp_playername,pp_viplevel,pp_level) values('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')" % (
                acc_tab.get('asdkid', 0),
                acc_tab.get('accountid', ''),
                acc_tab.get('account', ''),
                acc_tab.get('serverid', 0),
                acc_tab.get('playerid', ''),
                acc_tab.get('playername', ''),
                acc_tab.get('viplevel', 0),
                acc_tab.get('level', 0)
            )
            rnum = lcur.execute(sql)
            print rnum, sql

    lconn.commit()
    lcur.close()
    cur.close()

    conn.close()
    lconn.close()
except MySQLdb.Error,e:
    print "Mysql Error %d: %s" % (e.args[0], e.args[1])
