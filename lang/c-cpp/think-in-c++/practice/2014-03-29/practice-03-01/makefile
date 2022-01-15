# from Think in C++ 2nd Edition practice

compile = g++
main.exe : main.o func.o
	${compile} -o main.exe \
		main.o \
		func.o

func.o : func.h func.cpp
	${compile} -c -o func.o \
		func.cpp

main.o : main.cpp
	${compile} -c -o main.o \
		main.cpp

clean: 
	rm \
		main.o \
		func.o \
		main.exe
