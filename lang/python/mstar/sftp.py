#!/usr/bin/env python
#-*- coding:utf-8 -*-
import argparse
import paramiko
import os
import sys

config = {
    u"host": u"192.168.1.247",
    u"port": 22,
    u"username": u"sunday"
}

class MstarTransferSftp:
    def __init__(self, host, port, username, keyfile):
        privatekeyfile = os.path.expanduser(keyfile)
        self.mykey = paramiko.RSAKey.from_private_key_file(privatekeyfile)
        self.host = host
        self.port = port
        self.username = username

    def create_sftp(self):
        self.transport = paramiko.Transport((self.host, self.port))
        self.transport.connect(username=self.username, pkey=self.mykey)
        self.sftp = paramiko.SFTPClient.from_transport(self.transport)
        return self.sftp

    def upload(self, local_dir, remote_dir, filename):
        sftp = self.create_sftp()
        file_list = sftp.listdir(remote_dir)

        if filename in file_list:
            stat = sftp.stat(remote_dir + filename)
            f_local = open(local_dir + filename)
            f_local.seek(stat.st_size)
            f_remote = sftp.open(remote_dir + filename, u"a")
            tmp_buffer = f_local.read(100000)
            while tmp_buffer:
                f_remote.write(tmp_buffer)
                tmp_buffer = f_local.read(100000)
            f_remote.close()
            f_local.close()
        else:
            f_local = open(local_dir + filename)
            f_remote = sftp.open(remote_dir + filename, u"w")
            tmp_buffer = f_local.read(100000)
            while tmp_buffer:
                f_remote.write(tmp_buffer)
                tmp_buffer = f_local.read(100000)
            f_remote.close()
            f_local.close()

        self.closse_sftp()

    def closse_sftp(self):
        self.sftp.close()
        self.transport.close()

def mstar_transfer_sftp_fill_getargs(parser):
    parser.add_argument(u"--sftp-host", required=True, help=u"目标主机")
    parser.add_argument(u"--sftp-port", required=True, type=int, help=u"目标端口")
    parser.add_argument(u"--sftp-username", required=True, help=u"目标端口")
    parser.add_argument(u"--sftp-keyfile", default=u"~/.ssh/id_rsa", help=u"目标端口")
    parser.add_argument(u"--sftp-local-dir", required=True, help=u"目标端口")
    parser.add_argument(u"--sftp-remote-dir", required=True, help=u"目标端口")
    parser.add_argument(u"--sftp-filename", required=True, help=u"目标端口")

def __mstar_sftp_main():

    parser = argparse.ArgumentParser()
    mstar_transfer_sftp_fill_getargs(parser)
    args = parser.parse_args()

    sftp = MstarTransferSftp(args.sftp_host, args.sftp_port, args.sftp_username, args.sftp_keyfile)
    sftp.create_sftp()
    sftp.upload(args.sftp_local_dir, args.sftp_remote_dir, args.sftp_filename)

if __name__ == u"__main__":
    __mstar_sftp_main()
