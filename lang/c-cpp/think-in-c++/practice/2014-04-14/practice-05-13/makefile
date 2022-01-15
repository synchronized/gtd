# // : practice-05-13/makefile

main.exe : main.o Handle.o
	g++ -o main.exe main.o Handle.o

main.o : main.cpp Handle.h
	g++ -c -o main.o main.cpp

Handle.o : Handle.h Handle.cpp
	g++ -c -o Handle.o Handle.cpp

cleanup :
	rm main.o Handle.o main.exe
