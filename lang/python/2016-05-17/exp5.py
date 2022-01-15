#!/usr/bin/env python

def newfoo(arg1, arg2, *nkw, **kw):
    'display regular args and all variable args'
    print 'arg1 is:', arg1
    print 'arg2 is:', arg2
    for eachNKW in nkw:
        print 'additional non-keyword arg:', eachNKW
    for eachKW in kw:
        print "additional keyword arg '%s': %s" % \
            (eachKW, kw[eachKW])

def newfoo2(arg1, arg2, *nkw, **kw):
    'display regular args and all variable args'
    print 'arg1 is:', arg1
    print 'arg2 is:', arg2
    for eachKW in kw:
        print "additional keyword arg '%s': %s" % \
            (eachKW, kw[eachKW])
    for eachNKW in nkw:
        print 'additional non-keyword arg:', eachNKW

def main():
    newfoo2('wolf', 3, 'projects', freud=90, gamble=96)
    print '-'*20
    newfoo(10, 20, 30, 40, foo=50, bar=60)
    print '-'*20
    newfoo(2, 4, *(6, 8), **{'foo':10, 'bar':12})
    print '-'*20
    aTuple = (6, 7, 8)
    aDict = {'z': 9}
    newfoo(1, 2, 3, x=4, y=5, *aTuple, **aDict)

if __name__ == '__main__':
    main()
