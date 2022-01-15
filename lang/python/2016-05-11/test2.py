def foo(debug=True):
    if debug:
        print 'in debug mode'
    print 'done'

foo()

foo(False)
