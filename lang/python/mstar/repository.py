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

class MstarRepositoryError(Exception):
    pass

class MstarRepository:
    u"版本管理类，用于获取对应版本，获取版本号等功能"
    def __init__(self, project_path):
        self.project_path = project_path

    def update_version(self, reversion):
        raise MstarRepositoryError(u"must use git or svn implement")

    def make_version_txt(self, reversion, output):
        raise MstarRepositoryError(u"must use git or svn implement")

    def get_version(self, reversion):
        raise MstarRepositoryError(u"must use git or svn implement")

    def export(self, reversion, output):
        raise MstarRepositoryError(u"must use git or svn implement")

class MstarRepositoryGit(MstarRepository):
    u"版本管理类，用于Git相应的实现"

    def update_version(self, reversion):
        project_path = self.project_path

        cmd = [u"git", u"svn", u"rebase"]
        p = subprocess.Popen(cmd, cwd=project_path)
        out, err = p.communicate()
        if p.returncode != 0:
            cmd = [u"git", u"pull"]
            p = subprocess.Popen(cmd, cwd=project_path)
            out, err = p.communicate()
            if p.returncode != 0:
                out, err = p.communicate()
                raise MstarRepositoryError(err)

        cmd = [u"git", u"checkout", reversion]
        p = subprocess.Popen(cmd, cwd=project_path)
        out, err = p.communicate()
        if p.returncode != 0:
            out, err = p.communicate()
            raise MstarRepositoryError(err)

    def make_version_txt(self, reversion, output):
        project_path = self.project_path
        cmd = [u"git", u"--no-pager", u"log", u"--max-count=1"]
        if reversion:
            cmd.append(reversion)
        p = subprocess.Popen(cmd, cwd=project_path, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        out, err = p.communicate()
        if p.returncode != 0:
            raise MstarRepositoryError(err)

        versionFile = u"{}/src/Version.txt".format(output)
        print(u"Version.txt path: {}".format(versionFile))
        with open(versionFile, u"w") as f:
            f.write(out)
            f.close()

    def get_version(self, reversion):
        project_path = self.project_path
        cmd = [u"git", u"rev-parse", reversion]
        p = subprocess.Popen(cmd, cwd=project_path, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        out, err = p.communicate()
        if p.returncode != 0:
            raise MstarRepositoryError(err)
        return out[0:8]

    def export(self, reversion, output):
        project_path = self.project_path
        cmd = u"git archive {} src | tar -x -C {}".format(reversion, output)
        p = subprocess.Popen(args=cmd, cwd=project_path, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                             shell=True, close_fds=True)
        out, err = p.communicate()
        if p.returncode != 0:
            raise MstarRepositoryError(err)
        self.make_version_txt(reversion, output)

class MstarRepositorySvn(MstarRepository):

    def update_version(self, reversion):
        project_path = self.project_path

        cmd = [u"svn", u"update"]
        if reversion:
            cmd = [u"svn", u"update", u"-r", reversion]
        p = subprocess.Popen(cmd, cwd=project_path)
        out, err = p.communicate()
        if p.returncode != 0:
            out, err = p.communicate()
            raise MstarRepositoryError(err)

    def make_version_txt(self, reversion, output):
        project_path = self.project_path
        cmd = [u"svn", u"info"]
        if reversion:
            cmd.append(u"-r")
            cmd.append(reversion)
        p = subprocess.Popen(cmd, cwd=project_path, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        out, err = p.communicate()

        if p.returncode != 0:
            raise MstarRepositoryError(err)
        versionFile = u"{}/src/Version.txt".format(output)

        print(u"Version.txt path: {}".format(versionFile))
        with open(versionFile, u"w") as f:
            f.write(out)
            f.close()

    def get_version(self, reversion):
        project_path = self.project_path
        cmd = [u"svn", u"info"]
        if reversion:
            cmd.append(u"-r")
            cmd.append(reversion)
        p = subprocess.Popen(cmd, cwd=project_path, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        out, err = p.communicate()

        if p.returncode != 0:
            raise MstarRepositoryError(err)
        versionFile = u"{}/src/Version.txt".format(project_path)

        version = u"null"
        list = out.splitlines()
        for str in list:
            match = re.match(r"^(Revision|版本): (\d+)", str)
            if match:
                version = match.group(2)
        return version

    def export(self, reversion, output):
        project_path = self.project_path
        cmd = [u"svn", u"export", u"-r", reversion, u"src", u"{}/src".format(output)]
        p = subprocess.Popen(cmd, cwd=project_path, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        out, err = p.communicate()
        if p.returncode != 0:
            raise MstarRepositoryError(err)
        print(u"make Version.txt")
        self.make_version_txt(reversion, output)

def mstar_repository_fill_getargs(parser):
    parser.add_argument(u"-r", u"--reversion", default=None, help=u"构建版本")

def mstar_repository_get(project_path):
    isgit = False
    if os.path.exists(u"{}/.git".format(project_path)):
        isgit = True

    repository = None
    if isgit:
        repository = MstarRepositoryGit(project_path)
    else:
        repository = MstarRepositorySvn(project_path)
    return repository

def mstar_repository_get_version(project_path, reversion):

    version = u"notfound"
    try:
        repository = mstar_repository_get(project_path)
        version = repository.get_version(reversion)
    except Exception as e:
        raise MstarRepositoryError(e)

    return version

def mstar_repository_check_version(args):
    # 如果传递了版本号直接返回
    if args.reversion: return args.reversion

    reversion = raw_input(u"Please Input Reversion(default HEAD): ")
    if not reversion:
        reversion = u"HEAD"
    return reversion

def __mstar_repository_main():

    parser = argparse.ArgumentParser()
    mstar_repository_fill_getargs(parser)
    args = parser.parse_args()
    reversion = mstar_repository_check_version(args)
    print(u"------------------------------------")
    print(u"reversion: {}".format(reversion))

    currdir = os.path.dirname(os.path.abspath(__file__))
    project_path = os.path.dirname(currdir)
    output = u"{}/build".format(currdir)
    if os.path.exists(output): shutil.rmtree(output)
    if not os.path.exists(output): os.makedirs(output)

    repository = mstar_repository_get(project_path)

    try:
        repository.export(reversion, output)
    except MstarRepositoryError as e:
        pass

if __name__ == u"__main__":
    __mstar_repository_main()
