###############################################
# 
# fb4-1.mk
# SQL分析器-Makefile
#
###############################################

CC = gcc -g
LEX = flex
YACC = bison
CFLAGS = -DYYDEBUG=1

PROGRAMSS = fb4-1.exe
all: ${PROGRAMSS}

# chapter 5

fb4-1.exe: fb4-1.tab.o fb4-1.flex.o
	${CC} -o $@ fb4-1.tab.o fb4-1.flex.o

fb4-1.tab.c fb4-1.tab.h: fb4-1.y
	${YACC} -vd fb4-1.y

fb4-1.flex.c: fb4-1.l
	${LEX} -o $@ $<

clean:
	rm -f fb4-1.tab.h fb4-1.tab.c fb4-1.tab.o
	rm -f fb4-1.flex.c fb4-1.flex.o
	rm -f fb4-1.exe

#fb4-1.tab.o: fb4-1.tab.h
#fb4-1.flex.o: fb4-1.tab.h
	
.SUFFIXES: .pgm .l .y .c

