
fb2-4.exe: fb2-4.l
	flex fb2-4.l
	gcc lex.yy.c -lfl -o $@
