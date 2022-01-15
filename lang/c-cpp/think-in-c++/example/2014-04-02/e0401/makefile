
CLibTest.exe : CLibTest.o CLib.o
	g++ -o CLibTest.exe CLibTest.o CLib.o

CLib.o : CLib.h CLib.cpp
	g++ -c -o CLib.o CLib.cpp

CLibTest.o : CLibTest.cpp CLib.h
	g++ -c -o CLibTest.o CLibTest.cpp

clean :
	rm CLib.o CLibTest.o CLibTest.exe
