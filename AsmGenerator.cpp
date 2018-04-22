#include "CodeGenerator/AsmGenerator.h"
#include <string> 

void AsmGenerator::initialize_file()
{
	assembly_code_file.open("AssemblyCode.asm");
	main_stream << ".text\n"
		<< ".globl main\n"
		<< "main:\n\n";
}

void AsmGenerator::write_asm_file()
{
	AsmGenerator::system_call(10);
	AsmGenerator::add_instruction("\n\n\n\n");
	assembly_code_file << main_stream.str();
	assembly_code_file.close();
}

void AsmGenerator::li(string reg, int value)
{
	string c = "li $";
	c += reg;
	c += ",";
	c += to_string(value);
	AsmGenerator::add_instruction(c);
}

void AsmGenerator::binary_operation(string dest_reg, string reg1, string reg2, int operation)
{
	//operation values:
	// 1 +
	// 2 -
	// 3 *
	// 4 /
	// 5 %
	// 6 &&
	// 7 ||
	string c = "";

	switch (operation)
	{
	case 1:
		c += "add $";
		break;
	case 2:
		c += "sub $";
		break;
	case 3:
		c += "mul $";
		break;
	case 4:
		c += "div $";
		break;
	case 5:
		c += "rem $";
		break;
	case 6:
		c += "and $";
		break;
	case 7:
		c += "or $";
		break;
	default:
		break;
	}

	c += dest_reg;
	c += ", $";

	c += reg1;
	c += ", $";

	c += reg2;
	AsmGenerator::add_instruction(c);
}

void AsmGenerator::add_label (string label_name)
{
	AsmGenerator::add_instruction(label_name+":");
}

void AsmGenerator::push(string source_register)
{

	AsmGenerator::add_instruction("\tsub $sp,$sp,4");
	string c="sw $";
	c+=source_register;
	c+=", 0($sp)";
	AsmGenerator::add_instruction("\t"+c);
}

void AsmGenerator::pop(string destination_register)
{
	string c = "lw $";
	c += destination_register;
	c += ", 0($sp)";
	AsmGenerator::add_instruction("\t"+c);
	AsmGenerator::add_instruction("\tadd $sp,$sp,4");
}

void AsmGenerator::add_instruction(string instruction)
{
	instruction += "\n";
	main_stream << instruction;	
}

void AsmGenerator::comment(string comment_message)
{
	if (!withComments)
		return;
	stringstream cmt(comment_message);
	string line;
	while (getline(cmt, line))
	{
		string c = "#-----------";
		c+= line;
		AsmGenerator::add_instruction(c);
	}
}

void AsmGenerator::system_call(int system_call_code)
{
	AsmGenerator::li("v0",system_call_code);
	main_stream << "syscall\n";
}

void AsmGenerator::print_string(string reg_string_address)
{
	AsmGenerator::move("a0",reg_string_address);
	AsmGenerator::system_call(4);
}

void AsmGenerator::print_int(int printed_int)
{
	AsmGenerator::li("a0",printed_int);
	AsmGenerator::system_call(1);
}

void AsmGenerator::print_reg(string reg)
{
	AsmGenerator::move("a0",reg);
	AsmGenerator::system_call(1);
}

void AsmGenerator::f_print_reg(string reg)
{
	AsmGenerator::f_move("f12",reg);
	AsmGenerator::system_call(2);
}

void AsmGenerator::move(string dest_reg,string source_reg)
{
	string c = "move $";
	c+=dest_reg;
	c+=",$";
	c+=source_reg;
	AsmGenerator::add_instruction(c);
}

void AsmGenerator::f_move(string dest_reg,string source_reg)
{
	string c = "mov.s $";
	c+=dest_reg;
	c+=",$";
	c+=source_reg;
	AsmGenerator::add_instruction(c);
}

ofstream AsmGenerator::assembly_code_file;
stringstream AsmGenerator::main_stream;