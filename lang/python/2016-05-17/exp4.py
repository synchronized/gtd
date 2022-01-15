#!/usr/bin/env python

def tupleVarArgs(arg1, arg2='defaultB', *theRest):
    'display regular args and non-keyword variable args'
    print 'formal arg 1:', arg1
    print 'formal arg 2:', arg2
    for eachXtrArg in theRest:
        print 'another arg:', eachXtrArg

def dictVarArgs(arg1, arg2='defaultB', **theRest):
    'display 2 regular args and keyword variable args'
    print 'formal arg1:', arg1
    print 'formal arg2:', arg2
    for eachXtrArg in theRest.keys():
        print 'Xtra arg %s: %s' % \
            (eachXtrArg, str(theRest[eachXtrArg]))

def main():
    tupleVarArgs('abc')
    print '-'*20
    tupleVarArgs(23, 4.56)
    print '-'*20
    tupleVarArgs('abc', 123, 'xyz', 456.789)
    print '='*20
    dictVarArgs(1220, 740.0, c='grail')
    print '-'*20
    dictVarArgs(arg2='tales', c=123, d='poe', arg1='mystery')
    print '-'*20
    dictVarArgs('one', d=10, e='zoo', men=('freud', 'gaudi'))
    print '*'*20
    tupleVarArgs('abc', 123, 'xyz', 456.789, 123)
    print '-'*20
    dictVarArgs('one', 10, b='zoo', a=('freud', 'gaudi'))



if __name__ == '__main__':
    main()
