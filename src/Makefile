all: parser

parser.tab.c parser.tab.h:	parser.y 
	bison -d parser.y

lex.yy.c: lexico.l parser.tab.h
	flex lexico.l

parser: lex.yy.c parser.tab.c parser.tab.h
	g++ -o parser parser.tab.c lex.yy.c

clean:
	rm parser parser.tab.c lex.yy.c parser.tab.h
