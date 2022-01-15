#!/usr/bin/env python

from random import randint as ri

def main():
    print [n for n in [ri(1,99) for i in range(9)] if n%2]

if __name__ == '__main__':
    main()
