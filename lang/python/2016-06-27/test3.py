#-*- coding:utf-8 -*-

import json

class stu(object):
    def __init__(self,name,age):
        self.name = name
        self.age = age

    @staticmethod
    def todic(std):
        return {'name':std.name, 'age':std.age}
    @staticmethod
    def dic2stu(d):
        return stu(d["name"], d["age"])

json_str = '{"age":20, "name": "Bob"}'
print(json.loads(json_str,object_hook=stu.dic2stu))
