#!/usr/bin/env python

def counter(start_at=0):
    count = start_at
    while True:
        val = (yield count)
        if val is not None:
            count = val
        else:
            count += 1

def main():
    count = counter(5)
    print 'count.next():', count.next()
    print 'count.next():', count.next()
    print 'count.send(9):', count.send(9)
    print 'count.next():', count.next()
    count.close()
    #count.next() #StopIteration

def countToFour1():
    for eachNum in range(5):
        print eachNum,
    print '.'

def countToFour2(n):
    for eachNum in range(n, 5):
        print eachNum,
    print '.'

def countToFour3(n=1):
    for eachNum in range(n, 5):
        print eachNum,
    print '.'

if __name__ == '__main__':
    for n in [2,4,5]:
        #countToFour1(n)
        countToFour2(n)
        countToFour3(n)
        print '-'*20

    countToFour1()
    #countToFour2()
    countToFour3()
