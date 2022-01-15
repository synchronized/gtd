#!/usr/bin/env python

def average(als):
    isum = reduce(lambda x, y:x+y, als)
    return isum/len(als)

if __name__ == '__main__':
    als = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    print average(als)
