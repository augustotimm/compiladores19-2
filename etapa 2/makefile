all: parser.y scanner.l
	bison -d parser.y
	flex  -o parser.lex.c scanner.l
	gcc  -o etapa2 parser.lex.c parser.tab.c -lfl -lm 

clean:
	rm -rf parser.lex.c parser.tab.c etapa2 parser.tab.h