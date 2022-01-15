#!/usr/bin/env python
# coding: utf-8

import redis

redis = redis.Redis(host='127.0.0.1', port=6379)
redis.set('foo', 'bar')
print redis.get('foo')
