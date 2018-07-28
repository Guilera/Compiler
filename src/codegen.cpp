#include "tree.hpp"
#include "parser.hpp"
#include <string>

using namespace tree;
using namespace std;

string ACC = "$a0"; // Accumulator
string TEMP = "$t0"; // Temporary
string SP = "$sp"; // Stack Pointer
string FP = "$fp"; // Frame Pointer
string RA = "$ra"; // Return Address

void Push(string reg, ostream &os) {
  os << "sw " << reg << ", 0($sp)" << endl; // put the value of reg in top of the stack
  os << "addiu $sp, $sp, -4" << endl;		// deslocate stack pointer to the next empty slot
}

void Pop(ostream &os) {
  os << "lw $ac";
}

void Pop(string, ostream &os);


