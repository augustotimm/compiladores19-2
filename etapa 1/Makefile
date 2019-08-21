
LIB = -lfl


all: lex.yy.o
	gcc -Wall main.c lex.yy.o $(LIB) -o etapa1

lex.yy.o:
	flex --header-file=lex.yy.h scanner.l
	gcc -c lex.yy.c

clean:
	rm lex.yy.* etapa1
