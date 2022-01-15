
main.exe : Video.o main.o
	g++ -o main.exe Video.o main.o

Video.o : Video.h Video.cpp
	g++ -c -o Video.o Video.cpp

main.o : Video.h main.cpp
	g++ -c -o main.o main.cpp

clean : 
	rm Video.o main.o main.exe
