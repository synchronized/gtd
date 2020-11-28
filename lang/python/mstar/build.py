#!/usr/bin/env python
#-*- coding:utf-8 -*-

import os
import argparse
import subprocess
import platform
import sys

class MstarBuildError(Exception):
    pass

class MstarBuild:

    def __init__(self, project_path, env):
        self.project_path = project_path
        self.env = env
        self.target_process = {
            u"all":         lambda: self.build_all(),
            u"server":      lambda: self.build_server(),
            u"center":      lambda: self.build_item(u"MyServer_Center"),
            u"module":      lambda: self.build_item(u"MyServer_Module"),
            u"game":        lambda: self.build_item(u"MyServer"),
            u"vest":        lambda: self.build_item(u"MyServer_Vestibule"),
            u"gate":        lambda: self.build_item(u"MyServer_Gate"),
            u"login":       lambda: self.build_item(u"MyServer_Login"),
            u"serverall":   lambda: self.build_item(u"MyServerAll"),
            u"platformapp": lambda: self.build_item(u"PlatformApp"),
            u"applog":      lambda: self.build_item(u"AppLog"),
            u"managerweb":  lambda: self.build_item(u"ManagerWeb"),
            u"managerwebex":lambda: self.build_item(u"ManagerWebEx"),
        }


    def print_env_info(self, args):
        print(u"* current system info")
        print(u"platform.system():  {}".format(args.osystem))
        print(u"platform.machine(): {}".format(args.omachine))
        print(u"os:                 {}".format(args.default_os))
        print(u"arch:               {}".format(args.default_arch))
        print(u"build goos:         {}".format(args.goos))
        print(u"build goarch:       {}".format(args.goarch))
        print(u"------------------------------------")

    def build_item(self, path):


        cwd = u"{}/src/{}".format(self.project_path, path)
        cmd = [u"go", u"build", u"-gcflags", u"-N -l"]
        print(u"build {} ...".format(path))
        p = subprocess.Popen(cmd, env=self.env, cwd=cwd)
        returncode = p.wait()
        if returncode != 0:
            out, err = p.communicate()
            raise MstarBuildError(err)

    def build_all(self):
        print(u"build all ...")
        self.build_item(u"MyServerGuard")
        self.build_item(u"MyServerAll")
        self.build_item(u"PlatformApp")
        self.build_item(u"ManagerWeb")
        self.build_item(u"AppLog")

    def build_server(self):
        print(u"build server ...")
        self.build_item(u"MyServerGuard")
        self.build_item(u"MyServerAll")
        self.build_item(u"PlatformApp")

    def build(self, target):
        print(u"build path: {}".format(self.project_path))

        target_process = self.target_process
        if target not in target_process:
            print(u"--target: {} not found".format(target))
            return

        target_process[target]()

def mstar_build_fill_getargs(parser):

    targetlist = [u"all", u"server", u"center", u"module", u"game", u"vest", 
                  u"gate", u"login", u"serverall", u"platformapp", 
                  u"platformdataapp", u"managerweb", u"managerwebex", u"applog"]

    osystem = platform.system()
    omachine = platform.machine()
    psystem = platform.system().lower()
    pplatform = platform.machine().lower()
    default_os= u"linux" if psystem == u"linux" else u"windows"
    default_arch = u"amd64" if pplatform == u"x86_64" or pplatform == u"amd64" else u"386"

    parser.set_defaults(
        osystem=osystem,
        omachine=omachine,
        psystem=psystem,
        pplatform=pplatform,
        default_os=default_os,
        default_arch=default_arch
    )
    parser.add_argument(u"--goos", default=default_os, help=u"操作系统", choices=[u'linux', u'windows'])
    parser.add_argument(u"--goarch", default=default_arch, help=u"cpu架构", choices=[u'amd64', u'386'])
    parser.add_argument(u"--target", default=u"server", help=u"构建的目标", choices=targetlist)
    parser.add_argument(u"--build-path", default=None, help=u"构建目录")

def __mstar_build_main():

    currdir = os.path.dirname(os.path.abspath(__file__))
    project_path = os.path.dirname(currdir)

    parser = argparse.ArgumentParser()
    mstar_build_fill_getargs(parser)
    args = parser.parse_args()

    project_path = os.path.abspath(args.build_path) if args.build_path else project_path

    env = os.environ.copy()
    env[u"GOOS"] = args.goos
    env[u"GOARCH"] = args.goarch
    env[u"GOPATH"] = project_path

    target = args.target
    mBuild = MstarBuild(project_path, env)
    mBuild.print_env_info(args)
    mBuild.build(target)

if __name__ == u"__main__":
    __mstar_build_main()

