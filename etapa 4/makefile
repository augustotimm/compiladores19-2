all: parser.y scanner.l
	bison -v --report=all -d parser.y 
	gcc -c parser.tab.c helper.c -lcunit
	flex --header-file=lex.yy.h scanner.l
	gcc -c lex.yy.c -lcunit
	gcc  -o etapa4 lex.yy.o parser.tab.o  -lm  main.c semanticsHelper.c helper.c helper.h -g  -lfl -O0 -lcunit

run:
	./etapa4 < teste.txt

clean:
	rm -rf parser.lex.c parser.tab.c etapa4 parser.tab.h rm lex.yy.* parser.tab.* parser.output etapa3 *.csv *.o