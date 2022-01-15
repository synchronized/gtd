all:test1.exe

test1.exe:mylib.so test1.c
	gcc -g -Wall -o test1.exe test1.c -lm -ldl liblua.a

mylib.so: test1-lib.c
	gcc -g -Wall -o mylib.so -fPIC -shared test1-lib.c

clean:
	rm test1.exe mylib.so
