all: parser.y scanner.l
	bison -v --report=all -d parser.y
	gcc -c parser.tab.c
	flex --header-file=lex.yy.h scanner.l
	gcc -c lex.yy.c
	gcc  -o etapa3 lex.yy.o parser.tab.o -lfl -lm  main.c helper.c

clean:
	rm -rf parser.lex.c parser.tab.c etapa2 parser.tab.h rm lex.yy.* parser.tab.* parser.output etapa2