all: parser

parser.cpp parser.hpp:  parser.y
	bison -d parser.y -o parser.cpp

lex.cpp: lexico.l parser.hpp
	flex -o lex.cpp lexico.l

parser: lex.cpp parser.cpp parser.hpp main.cpp tree.cpp semantic.cpp
	g++ -std=c++11 -o parser *.hpp *.cpp

clean:
	rm parser parser.cpp lex.cpp parser.hpp
