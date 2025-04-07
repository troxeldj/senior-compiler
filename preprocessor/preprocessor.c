#include "compiler.h"
#include "helpers/vector.h"
#include "helpers/buffer.h"

enum {
	TYPEDEF_TYPE_STANDARD,
	TYPEDEF_TYPE_STRUCTURE_TYPEDEF,

};

struct typedef_type {
	int type;
	const char* defintion_name;
	struct vector* value;
	struct typedef_structure {
		const char* sname;
	} structure;
};

enum {
	PREPROCESSOR_FLAG_EVALUATE = 0b00000001
};

enum {
	PREPROCESSOR_NUMBER_NODE,
	PREPROCESSOR_IDENTIFIER_NODE,
	PREPROCESSOR_KEYWORD_NODE,
	PREPROCESSOR_UNARY_NODE,
	PREPROCESSOR_EXPRESSION_NODE,
	PREPROCESSOR_PARENTHESES_NODE,
	PREPROCESSOR_JOINED_NODE,
	PREPROCESSOR_TERNARY_NODE
};

struct preprocessor_node {
	int type;
	struct preprocessor_const_val {
		union {
			char cval;
			unsigned int inum;
			long lnum;
			long long llnum;
			unsigned long ulnum;
			unsigned long long ullnum;
		};
	} const_val;

		union {
			struct preprocessor_exp_node {
				struct preprocessor_node* left;
				struct preprocessor_node* right;
				const char* op;
			} exp;

			struct preprocessor_unary_node {
				struct preprocessor_node* operand_node;
				const char* op;
				struct preprocessor_unary_indirection {
					int depth;
				} indirection;
			} unary_node;

			struct preprocessor_parentheses {
				struct preprocessor_node* exp;
			} parentheses;

			struct preprocessor_joined_node {
				struct preprocessor_node* left;
				struct preprocessor_node* right;
				const char* op;
			} joined;

			struct preprocessor_ternary_node {
				struct preprocessor_node* true_node;
				struct preprocessor_node* false_node;
			} ternary;
		};
		const char* sval;
};

void preprocessor_execute_warning(struct compile_process* compiler, const char* msg) {
	compiler_error(compiler, "Preprocessor Warning: %s\n", msg);
}

void preprocessor_execute_error(struct compile_process* compiler, const char* msg) {
	compiler_error(compiler, "Preprocessor Error: %s\n", msg);
}

struct preprocessor_included_file* preprocessor_add_included_file(struct preprocessor* preprocessor, const char* filename) {
	struct preprocessor_included_file* included_file = calloc(1, sizeof(struct preprocessor_included_file));
	strncpy(included_file->filename, filename, sizeof(included_file->filename));
	vector_push(preprocessor->includes, &included_file);
	return included_file;
}

void preprocessor_create_static_includes(struct preprocessor* preprocessor, const char* filename, PREPROCESSOR_STATIC_INCLUDE_HANDLER_POST_CREATION creation_handler) {
	struct preprocessor_included_file* included_file = preprocessor_add_included_file(preprocessor, filename);
	creation_handler(preprocessor, included_file);
}

bool preprocessor_is_keyword(const char* type) {
	return S_EQ(type, "defined");
}

struct vector* preprocessor_build_value_vector_for_integer(int value) {
	struct vector* token_vec = vector_create(sizeof(struct token));
	struct token t1 = {};
	t1.type = TOKEN_TYPE_NUMBER;
	t1.llnum = value;
	vector_push(token_vec, &t1);
	return token_vec;
}

void preprocessor_token_vec_push_keyword_and_identifier(struct vector* token_vec, const char* keyword, const char* identifier) {
	struct token t1 = {};
	t1.type = TOKEN_TYPE_KEYWORD;
	t1.sval = keyword;

	struct token t2 = {};
	t2.type = TOKEN_TYPE_IDENTIFIER;
	t2.sval = identifier;

	vector_push(token_vec, &t1);
	vector_push(token_vec, &t2);
}

void* preprocessor_node_create(struct preprocessor_node* node) {
	struct preprocessor_node* result = calloc(1, sizeof(struct preprocessor_node));
	memcpy(result, node, sizeof(struct preprocessor_node));
	return result;
}

int preprocessor_definition_argument_exists(struct preprocessor_definition* definition, const char* name) {
	vector_set_peek_pointer(definition->standard.arguments, 0);
	int i = 0;
	const char* current = vector_peek(definition->standard.arguments);
	while(current) {
		if(S_EQ(current, name)) {
			return i;
		}
		i++;
		current = vector_peek(definition->standard.arguments);
	}
	return -1;
}

struct preprocessor_function_argument* preprocessor_function_argument_at(struct preprocessor_function_arguments* arguments, int index) {
	struct preprocessor_function_argument* argument = vector_at(arguments->arguments, index);
	return argument;
}

void preprocessor_token_push_to_function_arguments(struct preprocessor_function_arguments* arguments, struct token* token) {
	struct preprocessor_function_argument argument = {};
	argument.tokens = vector_create(sizeof(struct token));
	vector_push(argument.tokens, token);
	vector_push(arguments->arguments, &argument);
}

void preprocessor_function_argument_push_to_vector(struct preprocessor_function_argument* argument, struct vector* vector_out) {
	vector_set_peek_pointer(argument->tokens, 0);
	struct token* token = vector_peek(argument->tokens);
	while(token) {
		vector_push(vector_out, token);
		token = vector_peek(argument->tokens);
	}
}

void preprocessor_token_push_to_dst(struct vector* token_vec, struct token* token) {
	struct token t = *token;
	vector_push(token_vec, &t);
}

void preprocessor_token_push_dst(struct compile_process* compiler, struct token* token) {
	preprocessor_token_push_to_dst(compiler->token_vec, token);
}

void preprocessor_token_vec_push_src_to_dst(struct compile_process* compiler, struct vector* src_vec, struct vector* dst_vec) {
	vector_set_peek_pointer(src_vec, 0);
	struct token* token = vector_peek(src_vec);
	while(token) {
		vector_push(dst_vec, token);
		token = vector_peek(src_vec);
	}
}	

void preprocessor_token_vec_push_src(struct compile_process* compiler, struct vector* src_vec) {
	preprocessor_token_vec_push_src_to_dst(compiler, src_vec, compiler->token_vec);
}

void preprocessor_token_vec_push_src_token(struct compile_process* compiler, struct token* token) {
	vector_push(compiler->token_vec, token);
}

void preprocessor_initialize(struct preprocessor* preprocessor) {
	memset(preprocessor, 0, sizeof(struct preprocessor));
	preprocessor->definitions = vector_create(sizeof(struct preprocessor_definition*));
	preprocessor->includes = vector_create(sizeof(struct preprocessor_included_file*));
	#warning "create preprocessor default definitions"

}

struct preprocessor* preprocessor_create(struct compile_process* compiler) {
	struct preprocessor* preprocessor = calloc(1, sizeof(struct preprocessor));
	preprocessor_initialize(preprocessor);
	preprocessor->compiler = compiler;
	return preprocessor;
}

struct token* preprocessor_next_token(struct compile_process* compiler) {
	return vector_peek(compiler->token_vec_original);
}

struct token* preprocessor_previous_token(struct compile_process* compiler) {
	return vector_peek_at(compiler->token_vec_original, compiler->token_vec_original->pindex -1);
}

struct token* preprocessor_next_token_no_increment(struct compile_process* compiler) {
	return vector_peek_no_increment(compiler->token_vec_original);
}

struct token* preprocessor_peek_next_token_skip_nl(struct compile_process* compiler) {
	struct token* token = preprocessor_next_token_no_increment(compiler);
	while(token && token->type == TOKEN_TYPE_NEWLINE) {
		token = preprocessor_next_token(compiler);
	}
	token = preprocessor_next_token_no_increment(compiler);
	return token;
}

void* preprocessor_handle_number_token(struct expressionable* expressionable) {
	struct token* token = expressionable_token_next(expressionable);
	return preprocessor_node_create(&(struct preprocessor_node){.type = PREPROCESSOR_NUMBER_NODE, .const_val.llnum = token->llnum});
}

void* preprocessor_handle_identifier_token(struct expressionable* expressionable) {
	struct token* token = expressionable_token_next(expressionable);
	bool is_preprocessor_keyword = preprocessor_is_keyword(token->sval);
	int type = PREPROCESSOR_IDENTIFIER_NODE;
	if(is_preprocessor_keyword) {
		type = PREPROCESSOR_KEYWORD_NODE;
	}
	return preprocessor_node_create(&(struct preprocessor_node){.type = type, .sval = token->sval});
}

void preprocessor_make_unary_node(struct expressionable* expressionable, const char* op, void* right_operand_node_ptr) {
	struct preprocessor_node* right_operand_node = right_operand_node_ptr;
	void* unary_node = preprocessor_node_create(&(struct preprocessor_node){.type = PREPROCESSOR_UNARY_NODE, .unary_node.operand_node = right_operand_node, .unary_node.op = op});
	expressionable_node_push(expressionable, unary_node);
}

void preprocessor_make_expression_node(struct expressionable* expressionable, void* left_node_ptr, void* right_node_ptr, const char* op) {
	struct preprocessor_node exp_node;
	exp_node.type = PREPROCESSOR_EXPRESSION_NODE;
	exp_node.exp.left = left_node_ptr;
	exp_node.exp.right = right_node_ptr;
	exp_node.exp.op = op;
	expressionable_node_push(expressionable, preprocessor_node_create(&exp_node));
}

void preprocessor_make_parentheses_node(struct expressionable* expressionable, void* node_ptr) {
	struct preprocessor_node* node = node_ptr;
	struct preprocessor_node parentheses_node;
	parentheses_node.type = PREPROCESSOR_PARENTHESES_NODE;
	parentheses_node.parentheses.exp = node_ptr;
	expressionable_node_push(expressionable, preprocessor_node_create(&parentheses_node));
}

void preprocessor_make_ternary_node(struct expressionable* expressionable, void* true_result_node_ptr, void* false_result_node_ptr) {
	struct preprocessor_node* true_result_node = true_result_node_ptr;
	struct preprocessor_node* false_result_node = false_result_node_ptr;
	expressionable_node_push(expressionable, preprocessor_node_create(&(struct preprocessor_node){.type = PREPROCESSOR_TERNARY_NODE, .ternary.true_node = true_result_node, .ternary.false_node = false_result_node}));
}

int preprocessor_get_node_type(struct expressionable* expressionable, void* node) {
	int generic_type = EXPRESSIONABLE_GENERIC_TYPE_NON_GENERIC;
	struct preprocessor_node* preprocessor_node = node;
	switch(preprocessor_node->type) {
		case PREPROCESSOR_NUMBER_NODE:
			generic_type = EXPRESSIONABLE_GENERIC_TYPE_NUMBER;
			break;
		case PREPROCESSOR_IDENTIFIER_NODE:
		case PREPROCESSOR_KEYWORD_NODE:
			generic_type = EXPRESSIONABLE_GENERIC_TYPE_IDENTIFIER;
			break;
		case PREPROCESSOR_UNARY_NODE:
			generic_type = EXPRESSIONABLE_GENERIC_TYPE_UNARY;
			break;
		case PREPROCESSOR_EXPRESSION_NODE:
			generic_type = EXPRESSIONABLE_GENERIC_TYPE_EXPRESSION;
			break;
		case PREPROCESSOR_PARENTHESES_NODE:
			generic_type = EXPRESSIONABLE_GENERIC_TYPE_PARENTHESES;
			break;
	}
	return generic_type;
}

void* preprocessor_get_left_node(struct expressionable* expressionable, void* target_node) {
	struct preprocessor_node* node = target_node;
	return node->exp.left;
}

void* preprocessor_get_right_node(struct expressionable* expressionable, void* target_node) {
	struct preprocessor_node* node = target_node;
	return node->exp.right;
}

const char* preprocessor_get_node_operator(struct expressionable* expressionable, void* target_node) {
	struct preprocessor_node* node = target_node;
	return node->exp.op;
}

void** preprocessor_get_left_node_address(struct expressionable* expressionable, void* target_node) {
	return (void**)&((struct preprocessor_node*)(target_node))->exp.left;
}

void** preprocessor_get_right_node_address(struct expressionable* expressionable, void* target_node) {
	return (void**)&((struct preprocessor_node*)(target_node))->exp.right;
}

void preprocessor_set_expression_node(struct expressionable* expressionable, void* node, void* left_node, void* right_node, const char* op) {
	struct preprocessor_node* preprocessor_node = node;
	preprocessor_node->exp.left = left_node;
	preprocessor_node->exp.right = right_node;
	preprocessor_node->exp.op = op;
}

bool preprocessor_should_join_nodes(struct expressionable* expressionable, void* previous_node_ptr, void* node_ptr) {
	return true;
}

void* preprocessor_join_nodes(struct expressionable* expressionable, void* previous_node_ptr, void* node_ptr) {
	struct preprocessor_node* previous_node = previous_node_ptr;
	struct preprocessor_node* node = node_ptr;
	return preprocessor_node_create(&(struct preprocessor_node){.type = PREPROCESSOR_JOINED_NODE, .joined.left = previous_node, .joined.right = node, .joined.op = node->exp.op});
}

bool preprocessor_expecting_additional_node(struct expressionable* expressionable, void* node_ptr) {
	struct preprocessor_node* node = node_ptr;
	return node->type == PREPROCESSOR_KEYWORD_NODE && S_EQ(node->sval, "defined");
}

bool preprocessor_is_custom_operator(struct expressionable* expressionable, struct token* token) {
	return false;
}

struct expressionable_config preprocessor_expressionable_config = {
	.callbacks.handle_number_callback = preprocessor_handle_number_token,
	.callbacks.handle_identifier_callback = preprocessor_handle_identifier_token,
	.callbacks.make_unary_node = preprocessor_make_unary_node,
	.callbacks.make_expression_node = preprocessor_make_expression_node,
	.callbacks.make_parentheses_node = preprocessor_make_parentheses_node,
	.callbacks.make_ternary_node = preprocessor_make_ternary_node,
	.callbacks.get_node_type = preprocessor_get_node_type,
	.callbacks.get_left_node = preprocessor_get_left_node,
	.callbacks.get_right_node = preprocessor_get_right_node,
	.callbacks.get_node_operator = preprocessor_get_node_operator,
	.callbacks.get_left_node_address = preprocessor_get_left_node_address,
	.callbacks.get_right_node_address = preprocessor_get_right_node_address,
	.callbacks.set_exp_node = preprocessor_set_expression_node,
	.callbacks.should_join_nodes = preprocessor_should_join_nodes,
	.callbacks.join_nodes = preprocessor_join_nodes,
	.callbacks.expecting_additional_node = preprocessor_expecting_additional_node,
	.callbacks.is_custom_operator = preprocessor_is_custom_operator
};

bool preprocessor_is_preprocessor_keyword(const char* value) {
	return S_EQ(value, "define") ||
		S_EQ(value, "undef") ||
		S_EQ(value, "warning") ||
		S_EQ(value, "if") ||
		S_EQ(value, "elseif") ||
		S_EQ(value, "ifdef") ||
		S_EQ(value, "ifndef") ||
		S_EQ(value, "endif") ||
		S_EQ(value, "include") ||
		S_EQ(value, "typedef");

}

bool preprocessor_token_is_preprocessor_keyword(struct token* token) {
	return token-> type == TOKEN_TYPE_IDENTIFIER || token->type == TOKEN_TYPE_KEYWORD && preprocessor_is_preprocessor_keyword(token->sval);
}

bool preprocessor_token_is_define(struct token* token) {
	if(!preprocessor_token_is_preprocessor_keyword(token)) {
		return false;
	}

	return (S_EQ(token->sval, "define"));
}

void preprocessor_multi_value_insert_to_vector(struct compile_process* compiler, struct vector* value_token_vec) {
	struct token* value_token = preprocessor_next_token(compiler);
	while(value_token) {
		if(value_token->type == TOKEN_TYPE_NEWLINE) {
			break;
		}

		if(token_is_symbol(value_token, '\\')) {
			// allows for another line
			preprocessor_next_token(compiler);
			value_token = preprocessor_next_token(compiler);
			continue;
		}
		vector_push(value_token_vec, value_token);
		value_token = preprocessor_next_token(compiler);
	}
}

void preprocessor_definition_remove(struct preprocessor* preprocessor, const char* name) {
	vector_set_peek_pointer(preprocessor->definitions, 0);
	struct preprocessor_definition* current_def = vector_peek_ptr(preprocessor->definitions);
	while(current_def) {
		if(S_EQ(current_def->name, name)) {
			vector_pop_last_peek(preprocessor->definitions);
		}
		current_def = vector_peek_ptr(preprocessor->definitions);
	}
}

struct preprocessor_definition* preprocessor_definition_create(const char* name, struct vector* value_vec, struct vector* arguments, struct preprocessor* preprocessor) {
	// unset the definition if it exists
	preprocessor_definition_remove(preprocessor, name);

	struct preprocessor_definition* definition = calloc(1, sizeof(struct preprocessor_definition));
	definition->type = PREPROCESSOR_DEFINITITION_STANDARD;
	definition->name = name;
	definition->standard.value = value_vec;
	definition->standard.arguments = arguments;
	definition->preprocessor = preprocessor;
	
	if(arguments && vector_count(definition->standard.arguments) > 0) {
		definition->type = PREPROCESSOR_DEFINITITION_MACRO_FUNCTION;
	}

	vector_push(preprocessor->definitions, &definition);
	return definition;
}


bool preprocessor_is_next_macro_arguments(struct compile_process* compiler) {
	bool res = false;
	vector_save(compiler->token_vec_original);
	struct token* last_token = preprocessor_previous_token(compiler);
	struct token* current_token = preprocessor_next_token(compiler);	
	
	if(token_is_operator(current_token, "(") && (!last_token || !last_token->whitespace)) {
		res = true;
	}

	vector_restore(compiler->token_vec_original);
	return res;
}

void preprocessor_parse_macro_argument_declaration(struct compile_process* compiler, struct vector* arguments) {
	if(token_is_operator(preprocessor_next_token_no_increment(compiler), "(")) {
		// skip '('
		preprocessor_next_token(compiler);
		struct token* next_token = preprocessor_next_token(compiler);
		while(!token_is_symbol(next_token, ')')) {
			if(next_token->type != TOKEN_TYPE_IDENTIFIER) {
				compiler_error(compiler, "Must provide a valid identifier in preprocessor definition\n");
			}
			vector_push(arguments, (void*)next_token->sval);
			next_token = preprocessor_next_token(compiler);
			if(!token_is_operator(next_token, ",") && !token_is_symbol(next_token, ')')) {
				compiler_error(compiler, "Incomplete sequence for macro arguments\n");
			}

			if(token_is_symbol(next_token, ')')) {
				break;
			}
			
			// skip comma
			next_token = preprocessor_next_token(compiler);
		}
	}
}

void preprocessor_handle_definition_token(struct compile_process* compiler) {
	struct token* name_token = preprocessor_next_token(compiler);
	struct vector* arguments = vector_create(sizeof(const char*));

	if(preprocessor_is_next_macro_arguments(compiler)) {
		preprocessor_parse_macro_argument_declaration(compiler, arguments);
	}

	struct vector* value_token_vec = vector_create(sizeof(struct token));
	preprocessor_multi_value_insert_to_vector(compiler, value_token_vec);

	struct preprocessor* preprocessor = compiler->preprocessor;
	preprocessor_definition_create(name_token->sval, value_token_vec, arguments, preprocessor);
}

int preprocessor_handle_hashtag_token(struct compile_process* compiler, struct token* token) {
	bool is_preprocessed = false;
	struct token* next_token = preprocessor_next_token(compiler);
	if(preprocessor_token_is_define(next_token)) {
		// handle definition token
		preprocessor_handle_definition_token(compiler);
		is_preprocessed = true;
	}

	return is_preprocessed;
}

void preprocessor_handle_symbol(struct compile_process* compiler, struct token* token) {
	int is_preprocessed = false;
	if(token->cval == '#') {
		is_preprocessed = preprocessor_handle_hashtag_token(compiler, token);
	}

	if(!is_preprocessed) {
		preprocessor_token_push_dst(compiler, token);
	}
}

void preprocessor_handle_token(struct compile_process* compiler, struct token* token) {
	switch(token->type) {
		case TOKEN_TYPE_SYMBOL:
			preprocessor_handle_symbol(compiler, token);
			break;
		case TOKEN_TYPE_NEWLINE:
			break;
		default:
			preprocessor_token_push_dst(compiler, token);
	}
}

int preprocessor_run(struct compile_process* compiler) {
	#warning "add source file as included file"
	vector_set_peek_pointer(compiler->token_vec_original, 0);
	struct token* token = preprocessor_next_token(compiler);
	while(token) {
		preprocessor_handle_token(compiler, token);
		token = preprocessor_next_token(compiler);
	}
	return 0;
}