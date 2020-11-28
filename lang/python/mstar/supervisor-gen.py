#!/usr/bin/env python
#-*- coding:utf-8 -*-

import os
import argparse
from jinja2 import Environment
from jinja2 import FileSystemLoader
import sys

def getargs():
    parser = argparse.ArgumentParser()
    #parser.add_argument("-v", "--verbose", action="store_true", default=False,
    #                    help="显示详细日志")
    parser.add_argument(u"--gate-num", default=1, type=int, help=u"启动网关数量")
    parser.add_argument(u"--game-num", default=1, type=int, help=u"启动游戏服务器数量")
    parser.add_argument(u"--prefix",   default=u"mstar", type=str, help=u"服务器组名称")
    parser.add_argument(u"--managerweb", action=u"store_true",
            default=False, help=u"是否生成管理后台")

    return parser.parse_args()

def main():

    args = getargs()

    currdir=os.path.dirname(os.path.abspath(__file__))
    project_path=os.path.dirname(currdir)

    params = {
            u"project_path": project_path,
            u"prefix": args.prefix,
            u"managerweb": args.managerweb,
            }

    env = Environment(loader=FileSystemLoader(currdir, u"utf-8"))
    serverlist = []

    if args.game_num > 1:
        serverlist = [
            {u"name":u"center", u"numprocs": 1, u"params": u"center"},
            {u"name":u"module", u"numprocs": 1, u"params": u"module"},
            {u"name":u"login",  u"numprocs": 1, u"params": u"login"},
            {u"name":u"gate",   u"numprocs": args.gate_num, u"params": u"gate"},
            {u"name":u"game",   u"numprocs": args.game_num, u"params": u"game"},
            {u"name":u"vest",   u"numprocs": args.game_num + 1, u"params": u"vest"},
        ]
    else:
        serverlist = [
            {u"name":u"serverall", u"numprocs": 1, u"params": u"center servernum:1 allinone:2"},
        ]

    params[u"serverlist"] = serverlist
    template = env.get_template(u"supervisor.conf.j2")
    print(template.render(params))

if __name__ == u"__main__":
    main()
