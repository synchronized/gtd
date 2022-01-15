#// : practice-05-09/makefile

main.exe : main.o Stash.o Mem.o
	g++ -o main.exe main.o Stash.o Mem.o

main.o : main.cpp Stash.h
	g++ -c -o main.o main.cpp

Stash.o : Stash.h Stash2.cpp Mem.h
	g++ -c -o Stash.o Stash2.cpp

Mem.o : Mem.h Mem.cpp
	g++ -c -o Mem.o Mem.cpp

clean :
	rm main.o Stash.o Mem.o main.exe
