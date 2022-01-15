
def longest():
    return max(len(x.strip()) for x in open('/etc/motd', 'r'))

print longest()
