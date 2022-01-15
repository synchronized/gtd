#: practice-05-11/makefile

main.exe : main.o Stack.o
	g++ -o main.exe main.o Stack.o

main.o : main.cpp Stack.h
	g++ -c -o main.o main.cpp

Stack.o : Stack.h Stack.cpp
	g++ -c -o Stack.o Stack.cpp

clean :
	rm main.o Stack.o main.exe
