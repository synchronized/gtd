
fb2-5.exe: fb2-5.l
	flex fb2-5.l
	gcc lex.yy.c -lfl -o $@
