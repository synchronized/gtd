
import string

def sample_output():
    prompt = """
SAMPLE OUTPUT 1
---------------"""
    while True:
        try:
            f = int(raw_input("Enter begin value: "))
            break
        except ValueError:
            print "please input a number"

    while True:
        try:
            e = int(raw_input("Enter end value: "))
            break
        except ValueError:
            print "please input a number"

    hasprintable = False
    for i in range(f, e + 1):
        if chr(i) in string.printable:
            hasprintable = True
            break

    if hasprintable:
        print '%-10s%-10s%-10s%-10s%-10s' % ('DEC', 'BIN', 'OCT', 'HEX', 'ASCII')
    else:
        print '%-10s%-10s%-10s%-10s' % ('DEC', 'BIN', 'OCT', 'HEX')

    for i in range(f, e + 1):
        binint = (8-len(bin(i)[2:])%8)*'0' + bin(i)[2:]
        if chr(i) in string.printable:
            print '%-10d%-10s%-10o%-10x%-10s' % (i, binint, i, i, chr(i))
        else:
            print '%-10d%-10s%-10o%-10x' % (i, binint, i, i)

sample_output()
