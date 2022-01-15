##########################################
#
# fb3-5.mk
# 高级计算器-makefile
#
##########################################

fb3-5.exe: fb3-5.h fb3-5.funcs.c fb3-5.l fb3-5.y
	bison -d fb3-5.y
	flex -ofb3-5.flex.c fb3-5.l
	gcc -g -o $@ fb3-5.funcs.c fb3-5.tab.c fb3-5.flex.c
