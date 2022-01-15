
main.exe : main.o printBinary.h printBinary.o
	g++ -o main.exe main.o printBinary.o

printBinary.o : printBinary.h printBinary.cpp
	g++ -c -o printBinary.o printBinary.cpp

main.o : main.cpp
	g++ -c -o main.o main.cpp

clean :
	rm *.o *.exe
