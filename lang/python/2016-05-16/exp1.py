
def showmenu():
    prompt = """
    (f)rom
    (t)o
    (i)ncrement
please input: """
    f = t = i = 0
    print prompt
    while not f:
        try:
            f = int(raw_input("Enter (f)rom: "))
        except ValueError, e:
            print 'please input a number'

    while not t:
        try:
            t = int(raw_input("Enter (t)o: "))
        except ValueError, e:
            print 'please input a number'

    while not i:
        try:
            i = int(raw_input("Enter (i)ncrement: "))
        except ValueError, e:
            print 'please input a number'

    for x in xrange(f, t, i):
        print x

if __name__ == '__main__':
    showmenu()
