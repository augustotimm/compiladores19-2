all: parser.y scanner.l
	bison -v --report=all -d parser.y 
	gcc -c parser.tab.c helper.c -lcunit
	flex --header-file=lex.yy.h scanner.l
	gcc -c lex.yy.c -lcunit
	gcc  -o etapa5 lex.yy.o parser.tab.o  -lm  main.c semanticsHelper.c helper.c helper.h ilochelper.c -g  -lfl -O0 -lcunit

run:
	./etapa5 < teste.txt >saida.iloc

clean:
	rm -rf parser.lex.c parser.tab.c etapa5 parser.tab.h rm lex.yy.* parser.tab.* parser.output etapa3 *.csv *.o *.iloc