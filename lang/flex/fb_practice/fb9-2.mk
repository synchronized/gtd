CFLAGS = -g
CC = gcc

all: fb9-2.exe

fb9-2.exe: fb9-2.flex.o fb9-2.tab.o
	${CC} ${CFLAGS} -o $@ fb9-2.flex.c

fb9-2.flex.c: fb9-2.l
	flex -o$@ fb9-2.l

fb9-2.tab.c fb9-2.tab.h:fb9-2.y
	bison -vd fb9-2.y

fb9-2.flex.o: fb9-2.flex.c fb9-2.tab.h fb9-2.funcs.h
	${CC} -c ${CFLAGS} -o $@ fb9-2.flex.c

fb9-2.tab.o: fb9-2.tab.c fb9-2.funcs.h
	${CC} -c ${CFLAGS} -o $@ fb9-2.tab.c
