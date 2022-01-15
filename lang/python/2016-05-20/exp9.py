#!/usr/bin/env python
#-*- coding:utf-8 -*-

import ftplib
import os
import socket

HOST = 'ftp.yzu.edu.tw'
DIRN = 'cygwin/x86'
FILE = 'setup.xz'

def main():
    try:
        f = ftplib.FTP(HOST)
    except (socket.error, socket.gaierror), e:
        print 'ERROR: connect reach "%s"' % HOST
        return

    print '*** Connected to host "%s"' % HOST

    try:
        f.login()
    except ftplib.error_perm:
        print 'ERROR: connect login anonymously'
        f.quit()
        return

    print '*** Logged in as "anonymously"'

    try:
        f.cwd(DIRN)
    except ftplib.error_perm:
        print 'ERROR: connect CD to "%s"' % DIRN
        f.quit()
        return

    print '*** Changed to "%s" folder' % DIRN

    try:
        f.retrbinary('RETR %s' % FILE, open(FILE, 'wb').write)
    except ftplib.error_perm:
        print 'ERROR connect read file "%s"' % FILE
        f.quit()
        os.unlink(FILE)
        return

    print '*** Downloaded "%s" to CWD' % FILE
    f.quit()
    return

if __name__ == '__main__':
    main()
