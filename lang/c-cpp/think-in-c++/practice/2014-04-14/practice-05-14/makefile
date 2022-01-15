#//:practice-05-14/makefile

main.exe : main.o StackOfInt.o
	g++ -o main.exe main.o StackOfInt.o

#main.exe : main.o StackImpOfVector.o
#	g++ -o main.exe main.o StackImpOfVector.o

main.o : main.cpp StackOfInt.h
	g++ -c -o main.o main.cpp

StackOfInt.o : StackOfInt.h StackImpOfArray.cpp
	g++ -c -o StackOfInt.o StackImpOfArray.cpp

StackImpOfVector.o : StackOfInt.h StackImpOfVector.cpp
	g++ -c -o StackImpOfVector.o StackImpOfVector.cpp

clean :
	rm main.o StackImpOfArray.o main.exe
