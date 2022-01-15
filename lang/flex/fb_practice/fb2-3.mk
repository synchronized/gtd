fb2-3.exe: fb2-3.l
	flex fb2-3.l
	gcc lex.yy.c -lfl -o $@
