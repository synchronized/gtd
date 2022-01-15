
CppLibTest.exe : CppLibTest.o CppLib.o
	g++ -o CppLibTest.exe CppLibTest.o CppLib.o

CppLib.o : CppLib.h CppLib.cpp
	g++ -c -o CppLib.o CppLib.cpp

CppLibTest.o : CppLibTest.cpp CppLib.h
	g++ -c -o CppLibTest.o CppLibTest.cpp

clean :
	rm CppLibTest.exe CppLibTest.o CppLib.o
