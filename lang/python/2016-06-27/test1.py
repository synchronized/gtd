#-*- coding:utf-8 -*-

import signal
import time

isrun = True

def sigint_callback(sig, frame):
    global isrun;
    print 'I am going quit after 10 seconds'
    signal.signal(signal.SIGINT, signal.SIG_IGN)

    time.sleep(10)

    isrun = False

def main():
    signal.signal(signal.SIGINT, sigint_callback)
    while isrun:
        print 'I am running'
        time.sleep(1)

if __name__ == '__main__':
    main()

