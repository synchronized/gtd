#########################################
# fb3-1.mk
#########################################

fb3-1.exe: fb3-1.h fb3-1.funcs.c fb3-1.l fb3-1.y
	bison -d fb3-1.y
	flex -ofb3-1.lex.c fb3-1.l
	gcc -o $@ -g fb3-1.funcs.c fb3-1.lex.c fb3-1.tab.c
