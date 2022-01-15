
main.exe : main.o Video.o Stack.o
	g++ -o main.exe main.o Video.o Stack.o

main.o : Video.h Stack.h main.cpp
	g++ -c -o main.o main.cpp

Video.o : Video.h Video.cpp
	g++ -c -o Video.o Video.cpp

Stack.o : Stack.h Stack.cpp
	g++ -c -o Stack.o Stack.cpp

clean :
	rm Stack.o Video.o main.o main.exe
