all: parser

parser.cpp parser.hpp:  parser.y
	bison -d parser.y -o parser.cpp

lex.cpp: lexico.l parser.hpp
	flex -o lex.cpp lexico.l

parser: lex.cpp parser.cpp parser.hpp main.cpp tree.cpp codegen.cpp
	g++ -std=c++11 -o parser *.hpp main.cpp parser.cpp lex.cpp tree.cpp codegen.cpp

clean:
	rm parser parser.cpp lex.cpp parser.hpp
