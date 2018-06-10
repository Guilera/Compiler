#include <iostream>
#include <fstream>
#include <sstream>
#include "tree.hpp"

extern tree::Program program;
extern int yyparse();
extern FILE * yyin;

int main(const int argc, const char **argv) {
  if(argc > 1) {
	std::ifstream input(argv[1], std::ios::in);
	if (input.is_open())
	  yyin = fopen(argv[1], "r");
	else
	  std::cout << "Impossible to open file" << argv[1] << std::endl;
  }

  if(argc > 2) {
	std::ofstream output(argv[2], std::ios::out);
	if (output.is_open()) {
	  yyparse();
	  program.print(output);
	} else {
	  std::cout << "Impossible to open file" << argv[2] << std::endl;
	}
  } else {
    yyparse();
	program.print(std::cout);
  }
}