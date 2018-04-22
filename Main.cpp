#include <iostream>
#include "CodeGenerator/AsmGenerator.h"
using namespace std;

// to hide the comments inside assembly code set this to 0
bool withComments = 0;

void genrateDummy(){ // This is just an example 
	// of how to use the helper class AsmGenerator
	AsmGenerator::comment("This is just a comment in asembly file");
	AsmGenerator::li("t1", 10);
	AsmGenerator::li("t2", 5);
	AsmGenerator::comment("Another comment");
	AsmGenerator::binary_operation("t3", "t1", "t2", 1);
	AsmGenerator::print_reg("t3");
}

int main()
{
	// This will initialize the assembly file
	AsmGenerator::initialize_file();
	// This will write on the assebmly file
	// This should be replaced with the function that will descent the AST
	genrateDummy();
	// Write the conent of the file to close it
	AsmGenerator::write_asm_file();

	cout << "\n\n=========================================Mars Output=========================================" << endl;
	// run the mars jar with the AssemblyCode.asm as input, the mars will execute the assembly file and return the result to current cmd
	system("java -jar CodeGenerator/Mars.jar CodeGenerator/AssemblyCode.asm");
	cout << "=============================================================================================\n\n" << endl;

	return 0;
}

