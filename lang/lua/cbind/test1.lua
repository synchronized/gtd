local mylib = require "mylib"


function l_ff(a, b)
   local c = mylib.c_add(a, b) + 1
   print ("in lua1: ", c)
   local d = mylib.c_step(c)
   print ("in lua2: ", d)
   return d
end

l_ff();
