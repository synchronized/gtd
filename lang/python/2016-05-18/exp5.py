#!/usr/bin/env python
# -*- coding:utf-8 -*-

class AddrBookEntry(object): #类定义
    'address book entry class'
    def __init__(self, nm, ph): #定义构造器
        self.name = nm   #设置name
        self.phone = ph  #设置 phone
        print 'Created instance for:', self.name

    def updatePhone(self, newph): #定义方法
        self.phone = newph
        print 'Updated phone# for:', self.name

    def updatePhoneA(newph): #定义方法
        print 'Updated phone# for:', newph

class EmplAddrBookEntry(AddrBookEntry):
    'Employee Address Book Entry class'
    def __init__(self, nm, ph, em):
        AddrBookEntry.__init__(self, nm, ph)
        #self.empid = id
        self.email = em

    def updateEmail(self, newem):
        self.email = newem
        print 'Updated e-mail address for:', self.name

def main():
    john = AddrBookEntry('John Doe', '408-555-1212')
    AddrBookEntry.updatePhone(john, '523-555-1212')
    updatePhoneA(john)
    # john = AddrBookEntry('John Doe', '408-555-1212')
    # jane = AddrBookEntry('Jane Doe', '650-555-1212')

    # print 'john:',john
    # print 'john.name:', john.name
    # print 'john.phone:', john.phone
    # print 'jane.name:', jane.name
    # print 'jane.phone:', jane.phone

    # john = EmplAddrBookEntry('John Doe', '408-555-1212', 'jhon@spam.doe')
    # print 'john:', john
    # print 'john.name:', john.name
    # print 'john.phone:', john.phone
    # print 'john.email:', john.email
    # john.updatePhone('415-555-1212')
    # print 'john.phone:', john.phone
    # john.updateEmail('john@doe.spam')
    # print 'john.email:', john.email

if __name__ == '__main__':
    main()
