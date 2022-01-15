-- 单行注释
--[[
多行注释
--]]

------------------
-- 1. 变量 & 控制流
------------------

num = 23 -- 数字都是双精度
str = 'this is a string' -- 像python 一样不可变
str = "this is a another string" -- 可以双引号
str = [[
像 python的多行注释可以用于表示多行字符串一样
]]

bol = nil -- 为定义,支持垃圾回收

-- 缩进职位易读性，像Matlab 一样以end结尾
while num < 50 do
   num = num +1 -- 没有++ 或+=子曾操作符号
end

-- IF 条件开关
if num > 40  then
   print('> 40')
elseif s ~= 'aspython' then -- ~= 表示 ！=
   io.write('s is not aspython') -- 风骚的标准输出
else
   thisIsGlobal = 5 -- 驼峰式命名
   -- 显示声明局部变量（像 js 一样）
   local line = io。read()

   -- .. 作为字符串链接字符
   print("凛冬将至" .. line)
end

-- 引用为定义变量返回nil，这不是错误
foo = anUnknowVariable -- 等价于 foo = nil
aBoolValue = false
-- 只有nil 与false 为逻辑假; 数字0与空字符串''为真!
if not aBoolValue  then
   print('false')
end

-- 想python 一样运用 'or' 和 'and'
-- 得到c语言中a ？ b ： c 的效果; 需注意 b = false 或者 nil的情况
ans = aBoolValue and 'yes' or 'no'

karlSum = 0
for i=l,100  do -- 像matlab 一样的递增语法，包括两端，如同数学中[1,100]
   karlSum = karlSum + i
end

-- Step 为 2 递减的方式 '100, 1, -2'
for i=1, 100, -2 do
   print(j)
end
-- 续上，范围可表示为"begin, end [, step]"

num = 23
repeat
   print('凡人必有一死')
until num == 0

--------------------
-- 2 函数
--------------------
function fib(n)
   if n < 2 then
      return 1
   end
   return fib(n -2) + fib(n -1)
end

-- js 一样的匿名函数与闭包
function adder(x)
   -- 返回一个函数
   -- 闭包内封存x值
   return function(y) return x + y end
end

a1 = adder(9)
a2 = adder(36)
print(a1(16)) --> 25
print(a2(64)) --> 00

x, y, z = 1, 2, 3, 4 --4 被忽略
