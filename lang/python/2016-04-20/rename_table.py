#!/usr/bin/env python

import MySQLdb
import sys

reload(sys)
sys.setdefaultencoding('utf8')

def table_rename(conn, tablename, primarykey, addcolumn):

    conn.autocommit(0)
    cur = conn.cursor()
    #drop template table if exists
    sql = ("DROP TABLE IF EXISTS `tmp_%s` " % (tablename))
    print sql
    cur.execute(sql)
    conn.commit()

    #create template table
    sql = ("CREATE TABLE `tmp_%s` LIKE `%s`" % (tablename, tablename))
    print sql
    cur.execute(sql)
    conn.commit()

    #modify table engine
    sql = ("ALTER TABLE `tmp_%s` ENGINE = InnoDB" % (tablename))
    print sql
    cur.execute(sql)
    conn.commit()

    #create template table
    sql = ("ALTER TABLE `tmp_%s` ADD COLUMN %s" % (tablename, addcolumn))
    print sql
    cur.execute(sql)
    conn.commit()

    #disable keys
    sql = ("/*!40000 ALTER TABLE `tmp_%s` DISABLE KEYS */;" % tablename)
    print sql
    cur.execute(sql)
    conn.commit()

    #insert data
    lastid = 0;
    sql = ("select * from %s where %s > %d order by %s limit 5000"
           % (tablename, primarykey, lastid, primarykey))
    print sql
    cur.execute(sql)
    fieldNames = []
    for field_desc in cur.description:
        fieldNames.append(field_desc[0])
    #end for

    sFieldNames = ",".join(fieldNames)
    rows = cur.fetchall()
    while rows:
        dt_rows = []
        for row in rows:
            dt_row = []
            for i in row:
                if type(i) == unicode or type(i) == str:
                    dt_row.append(i)
                elif i is None:
                    dt_row.append("")
                else:
                    dt_row.append(i)
                # print "gettype(%s):%s" %(str(i), type(i))
            #end for
            # exit
            dt_rows.append(dt_row);

            lastid = row[0]
        #end for
        strfields = ', '.join(['%s']*len(fieldNames))
        sql = ("insert into `tmp_%s`(%s) values(%s)"
               % (tablename, sFieldNames, strfields))
        print sql
        #print dt_rows
        cur.executemany(sql, dt_rows)
        conn.commit()

        sql = ("select * from %s where %s > %s order by %s limit 5000"
               % (tablename, primarykey, str(lastid), primarykey))
        print sql
        cur.execute(sql)
        conn.commit()
        rows = cur.fetchall()

    #end while

    #enable keys
    sql = ("/*!40000 ALTER TABLE `tmp_%s` ENABLE KEYS */;" % tablename)
    print sql
    cur.execute(sql)
    conn.commit();

    #rename
    sql = ("INSERT INTO `tmp_%s`(%s) SELECT %s FROM `%s` WHERE `%s` > %s;"
           % (tablename, sFieldNames, sFieldNames, tablename, primarykey,
              str(lastid)))
    print sql
    cur.execute(sql)
    sql = ("ALTER TABLE `%s` RENAME TO `tmp1_%s`;" % (tablename, tablename))
    print sql
    cur.execute(sql)
    sql = ("ALTER TABLE `tmp_%s` RENAME TO `%s`;" % (tablename, tablename))
    print sql
    cur.execute(sql)
    conn.commit()
    cur.close()

try:
    conn = MySQLdb.connect(
        host        = '127.0.0.1',
        port        = 3306,
        user        = 'root',
        passwd      = '123456',

        db          = 'asdk_beanspay',
        use_unicode = 1,
        charset     = 'utf8',
    )
    tablename = 'payrecord'
    primarykey = 'pr_id'
    addcolumn = "`pr_notify_desc` varchar(512) NOT NULL DEFAULT ''"
    table_rename(conn, tablename, primarykey, addcolumn)

    # tablename = 'userpayrecord'
    # primarykey = 'upr_id'
    # addcolumn = "`upr_real_money` int(11) NOT NULL DEFAULT 0"
    # table_rename(conn, tablename, primarykey, addcolumn)

    conn.close()

except MySQLdb.Error,e:
    print "MySQL Error %d:%s" %(e.args[0], e.args[1])
