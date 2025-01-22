#include "compiler.h"
#include "helpers/vector.h"
#include <stdarg.h>
#include <stdio.h>
static struct compile_process* current_process = NULL;

void codegen_new_scope(int flags) {
	#warning "the resolver needs to exist for this to work"
}

void codegen_finish_scope() {
	#warning "the resolver needs to exist for this to work"
}

struct node* codegen_node_next() {
	return vector_peek_ptr(current_process->node_tree_vec);
}

void asm_push_args(const char* ins, va_list args) {
	va_list args2;
	va_copy(args2, args);
	vfprintf(stdout, ins, args);
	fprintf(stdout, "\n");
	if(current_process->ofile) {
		vfprintf(current_process->ofile, ins, args2);
		fprintf(current_process->ofile, "\n");
	}
}

void asm_push(const char* ins, ...) {
	va_list(args);
	va_start(args, ins);
	asm_push_args(ins, args);
	va_end(args);
}

void codegen_generate_data_section_part(struct node* node) {
	// create a switch for processing global data
	
}

void codegen_generate_data_section() {
	asm_push("section .data");
	struct node* node = codegen_node_next();
	while(node) {
		codegen_generate_data_section_part(node);
		node = codegen_node_next();
	}
}	

void codegen_generate_root() {
}

void codegen_generate_rod() {
}

int codegen(struct compile_process* process) {
	current_process = process;
	scope_create_root(process);
	vector_set_peek_pointer(process->node_tree_vec, 0);
	codegen_new_scope(0);

	codegen_generate_data_section();
	vector_set_peek_pointer(process->node_tree_vec, 0);
	codegen_generate_root();
	codegen_finish_scope();

	// Generate read-only data
	codegen_generate_rod();
	return 0;
}