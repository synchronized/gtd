
import math

def isprime(n):
    s = int(math.floor(math.sqrt(n)) + 1)
    for i in xrange(2, s):
        if n % i == 0:
            return False
    return True

def getfactors(n):
    for i in xrange(1, n+1):
        if n % i == 0:
            yield i

def factorization(n):
    s = int(math.floor(math.sqrt(n)) + 1)
    L = []
    fact = 0
    for i in xrange(2, s):
        if n % i == 0:
            fact = i
            L.append(fact)
            break
    else:
        L.append(int(n))
        return L
    L.extend(factorization(n/fact))
    return L

def main():
    #for i in getfactors(1024):
    #    print i
    print factorization(1024)

if __name__ == '__main__':
    main()
