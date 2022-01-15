#!/usr/bin/env python

# def map(func, seq):
#     mapped_seq = []
#     for eachItem in seq:
#         mapped_seq.append(func(eachItem))
#     return mapped_seq

print map((lambda x: x+2), [0, 1, 2, 3, 4, 5])
