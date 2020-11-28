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

from repository import mstar_repository_fill_getargs
from build import mstar_build_fill_getargs
from build import MstarBuild

mstar_datadir_choices = [u"Android", u"EN", u"JP", u"TW", u"XM", u"Yiwan"]

class MstarArchiveError(Exception):
    pass

class MstarArchive:

    def __init__(self, project_path, itemfilter, itemprint, outputfile):
        self.project_path = project_path
        self.itemfilter = itemfilter
        self.itemprint = itemprint
        self.outputfile = outputfile
        compression = zipfile.ZIP_STORED
        try:
            import zlib
            compression = zipfile.ZIP_DEFLATED
        except:
            compression = zipfile.ZIP_STORED
        self.compression = compression

    def zip(self):
        dirname = self.project_path
        itemfilter = self.itemfilter
        zipfilename = self.outputfile
        itemprint = self.itemprint

        filelist = []
        if os.path.isfile(dirname):
            if itemfilter(dirname):
                filelist.append(dirname)
        else :
            for root, dirs, files in os.walk(dirname):
                for name in files:
                    item = os.path.join(root, name)
                    arcname = item[len(dirname):]
                    if itemfilter(arcname):
                        filelist.append(item)

        zf = zipfile.ZipFile(zipfilename, u"w", zipfile.zlib.DEFLATED)
        for tar in filelist:
            arcname = tar[len(dirname):]
            if itemprint:
                itemprint(tar, arcname)
            zf.write(tar,arcname, compress_type=self.compression)
        zf.close()

def mstar_archive_fill_getargs(parser, default_output):

    osystem = platform.system()
    psystem = platform.system().lower()
    default_os = u"linux" if psystem == u"linux" else u"windows"

    # target_choices = [u"all", u"server", u"managerweb", u"applog"]
    datadir_choices = mstar_datadir_choices

    parser.set_defaults(
        osystem = osystem,
        psystem = psystem,
        default_os = default_os,
    )

    parser.add_argument(u"--pack-bin-applog",     default=False, action=u"store_true", help=u"二进制程序-applog")
    parser.add_argument(u"--pack-bin-server",     default=False, action=u"store_true", help=u"二进制程序-server")
    parser.add_argument(u"--pack-bin-managerweb", default=False, action=u"store_true", help=u"二进制程序-managerweb")
    parser.add_argument(u"--pack-data",           default=False, action=u"store_true", help=u"数据包")
    parser.add_argument(u"--pack-src",            default=False, action=u"store_true", help=u"源码包")
    parser.add_argument(u"--pack-data-dir",       default=[],    action=u"append",     help=u"数据包")
    parser.add_argument(u"--output",    default=default_output,  help=u"输出目录")


def mstar_archive_filter_gen(atype, goos, target, datadir):
    u"生成过滤器"

    regexlist = mstar_archive_regex_filter(datadir)

    def file_filter(name):
        name = name.replace(u"\\", "/")
        if name[0] == u"/": name = name[1:]

        mStr = u"{}-{}-{}-{}".format(atype, goos, target, name)

        for regexItem in regexlist:
            match = re.match(regexItem[1], mStr)
            if match:
                return regexItem[0]

        return False

    return file_filter

def mstar_archive_regex_filter(datadir):
    u"默认过滤正则列表"
    binarylist = [
        #archivetype, goos, target, path
        [False, r".*/src/MyTool/.*"],
        [False, r".*/app\.conf$"],
        [False, r".*/ServerConfig\.ini$"],
        [True,  r".*/Version.txt$"],

        [True, r"bin-linux-(?:all|server)-src/MyServerGuard/MyServerGuard$"],
        [True, r"bin-linux-(?:all|server)-src/MyServerAll/MyServerAll$"],
        [True, r"bin-linux-(?:all|server)-src/PlatformApp/PlatformApp$"],
        [True, r"bin-linux-(?:all|managerweb)-src/ManagerWeb/ManagerWeb$"],
        [True, r"bin-linux-(?:all|applog)-src/AppLog/AppLog$"],

        [True, r"bin-windows-(?:all|server)-src/MyServerGuard/MyServerGuard.exe$"],
        [True, r"bin-windows-(?:all|server)-src/MyServerAll/MyServerAll.exe$"],
        [True, r"bin-windows-(?:all|server)-src/PlatformApp/PlatformApp.exe$"],
        [True, r"bin-windows-(?:all|managerweb)-src/ManagerWeb/ManagerWeb.exe$"],
        [True, r"bin-windows-(?:all|applog)-src/AppLog/AppLog.exe$"],

        [True, r"(?:bin|src)-[^-]+-(?:all|server)-src/ServerConfig.ServerConfig.+\.ini$"],
        [True, r"(?:bin|src)-[^-]+-(?:all|server)-src/PlatformApp/conf/app.+\.conf$"],
        [True, r"(?:bin|src)-[^-]+-(?:all|managerweb)-src/ManagerWeb/conf/app.+\.conf$"],
        [True, r"(?:bin|src)-[^-]+-(?:all|managerweb)-src/ManagerWeb/conf/locale.+\.ini$"],
        [True, r"(?:bin|src)-[^-]+-(?:all|applog)-src/AppLog/conf/app.+\.conf$"],

        [True, r"(?:bin|src)-[^-]+-(?:all|managerweb)-src/ManagerWeb/static/.*"],
        [True, r"(?:bin|src)-[^-]+-(?:all|managerweb)-src/ManagerWeb/views/.*"],

        [True, r"src-[^-]+-[^-]+-src/.*\.go$"],

        [True, r"data-[^-]+-[^-]+-src/MyServer/data/[A-Za-z0-9_-]+\.xlsx$"],
        [True, r"data-[^-]+-[^-]+-src/MyServer/data/[A-Za-z0-9_-]+\.datx$"],
    ]

    if datadir:
        # 打包数据的时候
        for item in datadir:
            binarylist.append([True, r"data-[^-]+-[^-]+-src/MyServer/data/{}/[A-Za-z0-9_-]+\.xlsx$".format(item)])
            binarylist.append([True, r"data-[^-]+-[^-]+-src/MyServer/data/{}/[A-Za-z0-9_-]+\.datx$".format(item)])
    return binarylist

def mstar_archive_itemprint(fullpath, path):
    print(u"zip add: {}".format(path))

def mstar_archive_check_datadir():

    datadir_choices = mstar_datadir_choices
    def select_datadir():
        print(u"0=default")
        idx = 0
        for item in datadir_choices:
            idx = idx + 1
            print(u"{}={}".format(idx, item))

        didxs = []
        sDidx = u""
        try:
            sDidx = raw_input(u"Please Input datadir index: ")
            for idxitem in sDidx.split(","):
                didx = int(idxitem.strip())
                if didx > len(datadir_choices) or didx < 0:
                    return -1, []
                if didx != 0 and didx not in didxs:
                    didxs.append(datadir_choices[didx-1])
        except ValueError as e:
            print(u"index format error: {}".format(sDidx))
            return -2, []

        return 0, didxs

    err = -1
    didxs = []
    while err != 0:
        err, didxs = select_datadir()

    return didxs

def __mstar_archive_check_pack_data_dir(pack_data_dir):
    result = []
    if not pack_data_dir: return result
    if len(pack_data_dir) <= 0: return result
    datadir_choices = mstar_datadir_choices
    for item in pack_data_dir:
        itemdir = []
        for _diritem in item.split(","):
            diritem = _diritem.strip()
            if diritem:
                datadir_choices.index(diritem)
                itemdir.append(diritem)
        result.append(itemdir)
    return result

def mstar_archive_check_pack_data_dir(pack_data_dir, pack_data):
    result = []
    if len(pack_data_dir) > 0 or pack_data:
        pack_data_dir = __mstar_archive_check_pack_data_dir(pack_data_dir)
        if len(pack_data_dir) <= 0:
            datadir = []
            try:
                datadir = mstar_archive_check_datadir()
            except KeyboardInterrupt as e2:
                print(u"user interrupt")
                exit(1)
            pack_data_dir.append(datadir)
            print(u"choices datadir: [{}]".format(u",".join(datadir)))
        key_metux = {}

        for data_dir in pack_data_dir:
            data_dir.sort()
            sDatadir = u"-".join(data_dir).lower()
            sDatadir = sDatadir or u"default"
            if key_metux.has_key(sDatadir):
                continue
            result.append([sDatadir, data_dir])
            key_metux[sDatadir] = True
    return result

def __mstar_archive_main():

    currdir = os.path.dirname(os.path.abspath(__file__))
    project_path = os.path.dirname(currdir)
    default_output = u"{}/scripts/build/".format(project_path)

    parser = argparse.ArgumentParser()
    mstar_repository_fill_getargs(parser)
    mstar_build_fill_getargs(parser)
    mstar_archive_fill_getargs(parser, default_output)
    args = parser.parse_args()

    goos = args.goos
    target = args.target
    output = args.output

    if os.path.exists(output): shutil.rmtree(output)
    if not os.path.exists(output): os.makedirs(output)

    sDatadir = "default"
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

    #----------------------------------------------
    # build
    if neet_build:
        env = os.environ.copy()
        env[u"GOOS"] = args.goos
        env[u"GOARCH"] = args.goarch
        env[u"GOPATH"] = project_path

        mBuild = MstarBuild(project_path, env)
        mBuild.print_env_info(args)
        mBuild.build_all()

    #----------------------------------------------
    # pack
    outfile_list = []
    for item in packagelist:
        outputfile = u"mstar-{}-{}-{}-{}.zip".format(item[0], item[1], item[2], version)
        outfile_list.append(outputfile)
        print(u"------------------------------------")
        print(u"archive: {}".format(outputfile))

        itemfilter = mstar_archive_filter_gen(item[0], goos, item[1], item[3])
        mArchive = MstarArchive(project_path, itemfilter, itemprint, u"{}/{}".format(output, outputfile))
        mArchive.zip()

if __name__ == u"__main__":
    __mstar_archive_main()
