#-*- coding:utf-8 -*-

import os
import sys

print os.getcwd()
print sys.path[0]
print os.path.realpath(__file__)
print os.path.split(os.path.realpath(__file__))[0]
