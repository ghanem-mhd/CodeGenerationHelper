#pragma once
#ifndef GODEGENERATOR_H
#define GODEGENERATOR_H
#include <iostream>
#include <cstring>

#include <fstream>
#include <sstream>

extern bool withComments;

using namespace std;

class AsmGenerator{
public:
	static ofstream assembly_code_file;

	static stringstream main_stream;

	static void initialize_file(); 

	static void write_asm_file();

	static void li							(string reg,int value);

	static void binary_operation(string dest_reg, string reg1, string reg2, int operation);

	static void add_label					(string label_name);

	static void push						(string source_register);

	static void pop							(string destination_register);

	static void add_instruction				(string instruction);
	
	static void comment						(string comment_meesage);

	// System Calls
	static void system_call					(int systam_call_code);

	static void print_string				(string reg_string_address);

	static void print_int					(int printed_int);

	static void print_reg					(string reg);

	static void f_print_reg					(string reg);

	static void move						(string dest_reg ,string source_reg);
	static void f_move						(string dest_reg ,string source_reg);
};

#endif