#!/usr/bin/env python
#-*- coding:utf-8 -*-

import os
import os.path
import argparse
import subprocess
import platform
import sys
import re
import zipfile
import shutil

from repository import mstar_repository_get
from repository import mstar_repository_get_version
from repository import mstar_repository_fill_getargs
from repository import mstar_repository_check_version
from build import mstar_build_fill_getargs
from build import MstarBuild
from archive import *
from sftp import MstarTransferSftp

def mstar_fill_getargs(parser):
    mtx = parser.add_mutually_exclusive_group()
    mtx.add_argument(u"--export", dest=u"export", action=u"store_true", help=u"导出文件")
    mtx.add_argument(u"--no-export", dest=u"export", action=u"store_false", help=u"不导出文件")
    mtx.set_defaults(export=True)

    parser.add_argument(u"--sftp-host", help=u"目标主机")
    parser.add_argument(u"--sftp-port", type=int, help=u"目标端口")
    parser.add_argument(u"--sftp-username", help=u"目标端口")
    parser.add_argument(u"--sftp-remote-dir", help=u"目标端口")
    parser.add_argument(u"--sftp-keyfile", default=u"~/.ssh/id_rsa", help=u"目标端口")

    parser.add_argument(u"--project-path", default=None, help=u"目标端口")


def __mstar_archive_main():

    currdir = os.path.dirname(os.path.abspath(__file__))

    parser = argparse.ArgumentParser()
    mstar_build_fill_getargs(parser)
    mstar_repository_fill_getargs(parser)
    mstar_archive_fill_getargs(parser)
    mstar_fill_getargs(parser)
    args = parser.parse_args()

    project_path = args.project_path or os.path.dirname(currdir)
    output = args.output or u"{}/scripts/build/".format(project_path)

    goos = args.goos
    target = args.target

    itemprint = mstar_archive_itemprint
    reversion = u""
    version = u""
    needversion = True
    while needversion == True:
        try:
            reversion = mstar_repository_check_version(args)
            version = mstar_repository_get_version(project_path, reversion)
            needversion = False
        except KeyboardInterrupt as e2:
            print u"user interrupt"
            exit(1)
        except Exception:
            needversion = True

    print u"------------------------------------"
    print u"reversion: {}, {}".format(reversion, version)
    if os.path.exists(output): shutil.rmtree(output)
    if not os.path.exists(output): os.makedirs(output)

    sDatadir = u"default"
    packagelist = []

    neet_build = False

    if args.pack_src: packagelist.append([u"src", u"all", u"default", []])
    if args.pack_bin_applog:
        neet_build = True
        packagelist.append([u"bin", u"applog", u"default", []])
    if args.pack_bin_server:
        neet_build = True
        packagelist.append([u"bin", u"server", u"default", []])
    if args.pack_bin_managerweb:
        neet_build = True
        packagelist.append([u"bin", u"managerweb", u"default", []])

    pack_data_dir = mstar_archive_check_pack_data_dir(args.pack_data_dir, args.pack_data)
    for data_item in pack_data_dir:
        packagelist.append([u"data", u"all", data_item[0], data_item[1]])

    workspace = project_path
    #----------------------------------------------
    # export
    if args.export:
        workspace = output
        print u"export path: {}".format(workspace)
        repository = mstar_repository_get(project_path)
        repository.export(reversion, workspace)
    else:
        repository = mstar_repository_get(project_path)
        repository.make_version_txt(reversion, workspace)


    #----------------------------------------------
    # build
    if neet_build:
        env = os.environ.copy()
        env[u"GOOS"] = args.goos
        env[u"GOARCH"] = args.goarch
        env[u"GOPATH"] = workspace

        mBuild = MstarBuild(workspace, env)
        mBuild.print_env_info(args)
        mBuild.build(args.target)

    #----------------------------------------------
    # pack
    outfile_list = []
    print u"workspace: {}".format(workspace)
    print u"output: {}".format(output)
    for item in packagelist:
        outputfile = u"mstar-{}-{}-{}-{}.zip".format(version, item[0], item[1], item[2])
        outfile_list.append(outputfile)
        print u"------------------------------------"
        print u"archive: {}".format(outputfile)

        itemfilter = mstar_archive_filter_gen(item[0], goos, item[1], item[3])
        mArchive = MstarArchive(workspace, itemfilter, itemprint, u"{}/{}".format(output, outputfile))
        mArchive.zip()

    #----------------------------------------------
    # sftp
    if args.sftp_host and args.sftp_port and args.sftp_username and args.sftp_remote_dir:
        print u"------------------------------------"
        print u"sftp-server: {}@{}:{}:{}".format(args.sftp_username, args.sftp_host, args.sftp_port, args.sftp_remote_dir)
        sftp = MstarTransferSftp(args.sftp_host, args.sftp_port, args.sftp_username, args.sftp_keyfile)
        sftp.create_sftp()
        for item in outfile_list:
            print u"    item: {}".format(item)
            sftp.upload(output, args.sftp_remote_dir, item)

if __name__ == u"__main__":
    __mstar_archive_main()
