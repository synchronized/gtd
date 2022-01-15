#// : practice-05-09/makefile

main.exe : main.o Stash.o
	g++ -o main.exe main.o Stash.o

main.o : main.cpp Stash.h
	g++ -c -o main.o main.cpp

Stash.o : Stash.h Stash.cpp
	g++ -c -o Stash.o Stash.cpp

clean :
	rm main.o Stash.o main.exe
