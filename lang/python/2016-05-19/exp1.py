#!/usr/bin/env python
# -*- coding:utf-8 -*-


class HotelRoomCalc(object):

    'Hotel room rate calculator'
    def __init__(self, rt, sales=0.085, rm=0.1):
        '''HotelRoomCalc default arguments:
        sales tax == 8.5% and room tax == 10% '''
        self.salesTax = sales
        self.roomTax = rm
        self.roomRate = rt

    def calcTotal(self, days=1):
        'Calculate total; default to daily rate'
        f = (self.roomRate * (1 + self.roomTax + self.salesTax))
        daily = round(f, 2)
        return float(days) * daily

def main():
    sfo = HotelRoomCalc(299)
    print 'sfo.calcTotal():', sfo.calcTotal()
    print 'sfo.calcTotal(2):', sfo.calcTotal(2)

    print '-'*20
    sea = HotelRoomCalc(189, 0.086, 0.058) #new instance
    print 'sea.calcTotal():', sea.calcTotal()
    print 'sea.calcTotal(4):', sea.calcTotal(4)

    print '-'*20
    wasWkDay = HotelRoomCalc(169, 0.045, 0.02)
    wasWkEnd = HotelRoomCalc(119, 0.045, 0.02)
    print '7 day rate:', wasWkDay.calcTotal(5) + wasWkEnd.calcTotal(1)


if __name__ == '__main__':
    main()
