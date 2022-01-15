#!/usr/bin/env python 

counter = 0
num = 0
str = ''
while True:
    if counter != 0:
        print('the number must be 0 - 100:')
    str = raw_input('please input your num')
    num = int(str)
    if num < 100 and num > 0:
        break
    counter += 1
