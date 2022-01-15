
#COMP = gcc
COMP = g++
main.exe : func.o main.o
	${COMP} -o main.exe func.o main.o

func.o : func.cpp
	${COMP} -c -o func.o func.cpp

main.o : main.cpp
	${COMP} -c -o main.o main.cpp

clean :
	rm main.o func.o main.exe
